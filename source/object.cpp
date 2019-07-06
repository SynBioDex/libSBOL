/**
 * @file    object.cpp
 * @brief   SBOLObject class (a low-level, abstract class)
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

#include "object.h"
#include <raptor2.h>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "document.h"

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
#include "Python.h"
#endif

using namespace std;
using namespace sbol;


SBOLObject::~SBOLObject()
{
    if (type.compare(SBOL_DOCUMENT) != 0)  // Documents have their own destructor override
    {
        for (auto &i_own : owned_objects)
        {
            if (std::find(hidden_properties.begin(), hidden_properties.end(), i_own.first) == hidden_properties.end())
            {
                vector<SBOLObject*>& object_store = i_own.second;
                for (auto &i_obj : object_store)
                    i_obj->close();
            }
        }
    }
}

#if defined(SBOL_BUILD_PYTHON2) || defined(SBOL_BUILD_PYTHON3)
void SBOLObject::register_extension_class(PyObject* python_class, std::string extension_name)
{
    if (namespaces.count(extension_name) == 0)
    {
        // Parse class name from Python __repr__
//        PyObject* bytes = PyUnicode_AsUTF8String(PyObject_Repr(python_class));
//        std::string repr_name = PyBytes_AsString(bytes);
//        size_t left_class_name = repr_name.find_last_of('.') + 1;
//        size_t len_class_name = repr_name.size() - left_class_name - 2;  // eg, <class '__main__.ComponentDerivation'>
//        std::string class_name = repr_name.substr(left_class_name, len_class_name);

        // Register namespace and its prefix (extension name)
        Config::PYTHON_DATA_MODEL_REGISTER[getTypeURI()] = python_class;
        std::string ns = parseNamespace(getTypeURI());
        namespaces[extension_name] = ns;
    }
};


PyObject* SBOLObject::cast(PyObject* python_class)
{
    typedef struct {
        PyObject_HEAD
        void *ptr; // This is the pointer to the actual C++ instance
        void *ty;  // swig_type_info originally, but shouldn't matter
        int own;
        PyObject *next;
    } SwigPyObject;

    PyObject* py_obj = PyObject_CallObject(python_class, NULL);  // Call constructor
    PyObject* temp_py_object = PyObject_GetAttr(py_obj, PyUnicode_FromString("this"));
    SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj, PyUnicode_FromString("this"));
    SBOLObject* new_obj = (SBOLObject *)swig_py_object->ptr;

    // Set identity
    new_obj->identity.set(this->identity.get());

    // Copy properties
    for (auto it = this->properties.begin(); it != this->properties.end(); it++)
    {
        new_obj->properties[it->first] = this->properties[it->first];
    }
    for (auto it = this->owned_objects.begin(); it != this->owned_objects.end(); it++)
    {
        new_obj->owned_objects[it->first] = this->owned_objects[it->first];
    }
    for (auto it = this->namespaces.begin(); it != this->namespaces.end(); it++)
    {
        new_obj->namespaces[it->first] = this->namespaces[it->first];
    }
    new_obj->parent = this->parent;
    new_obj->doc = this->doc;

    return py_obj;
};

#endif



bool sbol::operator !=(const SBOLObject &a, const SBOLObject &b)
{
    return (&a != &b);
};

void SBOLObject::close()
{
    delete this;
};

rdf_type SBOLObject::getTypeURI()
{
	return type;
};

std::string SBOLObject::getClassName(string type)
{
    std::size_t uri_subordinate_pos = type.find("#") + 1;
    if (uri_subordinate_pos != std::string::npos)
    {
        std::string sbol_class = type.substr(uri_subordinate_pos, type.size() - uri_subordinate_pos);
        return sbol_class;
    }
    else
        return type;
};


int SBOLObject::compare(SBOLObject* comparand)
{
    int IS_EQUAL = 1;
    if (type.compare(comparand->type) != 0)
    {
        std::cout << identity.get() << " does not match type of " << comparand->type << endl;
        return 0;
    };

    if (type.compare(SBOL_DOCUMENT) == 0)
    {
        vector < string > ns_list = {};
        vector < string > comparand_ns_list = {};
        for (auto &i_ns : namespaces)
            ns_list.push_back(i_ns.second);
        for (auto &i_ns : comparand->namespaces)
            comparand_ns_list.push_back(i_ns.second);
        sort(ns_list.begin(), ns_list.end());
        sort(comparand_ns_list.begin(), comparand_ns_list.end());
        if (!equal(ns_list.begin(), ns_list.end(), comparand_ns_list.begin()))
        {
            cout << "Namespaces do not match" << endl;
            int IS_EQUAL = 0;
        }
    }

    std::string l_id;
    std::string r_id;
    std::map < std::string, std::vector<std::string> >::iterator i_lp;  // iterator for left-hand side
    std::map < std::string, std::vector<std::string> >::iterator i_rp;  // iterator for right-hand side
    std::map < std::string, std::vector<std::string> >::iterator i_end;  // stop iteration

    // The longer property store is assigned to left-hand side for side-by-side comparison. Property keys are assumed alphabetically sorted since they are based on std::map
    if (properties.size() >= comparand->properties.size())
    {
        if (this->type != SBOL_DOCUMENT)
        {
            l_id = identity.get();
            r_id = comparand->identity.get();
        }
        else
        {
            l_id = "Document 1";
            r_id = "Document 2";
        }
        i_lp = properties.begin();
        i_rp = comparand->properties.begin();
        i_end = properties.end();
    }
    else
    {
        if (this->type != SBOL_DOCUMENT)
        {
            l_id = comparand->identity.get();
            r_id = identity.get();
        }
        else
        {
            l_id = "Document 2";
            r_id = "Document 1";
        }
        i_lp = comparand->properties.begin();
        i_rp = properties.begin();
        i_end = comparand->properties.end();

    }
    while (i_lp != i_end )
    {
        std::string l_key = i_lp->first;
        std::string r_key = i_rp->first;
        // In case one object has a property (ie, extension annotation) that another object does not
        if(l_key.compare(r_key) != 0)
        {
            cout << r_id << "::" << parsePropertyName(r_key) << " not found in " << l_id << endl;
            ++i_lp;
            IS_EQUAL = 0;
        }
        // If the property's match, then iterate through property values and compare them
        else
        {
            // Copy and sort the property store, so we can compare them side by side
            std::vector < std::string > l_store(i_lp->second);
            std::vector < std::string > r_store(i_rp->second);
            std::sort(l_store.begin(), l_store.end());
            std::sort(r_store.begin(), r_store.end());
            if (!std::equal(l_store.begin(), l_store.end(), r_store.begin()))
            {
                cout << "Values " << " in " << l_id << "::" << parsePropertyName(l_key) << " not equal to values in " << r_id << "::" << parsePropertyName(r_key) << endl;
                IS_EQUAL = 0;
            }
            ++i_lp;
            ++i_rp;
        }
    }

    /// @TODO this may fail if there are extension properties resulting in owned_objects of differing lengths in the comparand objects
    for (auto i_p = owned_objects.begin(); i_p != owned_objects.end(); ++i_p)
    {
        string p = i_p->first;

        SBOLObject* l;
        SBOLObject* r;
        if (this->owned_objects[p].size() >= comparand->owned_objects[p].size())
        {
            l = this;
            r = (SBOLObject*)comparand;
        }
        else
        {
            l = (SBOLObject*)comparand;
            r = this;
        }

        vector<SBOLObject*>& l_object_store = l->owned_objects[p];
        vector<SBOLObject*>& r_object_store = r->owned_objects[p];

        map<string, SBOLObject*> l_store_map;
        map<string, SBOLObject*> r_store_map;
        for (auto i_obj = l_object_store.begin(); i_obj != l_object_store.end(); ++i_obj)
        {
            SBOLObject* obj = *i_obj;
            l_store_map[obj->identity.get()] = obj;
        }
        for (auto i_obj = r_object_store.begin(); i_obj != r_object_store.end(); ++i_obj)
        {
            SBOLObject* obj = *i_obj;
            r_store_map[obj->identity.get()] = obj;
        }
        map<string, SBOLObject*>::iterator l_p = l_store_map.begin();
        map<string, SBOLObject*>::iterator r_p = r_store_map.begin();
        while (l_p != l_store_map.end())
        {
            string l_id = l_p->first;
            string r_id = r_p->first;
            if (l_id.compare(r_id) == 0)
            {
                SBOLObject* l_obj = l_store_map[l_id];
                SBOLObject* r_obj = r_store_map[r_id];
                if (!l_obj->compare(r_obj))  // Recurse into child objects and compare
                    IS_EQUAL = 0;
                ++l_p;
                ++r_p;
            }
            else
            {
                cout << "Child object " << l_id << " not in " << parsePropertyName(p) << " property of " << r->identity.get() << endl;
                IS_EQUAL = 0;
                ++l_p;
            }
        }
    }
    if (IS_EQUAL)
        return 1;
    else
        return 0;
};

//int SBOLObject::find(string uri)
//{
//    if (identity.get() == uri)
//        return 1;
//    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
//    {
//        vector<SBOLObject*>& store = i_store->second;
//        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
//        {
//            SBOLObject& obj = **i_obj;
//            if (obj.find(uri))
//                return 1;
//        }
//    }
//    return 0;
//};


void SBOLObject::apply(void (*callback_fn)(SBOLObject *, void *), void * user_data)
{
    callback_fn(this, user_data);
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        // Skip hidden properties
        if (std::find(hidden_properties.begin(), hidden_properties.end(), i_store->first) != hidden_properties.end())
            continue;
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            obj.apply(callback_fn, user_data);
        }
    }
    return;
};

void SBOLObject::cacheObjects(std::map<std::string, sbol::SBOLObject*> &cache) {
    cache[identity.get()] = this;

    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        if (std::find(hidden_properties.begin(), hidden_properties.end(), i_store->first) != hidden_properties.end())
            continue;
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject &obj = **i_obj;
            obj.cacheObjects(cache);
        }
    }
}

SBOLObject* SBOLObject::find(string uri)
{
    if (identity.get() == uri)
        return this;
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        // Skip hidden properties
        if (std::find(hidden_properties.begin(), hidden_properties.end(), i_store->first) != hidden_properties.end())
            continue;
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            if (obj.find(uri))
                return obj.find(uri);
        }
    }
    return NULL;
};

SBOLObject* SBOLObject::find_property(string uri)
{
    if (owned_objects.find(uri) != owned_objects.end() && properties.find(uri) != properties.end())
        return this;
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            if (obj.find_property(uri))
                return obj.find_property(uri);
        }
    }
    return NULL;
};

//std::vector < SBOLObject* > SBOLObject::find_property_value(string uri, string value)
//{
//    std::vector < SBOLObject* > = found_objects;
//    if (owned_objects.find(uri) != owned_objects.end() && properties.find(uri) != properties.end() && !value.compare(comparand))
//    {
//        found_objects.push_back(this);
//        return found_objects;
//    }
//    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
//    {
//        vector<SBOLObject*>& store = i_store->second;
//        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
//        {
//            SBOLObject& obj = **i_obj;
//            if (obj.find_property_value(uri, value).size() > 0)
//            {
//                std::vector < SBOLObject* > = more_found_objects = obj.find_property(uri, value);
//                std::vector < SBOLObject* > = found_objects.insert( found_objects.end(), more_found_objects.begin(), more_found_objects.end() );
//            }
//        }
//    }
//    return found_objects;
//};

vector<SBOLObject*> SBOLObject::find_property_value(string uri, string value, vector<SBOLObject*> matches)
{
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        // Skip hidden and aliased properties
        if (std::find(hidden_properties.begin(), hidden_properties.end(), i_store->first) != hidden_properties.end())
            continue;
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            vector<SBOLObject*> more_matches = obj.find_property_value(uri, value);
            matches.insert(matches.end(), more_matches.begin(), more_matches.end());
        }
    }
    // if (properties.find(uri) == properties.end())
    //     throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot find property value. " + uri + " is not a valid property type.");
    if (properties.find(uri) == properties.end())
        return matches;
    
    std::vector<std::string> value_store = properties[uri];
    for (auto & val : value_store)
    {
        if (val.compare("\"" + value + "\"") == 0)
        {
            matches.push_back(this);
        }
        if (val.compare("<" + value + ">") == 0)
        {
            matches.push_back(this);
        }
    }
    return matches;
};

vector<SBOLObject*> SBOLObject::find_reference(string uri)
{
    vector<SBOLObject*> matches = {};
    for (auto i_store = owned_objects.begin(); i_store != owned_objects.end(); ++i_store)
    {
        vector<SBOLObject*>& store = i_store->second;
        for (auto i_obj = store.begin(); i_obj != store.end(); ++i_obj)
        {
            SBOLObject& obj = **i_obj;
            vector<SBOLObject*> newMatches = obj.find_reference(uri);
            for(auto &el : newMatches)
            {
                matches.push_back(el);
            }
        }
    }

    for (auto &i_p : properties)
    {
        for(string val : i_p.second)
        {
            if (val.compare("<" + uri + ">") == 0)
            {
                matches.push_back(this);
                break;
            }
        }
    }

    return matches;
};


string SBOLObject::makeQName(string uri)
{
    string ns = parseNamespace(uri);
    string local_id = parsePropertyName(uri);
    string qname = "";
    for(auto const& i_ns : this->namespaces)
    {
        if (ns.compare(i_ns.second) == 0)
            qname = i_ns.first + ":" + local_id;
    }
    return qname;
};

std::string SBOLObject::getPropertyValue(std::string property_uri)
{
    if (properties.find(property_uri) != properties.end())
    {
        std::string property_value = properties[property_uri][0];
        property_value = property_value.substr(1, property_value.length() - 2);
        return property_value;
    }
    else throw SBOLError(SBOL_ERROR_NOT_FOUND, property_uri + " not contained in this object.");
};

void SBOLObject::setPropertyValue(std::string property_uri, std::string val)
{
    if (properties.find(property_uri) != properties.end())
    {
        if (properties[property_uri][0][0] == '<')
        {
            // Check if new value is a URI...
            properties[property_uri][0] = "<" + val + ">";
        }
        else if (properties[property_uri][0][0] == '\"')
        {
            // ...else treat the value as a literal
            properties[property_uri][0] = "\"" + val + "\"";
        }
    }
    else throw SBOLError(SBOL_ERROR_NOT_FOUND, property_uri + " not contained in this object.");

};

void SBOLObject::addPropertyValue(std::string property_uri, std::string val)
{
    if (properties.find(property_uri) != properties.end())
    {
        if (properties[property_uri][0][0] == '<')
        {
            // Check if new value is a URI...
            properties[property_uri].push_back("<" + val + ">");
        }
        else if (properties[property_uri][0][0] == '\"')
        {
            // ...else treat the value as a literal
            properties[property_uri].push_back("\"" + val + "\"");
        }
    }
    else throw SBOLError(SBOL_ERROR_NOT_FOUND, property_uri + " not contained in this object.");
};

std::vector < std::string > SBOLObject::getPropertyValues(std::string property_uri)
{
    if (properties.find(property_uri) != properties.end())
    {
        std::vector < std::string > property_values = properties[property_uri];
        for (auto i_val = 0; i_val < property_values.size(); ++i_val)
        {
            std::string val = property_values[i_val];
            property_values[i_val] = val.substr(1, val.length() - 2);
        }
        return property_values;
    }
    else throw SBOLError(SBOL_ERROR_NOT_FOUND, property_uri + " not contained in this object.");
};


std::vector < std::string > SBOLObject::getProperties()
{
    std::vector < std::string > property_uris;
    for (auto i_p = properties.begin(); i_p != properties.end(); ++i_p)
    {
        string uri = i_p->first;
        property_uris.push_back(uri);
    }
    for (auto i_p = owned_objects.begin(); i_p != owned_objects.end(); ++i_p)
    {
        string uri = i_p->first;
        property_uris.push_back(uri);
    }
    return property_uris;
};

void SBOLObject::setAnnotation(std::string property_uri, std::string val)
{
    setPropertyValue(property_uri, val);
};

std::string SBOLObject::getAnnotation(std::string property_uri)
{
    return getPropertyValue(property_uri);
};

// Python extension method
std::string SBOLObject::__str__()
{
    return identity.get();
}


URIProperty::URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value) :
    Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules, "<" + initial_value + ">")
{
}

URIProperty::URIProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
    Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
{
    // Overwrite default. By default, literal properties are initialized to quotes
    this->sbol_owner->properties[type_uri][0] = "<>";
}

std::vector<std::string> TextProperty::getAll()
{
    if (this->sbol_owner)
    {
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            // not found
            throw std::runtime_error("This property is not defined in the parent object");
        }
        else
        {
            // found
            if (this->size() == 0)
                return std::vector < std::string >(0);
            //                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
            else
            {
                std::vector<std::string> values;
                std::vector<std::string>& value_store = this->sbol_owner->properties[type];
                for (auto i_val = value_store.begin(); i_val != value_store.end(); ++i_val)
                {
                    std::string value = *i_val;
                    value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                    values.push_back(value);
                }
                return values;
            }
        }
    }	else
    {
        throw std::runtime_error("This property is not associated with a parent object");
    }
};

std::vector<std::string> URIProperty::getAll()
{
    if (this->sbol_owner)
    {
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            // not found
            throw std::runtime_error("This property is not defined in the parent object");
        }
        else
        {
            // found
            if (this->size() == 0)
                return std::vector < std::string >(0);
            //                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
            else
            {
                std::vector<std::string> values;
                std::vector<std::string>& value_store = this->sbol_owner->properties[type];
                for (auto i_val = value_store.begin(); i_val != value_store.end(); ++i_val)
                {
                    std::string value = *i_val;
                    value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                    values.push_back(value);
                }
                return values;
            }
        }
    }	else
    {
        throw std::runtime_error("This property is not associated with a parent object");
    }
};

std::vector<int> IntProperty::getAll()
{
    if (this->sbol_owner)
    {
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            // not found
            throw std::runtime_error("This property is not defined in the parent object");
        }
        else
        {
            // found
            if (this->size() == 0)
                return std::vector < int >(0);
            //                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
            else
            {
                std::vector<int> values;
                std::vector<std::string>& value_store = this->sbol_owner->properties[type];
                for (auto i_val = value_store.begin(); i_val != value_store.end(); ++i_val)
                {
                    std::string str_val = *i_val;
                    str_val = str_val.substr(1, str_val.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                    int value = stoi(str_val);
                    values.push_back(value);
                }
                return values;
            }
        }
    }	else
    {
        throw std::runtime_error("This property is not associated with a parent object");
    }
};

std::vector<double> FloatProperty::getAll()
{
    if (this->sbol_owner)
    {
        if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
        {
            // not found
            throw std::runtime_error("This property is not defined in the parent object");
        }
        else
        {
            // found
            if (this->size() == 0)
                return std::vector < double >(0);
            //                    throw SBOLError(NOT_FOUND_ERROR, "Property has not been set");
            else
            {
                std::vector<double> values;
                std::vector<std::string>& value_store = this->sbol_owner->properties[type];
                for (auto i_val = value_store.begin(); i_val != value_store.end(); ++i_val)
                {
                    std::string str_val = *i_val;
                    str_val = str_val.substr(1, str_val.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                    double value = stod(str_val);
                    values.push_back(value);
                }
                return values;
            }
        }
    }	else
    {
        throw std::runtime_error("This property is not associated with a parent object");
    }
};

TextProperty::TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value) :
    Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules, "\"" + initial_value + "\"")
{
}

TextProperty::TextProperty(void *property_owner, rdf_type type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
    Property(property_owner, type_uri, lower_bound, upper_bound, validation_rules)
{
}

ReferencedObject::ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules, std::string initial_value) :
    URIProperty(property_owner, type_uri, lower_bound, upper_bound, validation_rules, initial_value),
    reference_type_uri(reference_type_uri)
    {
        // Register Property in owner Object
        if (this->sbol_owner != NULL)
        {
            std::vector<std::string> property_store;
            this->sbol_owner->properties.insert({ type_uri, property_store });
        }
    };

ReferencedObject::ReferencedObject(void *property_owner, rdf_type type_uri, rdf_type reference_type_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
URIProperty(property_owner, type_uri, lower_bound, upper_bound, validation_rules),
reference_type_uri(reference_type_uri)
    {
        // Register Property in owner Object
        if (this->sbol_owner != NULL)
        {
            std::vector<std::string> property_store;
            this->sbol_owner->properties.insert({ type_uri, property_store });
        }
    };

void ReferencedObject::set(std::string uri)
{
    if (this->sbol_owner)
    {
        //sbol_owner->properties[type].push_back( new_value );
        std::string current_value = this->sbol_owner->properties[this->type][0];
        if (current_value[0] == '<')  //  this property is a uri
        {
            this->sbol_owner->properties[this->type][0] = "<" + uri + ">";
        }
        validate((void *)&uri);
    }
};

void ReferencedObject::add(std::string uri)
{
    if (sbol_owner)
    {
        std::string current_value = this->sbol_owner->properties[this->type][0];
        if (current_value[0] == '<')  //  this property is a uri
        {
            if (current_value[1] == '>')
                this->sbol_owner->properties[this->type][0] = "<" + uri + ">";
            else
                this->sbol_owner->properties[this->type].push_back("<" + uri + ">");
        }
        validate((void *)&uri);  //  Call validation rules associated with this Property
    }
};

// For compliant URIs
void ReferencedObject::setReference(const std::string uri)
{
    if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
    {
        // if not TopLevel throw an error
        // @TODO search Document by persistentIdentity and retrieve the latest version
        set(getHomespace() + "/" + parseClassName(this->reference_type_uri) + "/" + uri + "/1.0.0");
    }
    else if (hasHomespace())
    {
        set(getHomespace() + "/" + uri);
    }
    else
        set(uri);
};

//// For compliant URIs
//void ReferencedObject::setReference(const std::string uri_prefix, const std::string display_id, const std::string version)
//{
//    std::string sbol_class_name = parseClassName(this->reference_type_uri);
//    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, version);
//    this->set(compliant_uri);
//};
//
//// For compliant URIs
//void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id)
//{
//    std::string sbol_class_name = parseClassName(this->reference_type_uri);
//    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, "1.0.0");
//    this->addReference(compliant_uri);
//};
//
//// For compliant URI's
//void ReferencedObject::addReference(const std::string uri_prefix, const std::string display_id, const std::string version)
//{
//    std::string sbol_class_name = parseClassName(this->reference_type_uri);
//    std::string compliant_uri = getCompliantURI(uri_prefix, sbol_class_name, display_id, version);
//    this->addReference(compliant_uri);
//};


std::string ReferencedObject::operator[] (const int nIndex)
{
    std::vector<std::string> *reference_store = &this->sbol_owner->properties[this->type];
    return reference_store->at(nIndex);
};


void ReferencedObject::addReference(const std::string uri)
{
    this->sbol_owner->properties[this->type].push_back("<" + uri + ">");
};

void SBOLObject::serialize_rdfxml(std::ostream &os, size_t indentLevel) {
    const size_t spaces_per_indent = 2;

    std::string indentString = std::string(spaces_per_indent * indentLevel,
                                           ' ');
    
    // Serialize properties
    for(auto &propPair : properties) {

        auto &propValues = propPair.second;

        if(propPair.first.compare("http://sbols.org/v2#identity") == 0) {
            // This property is not serialized
            continue;
        }

        if(propValues.size() == 1 &&
           (propValues.at(0) == "\"\"" || propValues.at(0) == "<>"))
        {
            // No properties of this type
            continue;
        }
        
        auto predicate = doc->referenceNamespace(propPair.first);

        for(auto propValue : propValues) {
            if(propValue[0] == '<') {
                // URI
                os << indentString
                   << "<" << predicate << " rdf:resource=\""
                   << propValue.substr(1, propValue.size()-2)
                   << "\"/>" << std::endl;

            } else {
                // Non-URI Literal

                // Some characters need to be escaped
                std::string::size_type pos = 0;
                while(true) {
                    const char *cStr = propValue.c_str();
                    std::string::size_type len = propValue.size();
                    bool done = true;

                    for(; pos<len; ++pos)
                    {
                        if(cStr[pos] == '<')
                        {
                            propValue = propValue.replace(pos, 1, "&lt;");
                            pos += 4;
                            done = false;
                            break;
                        }

                        if(cStr[pos] == '>')
                        {
                            propValue = propValue.replace(pos, 1, "&gt;");
                            pos += 4;
                            done = false;
                            break;
                        }

                        if(cStr[pos] == '&')
                        {
                            propValue = propValue.replace(pos, 1, "&amp;");
                            pos += 5;
                            done = false;
                            break;
                        }
                    }

                    if(done) {
                        break;
                    }
                }

                os << indentString
                   << "<" << predicate << ">"
                   << propValue.substr(1, propValue.size()-2)
                   << "</" << predicate << ">"
                   << std::endl;
            }
        }
    }

    std::string indentString2 =
      std::string(spaces_per_indent * (indentLevel + 1), ' ');

    // Serialize owned objects
    for(auto ownedPair : owned_objects)
    {
        if(ownedPair.second.size() == 0) {
            continue;
        }

        std::string predicate = doc->referenceNamespace(ownedPair.first);

        for(auto &i_obj : ownedPair.second)
        {
            auto typeURI = i_obj->getTypeURI();

            if (std::find(hidden_properties.begin(), hidden_properties.end(), typeURI)
                != hidden_properties.end()) {
                continue;
            }

            std::string rdfType = doc->referenceNamespace(typeURI);
            std::string identity = i_obj->identity.get();

            os << indentString << "<" << predicate
               << ">" << std::endl;

            os << indentString2
               << "<" << rdfType << " rdf:about=\""
               << identity << "\">" << std::endl;

            i_obj->serialize_rdfxml(os, indentLevel + 2);

            os << indentString2
               << "</" << rdfType << ">" << std::endl;

            os << indentString
               << "</" << predicate << ">" << std::endl;
        }
    }
}
