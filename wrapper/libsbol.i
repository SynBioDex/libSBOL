%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    //  Headers are listed in strict order of dependency
    #include "constants.h"
    #include "sbolerror.h"
    #include "config.h"
    #include "validation.h"
    #include "property.h"
    #include "properties.h"
    #include "object.h"
    #include "identified.h"
    #include "measurement.h"
    #include "toplevel.h"
    #include "sequenceannotation.h"
    #include "component.h"
    #include "componentdefinition.h"
    #include "sequence.h"
    #include "document.h"
    #include "interaction.h"
    #include "participation.h"
    #include "location.h"
    #include "sequenceconstraint.h"
    #include "moduledefinition.h"
    #include "module.h"

    #include "mapsto.h"
    #include "model.h"
    #include "collection.h"
    #include "provo.h"
    #include "partshop.h"
    #include "combinatorialderivation.h"
    #include "attachment.h"
    #include "implementation.h"
    #include "experiment.h"
    #include "dbtl.h"
    #include "sbol.h"

    #include <vector>
    #include <map>
    #include <unordered_map>

    using namespace sbol;
    using namespace std;
    
%}
%include "python_docs.i"

#ifdef SWIGWIN
    %include <windows.i>
#endif

// I was never successful in getting typemap(in) to convert a Python list argument into C++ types, so I hacked these helper functions to perform the conversion
%{
    std::vector<std::string> convert_list_to_string_vector(PyObject *list)
    {
        if (!PyList_Check(list))
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "First argument must be a List of ComponentDefinition objects or Strings containing their displayIds");
        if (PyList_Size(list) == 0)
            return {};
        PyObject *obj = PyList_GetItem(list, 0);
        std::vector<std::string> list_of_cpp_strings;
        if (PyUnicode_Check(obj))
        {
            // Convert Python 3 strings
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                obj = PyList_GetItem(list, i);
                PyObject* bytes = PyUnicode_AsUTF8String(obj);
                std::string cpp_string = PyBytes_AsString(bytes);
                list_of_cpp_strings.push_back(cpp_string);
            }
        }
        else if (PyBytes_Check(obj))
        {
            // Convert Python 2 strings
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                obj = PyList_GetItem(list, i);
                std::string cpp_string = PyBytes_AsString(obj);
                list_of_cpp_strings.push_back(cpp_string);
            }
        }
        return list_of_cpp_strings;
    }
    
    std::vector<sbol::ComponentDefinition*> convert_list_to_cdef_vector(PyObject *list)
    {
        if (!PyList_Check(list))
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "First argument must be a List of ComponentDefinition objects or Strings containing their displayIds");
        if (PyList_Size(list) == 0)
            return {};
        PyObject *obj;
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = {};
        sbol::ComponentDefinition* cd;
        for (int i = 0; i < PyList_Size(list); ++i)
        {
            obj = PyList_GetItem(list, i);
            if ((SWIG_ConvertPtr(obj,(void **) &cd, SWIG_TypeQuery("sbol::ComponentDefinition*"),1)) == -1) break;
            list_of_cdefs.push_back(cd);
        }
        return list_of_cdefs;
    }

    std::vector<sbol::Identified*> convert_list_to_identified_vector(PyObject *list)
    {
        if (!PyList_Check(list))
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "First argument must be a List of ComponentDefinition objects or Strings containing their displayIds");
        if (PyList_Size(list) == 0)
            return {};
        PyObject *py_obj = PyList_GetItem(list, 0);
        std::vector<sbol::Identified*> identified_vector = {};
        sbol::Identified* sbol_obj;
        if (SWIG_IsOK(SWIG_ConvertPtr(py_obj,(void **) &sbol_obj, SWIG_TypeQuery("sbol::Identified*"),1)))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                py_obj = PyList_GetItem(list, i);
                if ((SWIG_ConvertPtr(py_obj,(void **) &sbol_obj, SWIG_TypeQuery("sbol::Identified*"),1)) == -1) 
                    throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Usages must be a valid SBOL object");;
                int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
                identified_vector.push_back(sbol_obj);
            }
        }
        return identified_vector;
    }
%}





//  General error handling and mapping of libSBOL exception types to Python exception types
%exception {
    try
    {
        $function
    }
    catch(SBOLError e)
    {
        if (e.error_code() == SBOL_ERROR_NOT_FOUND)
        {
            PyErr_SetString(PyExc_LookupError, e.what());
        }
        else if (e.error_code() == SBOL_ERROR_INVALID_ARGUMENT || e.error_code() == SBOL_ERROR_MISSING_DOCUMENT)
        {
            PyErr_SetString(PyExc_ValueError, e.what());
        }
        else if (e.error_code() == SBOL_ERROR_TYPE_MISMATCH)
        {
            PyErr_SetString(PyExc_TypeError, e.what());
        }
        else if (e.error_code() == SBOL_ERROR_FILE_NOT_FOUND)
        {
            PyErr_SetString(PyExc_IOError, e.what());
        }
        else
        {
            PyErr_SetString(PyExc_RuntimeError, e.what());
        }
        return NULL;
    }
    catch(...)
    {
        PyErr_SetString(PyExc_RuntimeError, "An error of unspecified type occurred");
    }
}

// Catch the signal from the Python interpreter indicating that iteration has reached end of list. For Python 2
%exception next
{
    try
    {
        $action
    }
    catch(SBOLError e)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}

// Catch the signal from the Python interpreter indicating that iteration has reached end of list. For Python 3
%exception __next__
{
    try
    {
        $action
    }
    catch(SBOLError e)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}

// Hide these methods in the Python API
%ignore sbol::SBOLObject::close;
%ignore sbol::SBOLObject::properties;
%ignore sbol::SBOLObject::list_properties;
%ignore sbol::SBOLObject::owned_objects;
%ignore sbol::SBOLObject::begin;
// %ignore sbol::SBOLObject::end;
%ignore sbol::SBOLObject::size;
%ignore sbol::Property::begin;
%ignore sbol::Property::end;
%ignore sbol::Property::size;

%ignore sbol::OwnedObject::begin;
%ignore sbol::OwnedObject::end;
%ignore sbol::OwnedObject::size;
%ignore sbol::ReferencedObject::begin;
%ignore sbol::ReferencedObject::end;
%ignore sbol::ReferencedObject::size;
%ignore sbol::Document::parse_objects;
%ignore sbol::Document::parse_properties;
%ignore sbol::Document::namespaceHandler;
%ignore sbol::Document::flatten();
%ignore sbol::Document::parse_objects;
%ignore sbol::Document::close;
%ignore sbol::ComponentDefinition::assemble(std::vector<std::string> list_of_uris, Document& doc);  // Use variant signature defined in this interface file
%ignore sbol::ComponentDefinition::assemble(std::vector<std::string> list_of_uris);  // Use variant signature defined in this interface file
%ignore sbol::ComponentDefinition::linearize(std::vector<std::string> list_of_uris);  // Use variant signature defined in this interface file
%ignore sbol::ComponentDefinition::assemblePrimaryStructure(std::vector<ComponentDefinition*> primary_structure);
%ignore sbol::ComponentDefinition::assemblePrimaryStructure(std::vector<ComponentDefinition*> primary_structure, Document& doc);
%ignore sbol::ComponentDefinition::assemblePrimaryStructure(std::vector<std::string> primary_structure);
%ignore sbol::ComponentDefinition::compile;               // Overriden in this file in native python
%ignore sbol::ComponentDefinition::getInSequentialOrder;  // Overriden in this file in native python

%ignore sbol::TopLevel::addToDocument;
%ignore sbol::PartShop::submit;  // A pure Python method is monkey-patched over this one in this file

// Instantiate STL templates
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
#include <string>

// This typemap is here in order to convert the return type of ComponentDefinition::getPrimaryStructure into a Python list. (The typemaps defined later in this file work on other methods, but did not work on this method specifically)
%typemap(out) std::vector < sbol::ComponentDefinition* > {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        ComponentDefinition* cd = *i_elem;
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::ComponentDefinition*), 0 |  0 );
        PyList_Append(list, elem);
    }
    $result  = list;
    $1.clear();
    PyErr_Clear();
}

// This typemap is here in order to convert the return type of ComponentDefinition::sortSequenceAnnotations into a Python list. 
%typemap(out) std::vector < sbol::SequenceAnnotation* > {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::SequenceAnnotation*), 0 |  0 );
        PyList_Append(list, elem);
    }
    $result  = list;
    $1.clear();
    PyErr_Clear();
}

// Typemap the hash table returned by Analysis::report methods
%typemap(out) std::unordered_map < std::string, std::tuple < int, int, float > > {
    int len = $1.size();
    PyObject* dict = PyDict_New();
    for(auto & i_elem : $1)
    {
        std::tuple < int, int, float > vals = i_elem.second;
        int range_start = std::get<0>(vals);
        int range_end = std::get<1>(vals);
        float qc_stat = std::get<2>(vals);
        PyObject* py_vals = Py_BuildValue("iif", range_start, range_end, qc_stat);
        PyDict_SetItemString(dict, i_elem.first.c_str(), py_vals);
    }
    $result  = dict;
    $1.clear();
    
}

%template(_IntVector) std::vector<int>;
%template(_StringVector) std::vector<std::string>;
%template(_SBOLObjectVector) std::vector<sbol::SBOLObject*>;
%template(_MapVector) std::map<std::string, std::string >;
%template(_MapOfStringVector) std::map<std::string, std::vector<std::string> >;
%template(_MapOfSBOLObject) std::map<std::string, std::vector< sbol::SBOLObject* > >;


// Instantiate libSBOL templates
%include "config.h"
%include "constants.h"
%include "validation.h"
%include "property.h"

%template(_StringProperty) sbol::Property<std::string>;  // These template instantiations are private, hence the underscore...
%template(_IntProperty) sbol::Property<int>;
%template(_FloatProperty) sbol::Property<double>;

%pythonappend add
%{
    try:
        sbol_obj.thisown = False
    except NameError:
        try:
            if not type(args[0]) == str:
                args[0].thisown = False
        except NameError:
            pass
%}

%pythonappend set
%{
    try:
        sbol_obj.thisown = False
    except NameError:
        try:
            if not type(args[0]) == str:
                args[0].thisown = False
        except NameError:
            pass
%}
    
%pythonappend create
%{
    val.thisown = False
%}
    
// verifyTarget acts like a setter
%pythonappend verifyTarget
%{
    consensus_sequence.thisown = False
%}
    
/* @TODO remove methods should change thisown flag back to True */
/* Currently this causes an exception (probably need a call to Py_INCREF */
//%pythonprepend remove
//%{
//    print ("Getting " + args[0])
//    obj = self.get(args[0])
//    obj.thisown = True
//%}
    
%pythonappend getAll
%{
    val = list(val)
%}

//%pythonappend addToDocument
//%{
//    print("Adding to Document")
//    arg2.thisown = False
//%}
    
    
%include "properties.h"
%include "object.h"
%include "identified.h"
%include "measurement.h"
%include "toplevel.h"
%include "location.h"
%include "sequenceannotation.h"
%include "mapsto.h"
%include "component.h"
%include "sequenceconstraint.h"
%include "componentdefinition.h"
%include "sequence.h"
%include "participation.h"
%include "interaction.h"
%include "module.h"
%include "model.h"
%include "collection.h"
%include "moduledefinition.h"
%include "provo.h"
%include "combinatorialderivation.h"
%include "attachment.h"
%include "implementation.h"
%include "experiment.h"
%include "dbtl.h"

%pythonappend sbol::PartShop::searchRootCollections
%{
    return json.loads(val)
%}

%pythonappend sbol::PartShop::searchSubCollections
%{
    return json.loads(val)
%}

%pythonappend sbol::PartShop::sparqlQuery
%{
    return json.loads(val)
%}

%include "partshop.h"
    
%include "document.h"

typedef std::string sbol::sbol_type;

/* This macro is used to instantiate container properties (OwnedObjects) that can contain more than one type of object, eg, SequenceAnnotation::locations */
%define TEMPLATE_MACRO_0(SBOLClass)
//    %template(add ## SBOLClass) sbol::OwnedObject::add<SBOLClass>;
    %template(create ## SBOLClass) sbol::OwnedObject::create<SBOLClass>;
    %template(get ## SBOLClass) sbol::OwnedObject::get<SBOLClass>;
    
%enddef

/* Convert C++ vector of pointers --> Python list */
%template(ComponentVector) std::vector<sbol::Component*>;
%typemap(out) std::vector<sbol::Component*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::Component*), 0 |  0 );
        PyList_Append(list, elem);
    }
    $result  = list;
    $1.clear();
}

/* This macro is used to instantiate container properties (OwnedObjects) that can contain a single type of object, eg, ComponentDefinition::sequenceAnnotations */
%define TEMPLATE_MACRO_1(SBOLClass)
    
    /* Convert C++ vector of pointers --> Python list */
    %typemap(out) std::vector<sbol::SBOLClass*> {
        int len = $1.size();
        PyObject* list = PyList_New(0);
        for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
        {
            PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::SBOLClass*), 0 |  0 );
            PyList_Append(list, elem);
        }
        $result  = list;
        $1.clear();
    }
    
    %extend sbol::OwnedObject<sbol::SBOLClass >
    {
        PyObject* __getitem__(const int nIndex)
        {
            SBOLClass& obj = $self->operator[](nIndex);
            PyObject *py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::SBOLClass*), 0 |  0 );
            return py_obj;
        }
        
        PyObject* __getitem__(const std::string uri)
        {
            SBOLClass& obj = $self->operator[](uri);
            PyObject *py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::SBOLClass*), 0 |  0 );
            return py_obj;
        }
        
        void __setitem__(const std::string uri, PyObject* py_obj)
        {
            sbol:: SBOLClass* obj;
            if ((SWIG_ConvertPtr(py_obj,(void **) &obj, $descriptor(sbol:: SBOLClass *),1)) == -1) throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Invalid object type for this property");
            $self->add(*obj);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            if (uri == obj->identity.get() || uri  == obj->displayId.get())
                return;
            else
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot add " + parseClassName(obj->type) + ". The given URIs do not match");
        }

        bool __contains__(const std::string uri)
        {
            if ($self->find(uri))
                return true;
            else 
                return false;
        }

    }
    
    /* Instantiate templates */
    %template(SBOLClass ## Vector) std::vector<sbol::SBOLClass>;
    %template(SBOLClass ## Property) sbol::Property<sbol::SBOLClass >;
    %template(Owned ## SBOLClass) sbol::OwnedObject<sbol::SBOLClass >;

%enddef

/* This macro is used to instantiate special adders and getters for the Document class */
%define TEMPLATE_MACRO_2(SBOLClass)

    %extend sbol::SBOLClass
    {
        SBOLClass& copy(Document* target_doc = NULL, std::string ns = "", std::string version = "")
        {
            return $self->copy < SBOLClass >(target_doc, ns, version);
        }
    }
    
    %pythonappend add ## SBOLClass
    %{
        if type(args[0]) is list:
            for obj in args[0]:
                obj.thisown = False
        else:
            args[0].thisown = False
    %}
    
    %template(add ## SBOLClass) sbol::Document::add<SBOLClass>;
    %template(get ## SBOLClass) sbol::Document::get<SBOLClass>;
    %extend sbol::Document
    {
        void add ## SBOLClass(PyObject *list)
        {
            std::vector<sbol:: SBOLClass *> list_of_cds = {};
            if (PyList_Check(list))
            {
                for (int i = 0; i < PyList_Size(list); ++i)
                {
                    PyObject *obj = PyList_GetItem(list, i);
                    sbol:: SBOLClass * cd;
                    if ((SWIG_ConvertPtr(obj,(void **) &cd, $descriptor(sbol:: SBOLClass *),1)) == -1) throw;
                    list_of_cds.push_back(cd);
                }
                $self->add(list_of_cds);
            };        
        }
    }
    
%enddef

/* This macro is used to create a Pythonic interface to object attributes */
%define TEMPLATE_MACRO_3(SBOLClass)
%extend sbol::SBOLClass {

%pythoncode {

    def __getattribute__(self,name):
        sbol_attribute = None
        if is_swig_property(self, name):
            sbol_attribute = object.__getattribute__(self, name)
        elif is_extension_property(self, name):
            sbol_attribute = object.__getattribute__(self, '__dict__')[name]
        if sbol_attribute != None:
            if not 'Owned' in sbol_attribute.__class__.__name__:
                if sbol_attribute.getUpperBound() != '1':
                    return sbol_attribute.getAll()
                else:
                    try:
                        return sbol_attribute.get()
                    except LookupError:
                        return None
                return None
            elif sbol_attribute.getUpperBound() == '1':
                try:
                    return sbol_attribute.get()
                except:
                    return None
        return object.__getattribute__(self, name)

    __setattribute__ = __setattr__
            
    def __setattr__(self,name, value):
        sbol_attribute = None
        if is_swig_property(self, name):
            sbol_attribute = object.__getattribute__(self, name)
        elif is_extension_property(self, name):
            sbol_attribute = object.__getattribute__(self, '__dict__')[name]
        if sbol_attribute != None:
            if not 'Owned' in sbol_attribute.__class__.__name__:
                if value == None:
                    sbol_attribute.clear()
                elif type(value) == list:
                    if sbol_attribute.getUpperBound() == '1':
                        raise TypeError('The ' + sbol_attribute.getTypeURI() + ' property does not accept list arguments')
                    sbol_attribute.clear()
                    for val in value:
                        sbol_attribute.add(val)
                else:
                    sbol_attribute.set(value)
            elif sbol_attribute.getUpperBound() == '1':
                if len(sbol_attribute) > 0:
                    sbol_obj = sbol_attribute.get()
                    doc = sbol_obj.doc
                    sbol_attribute.remove()
                    if not doc:
                        sbol_obj.thisown = True
                    elif not doc.find(sbol_obj.identity):
                        sbol_obj.thisown = True
                if not value == None:
                    sbol_attribute.set(value)
                    value.thisown = False
        else:
            self.__class__.__setattribute__(self, name, value)

    def __repr__(self):
        return self.__class__.__name__
    
}
}
%enddef

// Dynamically type Locations
%extend sbol::OwnedObject<sbol::Location >
{
    PyObject* __getitem__(const std::string uri)
    {
        Location& obj = (Location&)$self->operator[](uri);
        PyObject* py_obj;
        if (obj.type == SBOL_RANGE)
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::Range*), 0 |  0 );
        else if (obj.type == SBOL_CUT)
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::Cut*), 0 |  0 );
        else if (obj.type == SBOL_GENERIC_LOCATION)
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::GenericLocation*), 0 |  0 );
        else
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(&obj), $descriptor(sbol::Location*), 0 |  0 );
        return py_obj;
    }
    
    void __setitem__(const std::string uri, PyObject* py_obj)
    {
        Range* range;
        Cut* cut;
        GenericLocation* genericlocation;
        Location* location;
        Identified* obj;
        
        if ((SWIG_ConvertPtr(py_obj,(void **) &range, $descriptor(sbol::Range *),1)) != -1)
        {
            $self->add((Location&)*range);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)range;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &cut, $descriptor(sbol::Cut *),1)) != -1)
        {
            $self->add((Location&)*cut);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)cut;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &genericlocation, $descriptor(sbol::GenericLocation *),1)) != -1)
        {
            $self->add((Location&)*genericlocation);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)genericlocation;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &location, $descriptor(sbol::Location *),1)) != -1)
        {
            $self->add(*location);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)location;
        }
        else
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Invalid object type for this property");
        if (uri == obj->identity.get() || uri  == obj->displayId.get())
            return;
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot add " + parseClassName(obj->type) + ". The given URIs do not match");
    }
}
    
// Dynamically type Interactions
%extend sbol::OwnedObject<sbol::Interaction >
{
    PyObject* __getitem__(const std::string uri)
    {
        Interaction* obj = &($self->operator[](uri));
        PyObject* py_obj;
        if (dynamic_cast<TranscriptionalRepressionInteraction*>(obj))
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::TranscriptionalRepressionInteraction*), 0 |  0 );
        else if (dynamic_cast<SmallMoleculeInhibitionInteraction*>(obj))
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::SmallMoleculeInhibitionInteraction*), 0 |  0 );
        else if (dynamic_cast<GeneProductionInteraction*>(obj))
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::GeneProductionInteraction*), 0 |  0 );
        else if (dynamic_cast<TranscriptionalActivationInteraction*>(obj))
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::TranscriptionalActivationInteraction*), 0 |  0 );
        else if (dynamic_cast<SmallMoleculeActivationInteraction*>(obj))
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::SmallMoleculeActivationInteraction*), 0 |  0 );
        else
            py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::Interaction*), 0 |  0 );
        return py_obj;
    }

    void __setitem__(const std::string uri, PyObject* py_obj)
    {
        TranscriptionalRepressionInteraction* transcriptionalrepressioninteraction;
        SmallMoleculeInhibitionInteraction* smallmoleculeinhibitioninteraction;
        GeneProductionInteraction* geneproductioninteraction;
        TranscriptionalActivationInteraction* transcriptionalactivationinteraction;
        SmallMoleculeActivationInteraction* smallmoleculeactivationinteraction;
        Interaction* interaction;
        Identified* obj;
        if ((SWIG_ConvertPtr(py_obj,(void **) &transcriptionalrepressioninteraction, $descriptor(sbol::TranscriptionalRepressionInteraction *),1)) != -1)
        {
            $self->add((Interaction&)*transcriptionalrepressioninteraction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)transcriptionalrepressioninteraction;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &smallmoleculeinhibitioninteraction, $descriptor(sbol::SmallMoleculeInhibitionInteraction *),1)) != -1)
        {
            $self->add((Interaction&)*smallmoleculeinhibitioninteraction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)smallmoleculeinhibitioninteraction;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &geneproductioninteraction, $descriptor(sbol::GeneProductionInteraction *),1)) != -1)
        {
            $self->add((Interaction&)*geneproductioninteraction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)geneproductioninteraction;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &transcriptionalactivationinteraction, $descriptor(sbol::TranscriptionalActivationInteraction *),1)) != -1)
        {
            $self->add((Interaction&)*transcriptionalactivationinteraction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)transcriptionalactivationinteraction;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &smallmoleculeactivationinteraction, $descriptor(sbol::SmallMoleculeActivationInteraction *),1)) != -1)
        {
            $self->add((Interaction&)*smallmoleculeactivationinteraction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)smallmoleculeactivationinteraction;
        }
        else if ((SWIG_ConvertPtr(py_obj,(void **) &interaction, $descriptor(sbol::Interaction *),1)) != -1)
        {
            $self->add((Interaction&)*interaction);
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            obj = (Identified*)interaction;
        }
        else
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Invalid object type for this property");
        if (uri == obj->identity.get() || uri  == obj->displayId.get())
            return;
        else
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot add " + parseClassName(obj->type) + ". The given URIs do not match");
    }
}
    
// Templates used by subclasses of Location: Range, Cut, and Generic Location
TEMPLATE_MACRO_0(Range);
TEMPLATE_MACRO_0(Cut);
TEMPLATE_MACRO_0(GenericLocation);

// Template used by Measured class
TEMPLATE_MACRO_1(Measurement)

// Templates used in SequenceAnnotation class
TEMPLATE_MACRO_1(Location);
        
// Templates used in Component class
TEMPLATE_MACRO_1(MapsTo);
     
// Templates used in ComponentDefinition class
TEMPLATE_MACRO_1(SequenceConstraint);
TEMPLATE_MACRO_1(SequenceAnnotation);
TEMPLATE_MACRO_1(Component);

// Templates used in Participation class
//%template(listOfURIs) sbol::List<sbol::URIProperty>;

// Templates used in Interaction class
TEMPLATE_MACRO_1(Participation);
        
// ModuleDefinition templates
TEMPLATE_MACRO_1(Module);
TEMPLATE_MACRO_1(Interaction);
TEMPLATE_MACRO_1(FunctionalComponent);
    
// Templates used in Activity class
TEMPLATE_MACRO_1(Association);
TEMPLATE_MACRO_1(Usage);
  
// Templates used in ComponentDerivation class
TEMPLATE_MACRO_1(VariableComponent);

// Templates classes used by Document class
TEMPLATE_MACRO_1(ComponentDefinition);
TEMPLATE_MACRO_1(ModuleDefinition);
TEMPLATE_MACRO_1(Sequence);
TEMPLATE_MACRO_1(Model);
TEMPLATE_MACRO_1(Collection);
TEMPLATE_MACRO_1(Activity);
TEMPLATE_MACRO_1(Plan);
TEMPLATE_MACRO_1(Agent);
TEMPLATE_MACRO_1(Attachment);
TEMPLATE_MACRO_1(Implementation);
TEMPLATE_MACRO_1(CombinatorialDerivation);
TEMPLATE_MACRO_1(Experiment);
TEMPLATE_MACRO_1(ExperimentalData);
TEMPLATE_MACRO_1(Design);
TEMPLATE_MACRO_1(Build);
TEMPLATE_MACRO_1(Test);
TEMPLATE_MACRO_1(Analysis);
TEMPLATE_MACRO_1(SampleRoster);

TEMPLATE_MACRO_2(TopLevel)
TEMPLATE_MACRO_2(ComponentDefinition)
TEMPLATE_MACRO_2(ModuleDefinition)
TEMPLATE_MACRO_2(Sequence)
TEMPLATE_MACRO_2(Model)
TEMPLATE_MACRO_2(Collection)
TEMPLATE_MACRO_2(Activity);
TEMPLATE_MACRO_2(Plan);
TEMPLATE_MACRO_2(Agent);
TEMPLATE_MACRO_2(Attachment);
TEMPLATE_MACRO_2(Implementation);
TEMPLATE_MACRO_2(CombinatorialDerivation);
TEMPLATE_MACRO_2(Experiment);
TEMPLATE_MACRO_2(ExperimentalData);
TEMPLATE_MACRO_2(Design);
TEMPLATE_MACRO_2(Build);
TEMPLATE_MACRO_2(Test);
TEMPLATE_MACRO_2(Analysis);
TEMPLATE_MACRO_2(SampleRoster);
    
TEMPLATE_MACRO_3(SBOLObject)
TEMPLATE_MACRO_3(Identified)
TEMPLATE_MACRO_3(Measurement)
TEMPLATE_MACRO_3(TopLevel)
TEMPLATE_MACRO_3(ComponentDefinition)
TEMPLATE_MACRO_3(SequenceAnnotation)
TEMPLATE_MACRO_3(SequenceConstraint)
TEMPLATE_MACRO_3(Location)
TEMPLATE_MACRO_3(Range)
TEMPLATE_MACRO_3(Cut)
TEMPLATE_MACRO_3(GenericLocation)
TEMPLATE_MACRO_3(ModuleDefinition)
TEMPLATE_MACRO_3(Module)
TEMPLATE_MACRO_3(FunctionalComponent)
TEMPLATE_MACRO_3(Interaction)
TEMPLATE_MACRO_3(Participation)
TEMPLATE_MACRO_3(Component)
TEMPLATE_MACRO_3(MapsTo)
TEMPLATE_MACRO_3(Model)
TEMPLATE_MACRO_3(Sequence)
TEMPLATE_MACRO_3(Collection)
TEMPLATE_MACRO_3(Attachment)
TEMPLATE_MACRO_3(Implementation)
TEMPLATE_MACRO_3(CombinatorialDerivation)
TEMPLATE_MACRO_3(VariableComponent)
TEMPLATE_MACRO_3(Agent)
TEMPLATE_MACRO_3(Plan)
TEMPLATE_MACRO_3(Association);
TEMPLATE_MACRO_3(Usage)
TEMPLATE_MACRO_3(Activity)
TEMPLATE_MACRO_3(Experiment);
TEMPLATE_MACRO_3(ExperimentalData);
TEMPLATE_MACRO_3(Design)
TEMPLATE_MACRO_3(Build)
TEMPLATE_MACRO_3(Test)
TEMPLATE_MACRO_3(Analysis)
TEMPLATE_MACRO_3(SearchQuery);
TEMPLATE_MACRO_3(SampleRoster);
TEMPLATE_MACRO_3(TranscriptionalRepressionInteraction);
TEMPLATE_MACRO_3(SmallMoleculeInhibitionInteraction);
TEMPLATE_MACRO_3(GeneProductionInteraction);
TEMPLATE_MACRO_3(TranscriptionalActivationInteraction);
TEMPLATE_MACRO_3(SmallMoleculeActivationInteraction);
TEMPLATE_MACRO_3(EnzymeCatalysisInteraction);
TEMPLATE_MACRO_3(Document);
    
// Template functions used by PartShop
//%template(pullComponentDefinitionFromCollection) sbol::PartShop::pull < ComponentDefinition > (sbol::Collection& collection);
%template(pullComponentDefinition) sbol::PartShop::pull < ComponentDefinition >;
%template(pullCollection) sbol::PartShop::pull < Collection >;
%template(pullSequence) sbol::PartShop::pull < Sequence >;
//%template(pullDocument) sbol::PartShop::pull < Document >;
%template(countComponentDefinition) sbol::PartShop::count < ComponentDefinition >;
%template(countCollection) sbol::PartShop::count < Collection >;

// Used to create alias properties for FunctionalComponents used in the design-build-test-learn module
%template(AliasedOwnedFunctionalComponent) sbol::AliasedProperty<sbol::FunctionalComponent >;

    
%include "assembly.h"
    
%extend sbol::ComponentDefinition
{
    
    void assemble(PyObject *list, PyObject *doc)
    {
        sbol::Document* cpp_doc;
        if ((SWIG_ConvertPtr(doc,(void **) &cpp_doc, $descriptor(sbol::Document*),1)) == -1)
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Second argument must be a valid Document");
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = convert_list_to_cdef_vector(list);
        if (list_of_cdefs.size())
        {
            $self->assemble(list_of_cdefs, *cpp_doc);
            return;
        }
        return;
    };
    
    void assemble(PyObject *list)
    {
        std::vector<std::string> list_of_display_ids = convert_list_to_string_vector(list);
        if (list_of_display_ids.size())
        {
            $self->assemble(list_of_display_ids);
            return;
        }
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = convert_list_to_cdef_vector(list);
        if (list_of_cdefs.size())
        {
            $self->assemble(list_of_cdefs);
            return;
        }
        return;
    }
    
    void assemblePrimaryStructure(PyObject *list, std::string assembly_standard = "")
    {
        std::vector<std::string> list_of_display_ids = convert_list_to_string_vector(list);
        if (list_of_display_ids.size())
        {
            $self->assemblePrimaryStructure(list_of_display_ids, assembly_standard);
            return;
        }
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = convert_list_to_cdef_vector(list);
        if (list_of_cdefs.size())
        {
            $self->assemblePrimaryStructure(list_of_cdefs, assembly_standard);
            return;
        }
        return;
    }
    
    
    void assemblePrimaryStructure(PyObject *list, PyObject *doc)
    {        
        sbol::Document* cpp_doc;
        if ((SWIG_ConvertPtr(doc,(void **) &cpp_doc, $descriptor(sbol::Document*),1)) == -1)
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Second argument must be a valid Document");
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = convert_list_to_cdef_vector(list);
        if (list_of_cdefs.size())
        {
            $self->assemblePrimaryStructure(list_of_cdefs, *cpp_doc);
            return;
        }
        return;
    }
    
    void linearize(PyObject *list)
    {
        std::vector<std::string> list_of_display_ids = convert_list_to_string_vector(list);
        if (list_of_display_ids.size())
        {
            $self->linearize(list_of_display_ids);
            return;
        }
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = convert_list_to_cdef_vector(list);
        if (list_of_cdefs.size())
        {
            $self->linearize(list_of_cdefs);
            return;
        }
        return;
    }
    
    
    bool isRegular(PyObject* py_string)
    {
        std::string msg;
        bool IS_REGULAR;
        IS_REGULAR = $self->isRegular(msg);
        py_string = PyUnicode_FromString(msg.c_str());
        return IS_REGULAR;
    };
}
    
%extend sbol::Document
{
    PyObject* getExtensionObject(std::string id)
    {
        // Search the Document's object store for the uri
        if ($self->PythonObjects.find(id) != $self->PythonObjects.end())
        {
            PyObject* py_obj = $self->PythonObjects[id];
            Py_INCREF(py_obj);
            return py_obj;
        }
        else if ($self->SBOLObjects.find(id) != $self->SBOLObjects.end())
        {
            SBOLObject* obj = $self->SBOLObjects[id];
            PyObject *py_obj = SWIG_NewPointerObj(SWIG_as_voidptr(obj), $descriptor(sbol::TopLevel*), 0 |  0 );
            int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
            Py_INCREF(py_obj);
            return py_obj;
        }
        throw SBOLError(NOT_FOUND_ERROR, "Object " + id + " not found");
    }
    
    void addExtensionObject(PyObject* py_obj)
    {
        typedef struct {
            PyObject_HEAD
            void *ptr; // This is the pointer to the actual C++ instance
            void *ty;  // swig_type_info originally, but shouldn't matter
            int own;
            PyObject *next;
        } SwigPyObject;
        
        // Get pointer to wrapped object
        SwigPyObject* swig_py_object = (SwigPyObject*)PyObject_GetAttr(py_obj,  PyUnicode_FromString("this"));
        if (swig_py_object)
        {
            SBOLObject* sbol_obj = (SBOLObject *)swig_py_object->ptr;
            TopLevel* tl = dynamic_cast<TopLevel*>(sbol_obj);
            if (tl)
            {
                tl->doc = $self;
                tl->parent = $self;
                $self->SBOLObjects[sbol_obj->identity.get()] = tl;
                $self->PythonObjects[sbol_obj->identity.get()] = py_obj;
                int check = PyObject_SetAttr(py_obj, PyUnicode_FromString("thisown"), Py_False);
                Py_INCREF(py_obj);
            }
            // Call the add method to recursively add child objects and set their back-pointer to this Document
            for (auto i_store = sbol_obj->owned_objects.begin(); i_store != sbol_obj->owned_objects.end(); ++i_store)
            {
                std::vector<SBOLObject*>& object_store = i_store->second;
                for (auto i_obj = object_store.begin(); i_obj != object_store.end(); ++i_obj)
                {
                    $self->add<SBOLObject>(**i_obj);
                }
            }
        }
        else
            throw SBOLError(SBOL_ERROR_TYPE_MISMATCH, "Not a valid SBOL object");
    }
    
    Document* __iter__()
    {
        $self->python_iter = Document::iterator($self->SBOLObjects.begin());
        return $self;
    }
    
    TopLevel* next()
    {
        if ($self->python_iter != $self->end())
        {
            TopLevel& obj = *self->python_iter;
            $self->python_iter++;
            if ($self->python_iter == $self->end())
            {
                PyErr_SetNone(PyExc_StopIteration);
            }
            return &obj;
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }
    
    TopLevel* __next__()
    {
        if ($self->python_iter != $self->end())
        {
            
            TopLevel& obj = *$self->python_iter;
            $self->python_iter++;
            return &obj;
        }
        
        throw SBOLError(END_OF_LIST, "");;
        return NULL;
    }
    
    int __len__()
    {
        return $self->size();
    }

    void readString(char * str)
    {
        string s = string(str);
        $self->readString(s);
    }
    
}

    
%extend sbol::ModuleDefinition
{
    void assemble(PyObject *list)
    {
        std::vector<sbol::ModuleDefinition*> list_of_mdefs = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::ModuleDefinition* md;
                if ((SWIG_ConvertPtr(obj,(void **) &md, $descriptor(sbol::ModuleDefinition*),1)) == -1) throw;
                list_of_mdefs.push_back(md);
            }
            $self->assemble(list_of_mdefs);
        };
    }
}

%extend sbol::SearchQuery
{
    sbol::TextProperty __getitem__(std::string uri)
    {
        return $self->operator[](uri);
    }
    
}

%extend sbol::SearchResponse
{
    sbol::Identified& __getitem__(int i)
    {
        return $self->operator[](i);
    }
    
    int __len__()
    {
        return $self->size();
    }
    
    SearchResponse* __iter__()
    {
        $self->python_iter = SearchResponse::iterator($self->begin());
        return $self;
    }

    Identified* next()
    {
        if ($self->size() == 0)
            throw SBOLError(END_OF_LIST, "");
        if ($self->python_iter != $self->end())
        {
            Identified* obj = *$self->python_iter;
            $self->python_iter++;

            return obj;
        }
        if ($self->python_iter == $self->end())
        {
            PyErr_SetNone(PyExc_StopIteration);
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }

    Identified* __next__()
    {
        if ($self->python_iter != $self->end())
        {
            
            Identified* obj = *$self->python_iter;
            $self->python_iter++;
            
            return obj;
        }
        
        throw SBOLError(END_OF_LIST, "");;
        return NULL;
    }
}

%extend sbol::ComponentDefinition {
    %pythoncode %{
        
    def getPrimaryStructureComponents(self):
        subcomponents = []
        if len(self.components) == 1:
            subcomponents.append(self.components[0])
        else:
            # Check if this is a complete primary structure (note this isn't a perfect test)
            if len(self.sequenceConstraints) != (len(self.components) - 1):
                raise ValueError('ComponentDefinition <%s> does not appear to describe a complete primary structure ' \
                                 'It appears to be missing SequenceConstraints.' %self.identity)

            c_first = self.getFirstComponent()
            subcomponents.append(c_first)
            c_next = c_first;
            while self.hasDownstreamComponent(c_next):
                c_next = self.getDownstreamComponent(c_next)
                subcomponents.append(c_next)
        return subcomponents

    def assemble(self, component_list, assembly_method=None, doc=None):
        '''
        Due to the recursive nature of this routine, it is hard to completely validate that all the necessary
        preconditions for successful execution are met prior to execution.  That means if a call fails, it may result
        in a modified and incomplete data structure that will be difficult to fix when the user is working interactively
        in the interpreter
        '''
        if not Config.getOption('sbol_compliant_uris'):
            raise EnvironmentError('Assemble method requires SBOL-compliance enabled')

        # Validate doc
        if not self.doc and not doc:
            raise ValueError('Missing doc argument. If the ComponentDefinition does not belong to a Document, ' \
                             'a target Document must be specified using the doc keyword argument.')
        if doc and self.doc != doc:
            raise ValueError('Invalid doc argument. Do not use the doc keyword argument if the ComponentDefinition ' \
                             'already belongs to a Document')

        # Validate component_list
        doc = doc if doc else self.doc
        if isinstance(component_list, list) and all(isinstance(c, ComponentDefinition) \
                                                    for c in component_list):
            for cdef in component_list:
                if cdef.doc and cdef.doc.this != doc.this:
                    raise ValueError('Invalid component_list specified. Assembly subcomponents cannot ' \
                                     'belong to a different Document than the calling object.')
        elif isinstance(component_list, list) and all(isinstance(c, str) \
                                                      for c in component_list):
            component_identities = component_list[:]
            component_list = []
            for c_id in component_identities:
                if not c_id in doc.componentDefinitions:
                    raise ValueError('Invalid component_list specified. ComponentDefinition <%s> not found.' \
                                     %c_id)
                cdef = doc.componentDefinitions[c_id]
                component_list.append(cdef)
        else:
            raise TypeError('Invalid component_list specified. Please provide a list of ' \
                            'ComponentDefinitions or, alternatively, a list of ComponentDefinition' \
                            'displayIds')

        if not self.doc:
            doc.addComponentDefinition(self)
        for cdef in component_list:
            if not cdef.doc:
                self.doc.addComponentDefinition(cdef)
                
        if assembly_method:
            component_list = assembly_method(component_list)
            if not all(type(c) is ComponentDefinition for c in component_list):
                raise TypeError('Invalid callback specified for assembly_method. The callback must return a list ' \
                                'of ComponentDefinitions')
                           
        # Instantiate a Component for each ComponentDefinition in the list
        instance_list = []
        for cdef in component_list:
            
            # Generate URI of new Component.  Check if an object with that URI is already instantiated.
            instance_count = 0
            component_id = self.persistentIdentity + "/" + cdef.displayId + "_" + str(instance_count) + \
                           "/" + self.version
            while self.find(component_id):
                # Find the last instance assigned
                instance_count += 1
                component_id = self.persistentIdentity + "/" + cdef.displayId + "_" + str(instance_count) + \
                               "/" + self.version
            
            c = self.components.create(cdef.displayId + "_" + str(instance_count))
            c.definition = cdef.identity
            instance_list.append(c)
        return component_list
    
    def assemblePrimaryStructure(self, primary_structure, assembly_method=None, doc=None):
                           
        primary_structure = self.assemble(primary_structure, assembly_method, doc)

        # If user specifies a list of IDs rather than ComponentDefinitions, convert to list of ComponentDefinitions
        # (Some parameter validation is done by the preceding call to ComponentDefinition.assemble)
        doc = doc if doc else self.doc
        if all(isinstance(c, str) for c in primary_structure):
            component_identities = primary_structure[:]
            primary_structure = []
            for c_id in component_identities:
                cdef = doc.componentDefinitions[c_id]
                primary_structure.append(cdef)
                    
        self.types += [SO_LINEAR]

        
        component_map = {}
        for c in self.components:
            if not c.definition in component_map:
                component_map[c.definition] = [c]
            else:
                component_map[c.definition].append(c)
        primary_structure_components = []
        for cd in primary_structure:
            primary_structure_components.append(component_map[cd.identity].pop())
            
        # Iterate pairwise through the primary_structure, and place SequenceConstraints between adjacent
        # ComponentDefinitions.
        if len(self.sequenceConstraints):
            self.sequenceConstraints.clear()
        for upstream, downstream in zip(primary_structure_components[:-1], primary_structure_components[1:]):
            instance_count = 0
            constraint_id = 'constraint_%d' %instance_count
            while constraint_id in self.sequenceConstraints:
                instance_count += 1
                constraint_id = 'constraint_%d' %instance_count
            sc = self.sequenceConstraints.create(constraint_id)
            sc.subject = upstream
            sc.object = downstream
            sc.restriction = SBOL_RESTRICTION_PRECEDES
                
    def compile(self, assembly_method = None):
        if not self.doc:
            raise ValueError('Cannot compile <%s>. The ComponentDefinition must belong to a Document ' \
                             'in order to compile.' %self.identity)

        if not self.sequence:
            if Config.getOption('sbol_compliant_uris'):
                display_id = self.displayId
                if not Config.getOption('sbol_typed_uris'):
                    display_id += '_seq'
                seq = self.doc.sequences.create(display_id)
                self.sequence = seq
                self.sequences = seq.identity
            else:
                seq = self.sequences.create(self.identity + '_seq')
                self.sequence = seq
                self.sequences = seq.identity

        return self.sequence.compile(assembly_method = assembly_method)
    %}
};
    
%extend sbol::Sequence {
    %pythoncode %{
        def compile(self, composite_sequence = '', assembly_method = None):
            if not self.doc:
                raise ValueError('Cannot compile Sequence <%s>. The Sequence must belong to a Document ' \
                                 'in order to compile.' %self.identity)

            # Search for the parent ComponentDefinition to which this Sequence belongs
            parent_cdef = None
            for cd in self.doc.componentDefinitions:
                if cd.sequence and cd.sequence.identity == self.identity:
                    parent_cdef = cd
                    break
        
            if not parent_cdef:
                raise ValueError('Cannot compile Sequence <%s>. The Sequence must be associated ' \
                                 'with a ComponentDefinition in order to compile.' %self.identity)

            if len(parent_cdef.components) == 0:
                if parent_cdef.sequence.elements:
                    return parent_cdef.sequence.elements
                else:
                    return ''  # Maybe this should raise an Exception ?
                    
            elif len(parent_cdef.components) > 0:
                # Recurse into subcomponents and assemble their sequence
                composite_sequence_initial_size = len(composite_sequence)
                    
                subcomponents = parent_cdef.getPrimaryStructureComponents()
                for c in subcomponents:
                    cdef = self.doc.getComponentDefinition(c.definition)
                    if not cdef.sequence:
                        if Config.getOption('sbol_compliant_uris'):
                            seq = self.doc.sequences.create(cdef.displayId)
                            cdef.sequence = seq
                            cdef.sequences = seq.identity
                        else:
                            seq = self.doc.sequences.create(cdef.identity+ '_seq')
                            cdef.sequence = seq
                            cdef.sequences = seq.identity
                    seq = cdef.sequence
                    
                    # Check for regularity -- only one SequenceAnnotation per Component is allowed
                    sequence_annotations = parent_cdef.find_property_value(SBOL_COMPONENT_PROPERTY, c.identity)
                    sequence_annotations = [o.cast(SequenceAnnotation) for o in sequence_annotations]
                    if len(sequence_annotations) > 1:
                        raise ValueError('Cannot compile Sequence. Component <%s> is irregular. ' \
                                         'More than one SequenceAnnotation is associated with ' \
                                         'this Component' %c.identity)
                            
                    # Auto-construct a SequenceAnnotation for this Component if one doesn't already exist
                    if len(sequence_annotations) == 0:
                        sa_instance = 0
                        sa_id = cdef.displayId if Config.getOption('sbol_compliant_uris') else cdef.identity
                        sa_id += '_annotation'
                        sa_uri = '%s/%s_%d/%s' %(parent_cdef.persistentIdentity, sa_id, sa_instance, cdef.version)
                        while sa_uri in parent_cdef.sequenceAnnotations:
                            sa_instance += 1
                            sa_uri = '%s/%s_%d/%s' %(parent_cdef.persistentIdentity, sa_id, sa_instance, cdef.version)
                        sa = parent_cdef.sequenceAnnotations.create('%s_%d' %(sa_id, sa_instance))
                        sa.component = c
                        sequence_annotations.append(sa)

                    sa = sequence_annotations[0]
                    
                    # Check for regularity -- only one Range per SequenceAnnotation is allowed
                    ranges = []
                    if len(sa.locations):
                        # Look for an existing Range that can be re-used
                        for l in sa.locations:
                            if l.type == SBOL_RANGE:
                                ranges.append(l.cast(Range))
                    else:
                        # Auto-construct a Range
                        range_id = sa.displayId if Config.getOption('sbol_compliant_uris') else sa.identity
                        r = sa.locations.createRange(range_id + '_range')
                        ranges.append(r)
                    if len(ranges) > 1:
                        raise ValueError('Cannot compile Sequence <%s> because SequenceAnnotation <%s> has ' \
                                         'more than one Range.' %(self.identity, sa.identity))

                    r = ranges[0]

                    #if len(parent_cdef.components) == 1:
                    #    r.start = len(composite_sequence) + 1
                    #   r.end = len(composite_sequence) + len(seq.elements)
                    #    #return seq.elements
                    r.start = len(composite_sequence) + 1
                    subsequence = seq.compile(composite_sequence)  # Recursive call
                    if assembly_method:
                        subsequence = assembly_method(subsequence)
                        if not type(subsequence) is str:
                            raise TypeError('Invalid callback specified for assembly_method. The callback must return' \
                                            ' a string.')

                    # If sourceLocation is specified, don't use the entire sequence for the subcomponent
                    if len(c.sourceLocations) == 1:
                        source_loc = c.sourceLocations.getRange()
                        subsequence = subsequence[(source_loc.start - 1):(source_loc.end)]
                    composite_sequence = composite_sequence + subsequence
                    r.end = len(composite_sequence)

                subsequence = composite_sequence[composite_sequence_initial_size:(composite_sequence_initial_size+len(composite_sequence))]
                self.elements = subsequence
                return subsequence;
    %}
};

%extend sbol::Activity {
    %pythoncode %{

    def generateDesign(self, uris, analysis_usages, design_usages = None):
        """


        Generate one or more Design objects  

        Parameters
        ----------
        * `uris` :  
            One or more identifiers for the new Design object(s). If the 
            `sbol_compliant_uris` option configuration is enabled, then the user 
            should specify simple identifiers for the objects. Otherwise the user 
            must provide full URIs each consisting of a scheme, namespace, and identifier. 
        * `analysis_usages` :  
            A singleton Analysis object, list of Analysis objects, or None. Analysis usages
            represent a prediction or forward-specification of the new Design's intended 
            structure or function.  
        * `design_usages` :  
            A singleton Design object, list of Design objects, or None. Design usages may 
            represent previous Designs that are being tranformed or composed into 
            the new Design.

        Returns
        -------
        A singleton Design or list of Designs depending on whether the user specifies
        a single URI or list of URIs.  

        """

        self.__validate_activity__(SBOL_DESIGN)
        if type(uris) != list:
            uris = [ uris ]
        for uri in uris:
            if type(uri) != str:
                raise TypeError('Cannot generate Design. The first argument must be a string or list of strings')
        if len(uris) != len(set(uris)):
            raise ValueError('Cannot generate Design. The first argument cannot contain duplicate values')

        try:
            analysis_usages = self.__validate_usages__(analysis_usages, Analysis)
        except TypeError:
            raise TypeError('Cannot generate Design. The second argument must be an Analysis or list of Analyses')
        
        try:
            design_usages = self.__validate_usages__(design_usages, Design)
        except TypeError:
            raise TypeError('Cannot generate Design. The third argument must be a Design or list of Designs')

        if not len(analysis_usages) and not len(design_usages):
            raise ValueError('Cannot generate Design. User must specify usages of either Analysis or Design type')

        new_designs = []
        for uri in uris:            
            new_design = self.doc.designs.create(uri)
            new_design.wasGeneratedBy = self.identity
            if len(analysis_usages):
                new_design.specification = analysis_usages[0]
            new_designs.append(new_design)

        self.__create_usages__(analysis_usages)
        self.__create_usages__(design_usages)

        if len(new_designs) > 1:
            return new_designs
        else:
            return new_designs[0]

    def generateBuild(self, uris, design_usages, build_usages = None):
        """


        Generate one or more Build objects  

        Parameters
        ----------
        * `uris` :  
            One or more identifiers for the new Build object(s). If the 
            `sbol_compliant_uris` option configuration is enabled, then the user 
            should specify simple identifiers for the objects. Otherwise the user 
            must provide full URIs each consisting of a scheme, namespace, and identifier. 
        * `design_usages` :  
            A singleton Design object, list of Design objects, or None. Design usages represent
            the engineer's intent or "blueprint" for the Build target. 
        * `build_usages` :  
            A singleton Build object, list of Build objects, or None. Build usages
            represent physical components, such as laboratory samples, that are assembled
            into the target Build.  

        Returns
        -------
        A singleton Build or list of Builds depending on whether the user specifies
        a single URI or list of URIs.  

        """
        self.__validate_activity__(SBOL_BUILD)
        if type(uris) != list:
            uris = [ uris ]

        for uri in uris:
            if type(uri) != str:
                raise TypeError('Cannot generate Build. The first argument must be a string or list of strings')
        if len(uris) != len(set(uris)):
            raise ValueError('Cannot generate Build. The first argument cannot contain duplicate values')

        try:
            design_usages = self.__validate_usages__(design_usages, Design)
        except TypeError:
            raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
        
        try:
            build_usages = self.__validate_usages__(build_usages, Build)
        except TypeError:
            raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

        if not len(design_usages) and not len(build_usages):
            raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

        new_builds = []
        for uri in uris:
            new_build = self.doc.builds.create(uri)
            new_build.wasGeneratedBy = self.identity
            if len(design_usages):
                new_build.design = design_usages[0]
            new_builds.append(new_build)

        self.__create_usages__(design_usages)
        self.__create_usages__(build_usages)
        
        if len(new_builds) > 1:
            return new_builds
        else:
            return new_builds[0]


    def generateTest(self, uris, build_usages, test_usages = None):
        """


        Generate one or more Test objects  

        Parameters
        ----------
        * `uris` :  
            One or more identifiers for the new Test object(s). If the 
            `sbol_compliant_uris` option configuration is enabled, then the user 
            should specify simple identifiers for the objects. Otherwise the user 
            must provide full URIs each consisting of a scheme, namespace, and identifier. 
        * `build_usages` :  
            A singleton Build object, list of Build objects, or None. Build usages represent
            samples or analytes used in an experimental measurement.
        * `test_usages` :  
            A singleton Test object, list of Test objects, or None. Test usages
            represent other measurements or raw data that the user wants to integrate into
            a single data set.
        
        Returns
        -------
        A singleton Test or list of Tests depending on whether the user specifies
        a single URI or list of URIs.  

        """
        self.__validate_activity__(SBOL_TEST)

        if type(uris) != list:
            uris = [ uris ]
        for uri in uris:
            if type(uri) != str:
                raise TypeError('Cannot generate Test. The first argument must be a string or list of strings')
        if len(uris) != len(set(uris)):
            raise ValueError('Cannot generate Test. The first argument cannot contain duplicate values')

        if type(build_usages) == SampleRoster:
            build_usages = [ build_usages ]
        else:
            try:
                build_usages = self.__validate_usages__(build_usages, Build)
            except TypeError:
                raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
        
        try:
            test_usages = self.__validate_usages__(test_usages, Test)
        except TypeError:
            raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

        if not len(build_usages) and not len(test_usages):
            raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

        new_tests = []
        for uri in uris:
            new_test = self.doc.tests.create(uri)
            new_test.wasGeneratedBy = self.identity
            if len(build_usages):
                new_test.samples = build_usages
            new_tests.append(new_test)

        self.__create_usages__(build_usages)
        self.__create_usages__(test_usages)
        if len(new_tests) > 1:
            return new_tests
        else:
            return new_tests[0]

    def generateAnalysis(self, uris, test_usages, analysis_usages = None):
        """


        Generate one or more Analysis objects.

        Parameters
        ----------
        * `uris` :  
            One or more identifiers for the new Analysis object(s). If the 
            `sbol_compliant_uris` option configuration is enabled, then the user 
            should specify simple identifiers for the objects. Otherwise the user 
            must provide full URIs each consisting of a scheme, namespace, and identifier. 
        * `test_usages` :  
            A singleton Test object, list of Test objects, or None. Test usages represent
            raw experimental data used to generate an Analysis.
        * `analysis_usages` :  
            A singleton Analysis object, list of Analysis objects, or None. Analysis usages
            represent other analyses that the user wants to integrate into
            a single data set or data sheet.

        Returns
        -------
        A singleton Analysis or list of Analyses depending on whether the user specifies
        a single URI or list of URIs.

        """
        self.__validate_activity__(SBOL_TEST)

        if type(uris) != list:
            uris = [ uris ]
        for uri in uris:
            if type(uri) != str:
                raise TypeError('Cannot generate Analysis. The first argument must be a string or list of strings')
        if len(uris) != len(set(uris)):
            raise ValueError('Cannot generate Analysis. The first argument cannot contain duplicate values')

        try:
            test_usages = self.__validate_usages__(test_usages, Test)
        except TypeError:
            raise TypeError('Cannot generate Build. The second argument must be a Design or list of Designs')
        
        try:
            analysis_usages = self.__validate_usages__(analysis_usages, Analysis)
        except TypeError:
            raise TypeError('Cannot generate Build. The third argument must be a Design or list of Designs')

        if not len(test_usages) and not len(analysis_usages):
            raise ValueError('Cannot generate Build. User must specify usages of either Design or Build type')

        new_analyses = []
        for uri in uris:
            new_analysis = self.doc.analyses.create(uri)
            new_analysis.wasGeneratedBy = self.identity
            if len(test_usages):
                new_analysis.rawData = test_usages[0]
            new_analyses.append(new_analysis)

        self.__create_usages__(test_usages)
        self.__create_usages__(analysis_usages)
        if len(new_analyses) > 1:
            return new_analyses
        else:
            return new_analyses[0]

    def __validate_activity__(self, activity_type):
        if not self.doc : raise ValueError('Failed to generate. This Activity must first be added to a Document')
        if len(self.associations):
            for a in self.associations:
                if not a.agent: 
                    raise ValueError('Failed to generate. This Activity does not specify an Agent')
                if not a.plan:
                    raise ValueError('Failed to generate. This Activity does not specify a Plan')
            for a in self.associations:
                a.roles = activity_type 
        else:
            raise ValueError('Failed to generate. This Activity does not specify an Agent or Plan')

    def __validate_usages__(self, usage_list, UsageType):
        if usage_list == None:
            usage_list = []
        elif type(usage_list) != list:
            usage_list = [ usage_list ]
        for u in usage_list:
            if not type(u) == UsageType:
                raise TypeError()
        return usage_list       

    def __create_usages__(self, usage_list):
        
        usage_map = \
        {
            Design : SBOL_URI + "#design",
            Build : SBOL_URI + "#build",
            Test : SBOL_URI + "#test",
            Analysis : SBOL_URI + "#learn",
            SampleRoster : SBOL_URI + "#build"
        }

        for u in usage_list:
            if not u.doc:
                if type(u == Design):
                    self.doc.addDesign(u)
                if type(u == Build):
                    self.doc.addBuild(u)
                elif type(u == Test):
                    self.doc.addTest(u)
                elif type(u == Analysis):
                    self.doc.addAnalsis(u)
                elif type(u == SampleRoster):
                    self.doc.addTest(u)
            if Config.getOption('sbol_compliant_uris') == 'True':
                id = u.displayId
            else:
                id = u.identity
            U = self.usages.create(id + '_usage');
            U.entity = u.identity
            U.roles = usage_map[type(u)]
    %}
};

%extend sbol::PartShop {
    %pythoncode %{
    def submit(self, doc, collection='', overwrite=0):
        """
        Submit a SBOL Document to SynBioHub
        :param doc: The Document to submit
        :param collection: The URI of a SBOL Collection to which the Document
        contents will be uploaded
        :param overwrite: An integer code: '0' prevent, '1' overwrite,
            '2' merge and prevent, '3' merge and overwrite
        :return: the HTTP response object
        """
        if collection == '':
            # If a Document is submitted as a new collection,
            # then Document metadata must be specified
            if not (doc.displayId and doc.name and doc.description):
                raise ValueError('Cannot submit Document. The Document must be '
                                 'assigned a displayId, name, and ' +
                                 'description for upload.')
        else:
            if self.getSpoofedURL() != '' and self.getURL() in collection:
                # Correct collection URI in case a spoofed resource is being used
                collection = collection.replace(self.getURL(),
                                                self.getSpoofedURL())
                if Config.getOption('verbose') is True:
                    self.logger.info('Submitting Document to an existing collection: ' + collection)
        # if Config.getOption(ConfigOptions.SERIALIZATION_FORMAT.value) == 'rdfxml':
        #     self.addSynBioHubAnnotations(doc)
        files = {}
        if doc.displayId:
            files['id'] = (None, doc.displayId)
        if doc.version:
            files['version'] = (None, doc.version)
        if doc.name:
            files['name'] = (None, doc.name)
        if doc.description:
            files['description'] = (None, doc.description)
        citations = ''
        for citation in doc.citations:
            citations += citation + ','
        citations = citations[0:-1]  # chop off final comma
        files['citations'] = (None, citations)
        keywords = ''
        for kw in doc.keywords:
            keywords += kw + ','
        keywords = keywords[0:-1]
        files['keywords'] = (None, keywords)
        files['overwrite_merge'] = (None, str(overwrite))
        files['user'] = (None, self.getKey())
        files['file'] = ('file', doc.writeString(), 'text/xml')

        
        collection_instance = None
        if collection != '':
            files['rootCollections'] = (None, collection)
            
            # When uploading to a Collection, if the same Collection
            # exists in the submission Document, it can result in duplicate Collections.
            # Removing the Collection first will prevent that
            if collection in doc.collections:
                collection_instance = doc.collections.remove(collection)
                
        # Send POST request
        response = requests.post(self.getURL() + '/submit',
                                 files=files,
                                 headers={'Accept': 'text/plain',
                                     'X-authorization': self.getKey()})
        
        if collection_instance:
            doc.collections.add(collection_instance)
            
        if response:
            return response
        elif response.status_code == 401:
            raise HTTPError('You must login with valid credentials '
                            'before submitting')
        else:
            raise HTTPError('HTTP post request failed with: ' +
                            str(response.status_code) +
                            ' - ' + str(response.content))
    %}
};

%pythonbegin %{
from __future__ import absolute_import
import json
import requests
from urllib3.exceptions import HTTPError
%}
    
%pythoncode
%{
    class InsertionError(Exception):
        pass

    def IGEM_STANDARD_ASSEMBLY(parts_list):
        if not all(type(part) is ComponentDefinition for part in parts_list):
            raise TypeError()
        doc = parts_list[0].doc
        G0000_uri = 'https://synbiohub.org/public/igem/BBa_G0000/1'
        G0000_seq_uri = 'https://synbiohub.org/public/igem/BBa_G0000_sequence/1'
        G0002_uri = 'https://synbiohub.org/public/igem/BBa_G0002/1'
        G0002_seq_uri = 'https://synbiohub.org/public/igem/BBa_G0002_sequence/1'
        if not (G0000_uri in doc.componentDefinitions and G0002_uri in doc.componentDefinitions and G0000_seq_uri \
                in doc.sequences and G0002_seq_uri in doc.sequences):
            doc.readString('''<?xml version="1.0" encoding="utf-8"?>
                       <rdf:RDF xmlns:dc="http://purl.org/dc/elements/1.1/"
                       xmlns:dcterms="http://purl.org/dc/terms/"
                       xmlns:gbconv="http://sbols.org/genBankConversion#"
                       xmlns:genbank="http://www.ncbi.nlm.nih.gov/genbank#"
                       xmlns:igem="http://wiki.synbiohub.org/wiki/Terms/igem#"
                       xmlns:ncbi="http://www.ncbi.nlm.nih.gov#"
                       xmlns:obo="http://purl.obolibrary.org/obo/"
                       xmlns:om="http://www.ontology-of-units-of-measure.org/resource/om-2/"
                       xmlns:prov="http://www.w3.org/ns/prov#"
                       xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#"
                       xmlns:rdfs="http://www.w3.org/2000/01/rdf-schema#"
                       xmlns:sbh="http://wiki.synbiohub.org/wiki/Terms/synbiohub#"
                       xmlns:sbol="http://sbols.org/v2#"
                       xmlns:sybio="http://www.sybio.ncl.ac.uk#"
                       xmlns:synbiohub="http://synbiohub.org#"
                       xmlns:xsd="http://www.w3.org/2001/XMLSchema#dateTime/">
                       <sbol:ComponentDefinition rdf:about="https://synbiohub.org/public/igem/BBa_G0000/1">
                       <dc:creator>Reshma Shetty</dc:creator>
                       <dcterms:created>2007-07-22T11:00:00Z</dcterms:created>
                       <dcterms:description>SpeI/XbaI scar for RBS-CDS junctions</dcterms:description>
                       <dcterms:modified>2015-08-31T04:07:27Z</dcterms:modified>
                       <dcterms:title>scar</dcterms:title>
                       <sbol:displayId>BBa_G0000</sbol:displayId>
                       <sbol:persistentIdentity rdf:resource="https://synbiohub.org/public/igem/BBa_G0000"/>
                       <sbol:role rdf:resource="http://identifiers.org/so/SO:0000110"/>
                       <sbol:role rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#partType/DNA"/>
                       <sbol:sequence rdf:resource="https://synbiohub.org/public/igem/BBa_G0000_sequence/1"/>
                       <sbol:type rdf:resource="http://www.biopax.org/release/biopax-level3.owl#DnaRegion"/>
                       <sbol:version>1</sbol:version>
                       <igem:discontinued>false</igem:discontinued>
                       <igem:dominant>true</igem:dominant>
                       <igem:experience rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#experience/None"/>
                       <igem:group_u_list>_41_</igem:group_u_list>
                       <igem:m_user_id>0</igem:m_user_id>
                       <igem:owner_id>126</igem:owner_id>
                       <igem:owning_group_id>162</igem:owning_group_id>
                       <igem:sampleStatus>Not in stock</igem:sampleStatus>
                       <igem:status rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#status/Unavailable"/>
                       <sbh:bookmark>false</sbh:bookmark>
                       <sbh:mutableDescription>This is the sequence of the SpeI/XbaI scar for RBS-CDS junctions in BioBricks standard assembly.</sbh:mutableDescription>
                       <sbh:mutableNotes>This is a shorter scar to ensure proper spacing between the RBS and CDS.</sbh:mutableNotes>
                       <sbh:mutableProvenance>SpeI/XbaI scar</sbh:mutableProvenance>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/james"/>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/myers"/>
                       <sbh:star>false</sbh:star>
                       <sbh:topLevel rdf:resource="https://synbiohub.org/public/igem/BBa_G0000/1"/>
                       <prov:wasDerivedFrom rdf:resource="http://parts.igem.org/Part:BBa_G0000"/>
                       <prov:wasGeneratedBy rdf:resource="https://synbiohub.org/public/igem/igem2sbol/1"/>
                       </sbol:ComponentDefinition>
                       <sbol:Sequence rdf:about="https://synbiohub.org/public/igem/BBa_G0000_sequence/1">
                       <sbol:displayId>BBa_G0000_sequence</sbol:displayId>
                       <sbol:elements>tactag</sbol:elements>
                       <sbol:encoding rdf:resource="http://www.chem.qmul.ac.uk/iubmb/misc/naseq.html"/>
                       <sbol:persistentIdentity rdf:resource="https://synbiohub.org/public/igem/BBa_G0000_sequence"/>
                       <sbol:version>1</sbol:version>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/james"/>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/myers"/>
                       <sbh:topLevel rdf:resource="https://synbiohub.org/public/igem/BBa_G0000_sequence/1"/>
                       <prov:wasDerivedFrom rdf:resource="http://parts.igem.org/Part:BBa_G0000"/>
                       <prov:wasGeneratedBy rdf:resource="https://synbiohub.org/public/igem/igem2sbol/1"/>
                       </sbol:Sequence>
                       <sbol:ComponentDefinition rdf:about="https://synbiohub.org/public/igem/BBa_G0002/1">
                       <dc:creator>Reshma Shetty</dc:creator>
                       <dcterms:created>2007-02-26T12:00:00Z</dcterms:created>
                       <dcterms:description>SpeI/XbaI mixed site</dcterms:description>
                       <dcterms:modified>2015-08-31T04:07:27Z</dcterms:modified>
                       <dcterms:title>SX scar</dcterms:title>
                       <sbol:displayId>BBa_G0002</sbol:displayId>
                       <sbol:persistentIdentity rdf:resource="https://synbiohub.org/public/igem/BBa_G0002"/>
                       <sbol:role rdf:resource="http://identifiers.org/so/SO:0000110"/>
                       <sbol:role rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#partType/DNA"/>
                       <sbol:sequence rdf:resource="https://synbiohub.org/public/igem/BBa_G0002_sequence/1"/>
                       <sbol:type rdf:resource="http://www.biopax.org/release/biopax-level3.owl#DnaRegion"/>
                       <sbol:version>1</sbol:version>
                       <igem:discontinued>false</igem:discontinued>
                       <igem:dominant>true</igem:dominant>
                       <igem:experience rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#experience/None"/>
                       <igem:group_u_list>_41_</igem:group_u_list>
                       <igem:m_user_id>0</igem:m_user_id>
                       <igem:owner_id>126</igem:owner_id>
                       <igem:owning_group_id>70</igem:owning_group_id>
                       <igem:sampleStatus>Not in stock</igem:sampleStatus>
                       <igem:status rdf:resource="http://wiki.synbiohub.org/wiki/Terms/igem#status/Unavailable"/>
                       <sbh:bookmark>false</sbh:bookmark>
                       <sbh:mutableDescription>XbaI/SpeI mixed site.  Simply used to aid in entry of parts into the registry.</sbh:mutableDescription>
                       <sbh:mutableNotes>None.</sbh:mutableNotes>
                       <sbh:mutableProvenance>XbaI and SpeI sites</sbh:mutableProvenance>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/james"/>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/myers"/>
                       <sbh:star>false</sbh:star>
                       <sbh:topLevel rdf:resource="https://synbiohub.org/public/igem/BBa_G0002/1"/>
                       <prov:wasDerivedFrom rdf:resource="http://parts.igem.org/Part:BBa_G0002"/>
                       <prov:wasGeneratedBy rdf:resource="https://synbiohub.org/public/igem/igem2sbol/1"/>
                       </sbol:ComponentDefinition>
                       <sbol:Sequence rdf:about="https://synbiohub.org/public/igem/BBa_G0002_sequence/1">
                       <sbol:displayId>BBa_G0002_sequence</sbol:displayId>
                       <sbol:elements>tactagag</sbol:elements>
                       <sbol:encoding rdf:resource="http://www.chem.qmul.ac.uk/iubmb/misc/naseq.html"/>
                       <sbol:persistentIdentity rdf:resource="https://synbiohub.org/public/igem/BBa_G0002_sequence"/>
                       <sbol:version>1</sbol:version>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/james"/>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/myers"/>
                       <sbh:topLevel rdf:resource="https://synbiohub.org/public/igem/BBa_G0002_sequence/1"/>
                       <prov:wasDerivedFrom rdf:resource="http://parts.igem.org/Part:BBa_G0002"/>
                       <prov:wasGeneratedBy rdf:resource="https://synbiohub.org/public/igem/igem2sbol/1"/>
                       </sbol:Sequence>
                       <prov:Activity rdf:about="https://synbiohub.org/public/igem/igem2sbol/1">
                       <dc:creator>Chris J. Myers</dc:creator>
                       <dc:creator>James Alastair McLaughlin</dc:creator>
                       <dcterms:description>Conversion of the iGEM parts registry to SBOL2.1</dcterms:description>
                       <dcterms:title>iGEM to SBOL conversion</dcterms:title>
                       <sbol:displayId>igem2sbol</sbol:displayId>
                       <sbol:persistentIdentity rdf:resource="https://synbiohub.org/public/igem/igem2sbol"/>
                       <sbol:version>1</sbol:version>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/james"/>
                       <sbh:ownedBy rdf:resource="https://synbiohub.org/user/myers"/>
                       <sbh:topLevel rdf:resource="https://synbiohub.org/public/igem/igem2sbol/1"/>
                       <prov:endedAtTime>2017-03-06T15:00:00.000Z</prov:endedAtTime>
                       </prov:Activity>
                       </rdf:RDF>''')

        G0000 = doc.componentDefinitions[G0000_uri]
        G0002 = doc.componentDefinitions[G0002_uri]
        new_parts_list = []
        for upstream, downstream in zip(parts_list[:-1], parts_list[1:]):
            new_parts_list.append(upstream)
            if SO_RBS in upstream.roles and SO_CDS in downstream.roles:
                new_parts_list.append(G0000)
            else:
                new_parts_list.append(G0002)
        new_parts_list.append(downstream)
        return new_parts_list

    def applyToComponentHierarchy(self, callback_fn, user_data):
        # Assumes parent_component is an SBOL data structure of the general form ComponentDefinition(->Component->ComponentDefinition)n where n+1 is an integer describing how many hierarchical levels are in the SBOL structure
        # Look at each of the ComponentDef's SequenceAnnotations, is the target base there?
        if not self.doc:
            raise Exception('Cannot traverse Component hierarchy without a Document')
    
        GET_ALL = True
        component_nodes = []
        if len(self.components) == 0:
            component_nodes.append(self)  # Add leaf components
            if (callback_fn):
                callback_fn(self, user_data)
        else:
            if GET_ALL:
                component_nodes.append(self)  # Add components with children
                if callback_fn:
                    callback_fn(self, user_data)
            for subc in self.components:
                if not self.doc.find(subc.definition):
                    raise Exception(subc.definition + 'not found')
                subcdef = self.doc.getComponentDefinition(subc.definition)
                subcomponents = subcdef.applyToComponentHierarchy(callback_fn, user_data)
                component_nodes.extend(subcomponents)
        return component_nodes

    
    ComponentDefinition.applyToComponentHierarchy = applyToComponentHierarchy

    def applyToModuleHierarchy(self, callback_fn, user_data):
        # Applies the callback to an SBOL data structure of the general form ModuleDefinition(->Module->ModuleDefinition)n where n+1 is an integer describing how many hierarchical levels are in the SBOL structure
        if not self.doc:
            raise Exception('Cannot traverse Module hierarchy without a Document')
    
        GET_ALL = True
        module_nodes = []
        if len(self.modules) == 0:
            module_nodes.append(self)  # Add leaf components
            if (callback_fn):
                callback_fn(self, user_data)
        else:
            if GET_ALL:
                module_nodes.append(self)  # Add components with children
                if callback_fn:
                    callback_fn(self, user_data)
            for subm in self.modules:
                if not self.doc.find(subm.definition):
                    raise Exception(subm.definition + 'not found')
                submdef = self.doc.getModuleDefinition(subm.definition)
                submodules = submdef.applyToModuleHierarchy(callback_fn, user_data)
                module_nodes.extend(submodules)
        return module_nodes

    
    ModuleDefinition.applyToModuleHierarchy = applyToModuleHierarchy
    
    def testSBOL(username = None, password = None, resource = None, spoofed_resource = None):
        """
        Function to test pySBOL API
        """
        import sbol.unit_tests as unit_tests
        unit_tests.runTests(username=username, password=password, resource=resource, spoofed_resource=spoofed_resource)

    def testRoundTrip():
        """
        Function to run test suite for pySBOL
        """
        import sbol.unit_tests as unit_tests
        unit_tests.runRoundTripTests()

    def is_extension_property(obj, name):
        attribute_dict = object.__getattribute__(obj, '__dict__')
        if name in attribute_dict:
            if type(attribute_dict[name]) in [ TextProperty, URIProperty, IntProperty, FloatProperty, ReferencedObject, DateTimeProperty, VersionProperty ] :
                return True
        return False

    def is_swig_property(obj, name):
        swig_attribute_dict = object.__getattribute__(obj, '__swig_getmethods__')
        if name in swig_attribute_dict:
            return True
        return False

    class PythonicInterface(object):

        def __getattribute__(self,name):
            sbol_attribute = None
            if is_swig_property(self, name):
                sbol_attribute = object.__getattribute__(self, name)
            elif is_extension_property(self, name):
                sbol_attribute = object.__getattribute__(self, '__dict__')[name]
            if sbol_attribute != None:
                if not 'Owned' in sbol_attribute.__class__.__name__:
                    if sbol_attribute.getUpperBound() != '1':
                        return sbol_attribute.getAll()
                    else:
                        try:
                            return sbol_attribute.get()
                        except LookupError:
                            return None
                    return None
                elif sbol_attribute.getUpperBound() == '1':
                    try:
                        return sbol_attribute.get()
                    except:
                        return None
            return object.__getattribute__(self, name)

        def __setattr__(self,name, value):
            sbol_attribute = None
            if is_swig_property(self, name):
                sbol_attribute = object.__getattribute__(self, name)
            elif is_extension_property(self, name):
                sbol_attribute = object.__getattribute__(self, '__dict__')[name]
            if sbol_attribute != None:
                if not 'Owned' in sbol_attribute.__class__.__name__:
                    if value == None:
                        sbol_attribute.clear()
                    elif type(value) == list:
                        if sbol_attribute.getUpperBound() == '1':
                            raise TypeError('The ' + sbol_attribute.getTypeURI() + ' property does not accept list arguments')
                        sbol_attribute.clear()
                        for val in value:
                            sbol_attribute.add(val)
                    else:
                        sbol_attribute.set(value)
                elif sbol_attribute.getUpperBound() == '1':
                    if len(sbol_attribute) > 0:
                        sbol_obj = sbol_attribute.get()
                        doc = sbol_obj.doc
                        sbol_attribute.remove()
                        if not doc:
                            sbol_obj.thisown = True
                        elif not doc.find(sbol_obj.identity):
                            sbol_obj.thisown = True
                    if not value == None:
                        sbol_attribute.set(value)
                        value.thisown = False
            else:
                self.__class__.__setattribute__(self, name, value)

            def __repr__(self):
                return self.__class__.__name__
%}
  
%extend sbol::ComponentDefinition {
    %pythoncode %{
 
    def insert(self, cd_to_insert, insert_point, display_id):
        """
        Construct SBOL representing a genetic insert. Inserts cd_to_insert
        into self at insert_point.
        
        This method constructs a new ComponentDefinition that is annotated
        with the original sequence and the inserted sequence such that the
        new DNA sequence can be generated. This method does not generate
        the new sequence itself.
        
        The new sequence is not generated to avoid duplicating very long
        sequences in memory when they are not needed.
        
        """
        
        def autoconstruct_id(sbol_owned_object_property, display_id):
            instance_count = 0
            auto_id = '%s_%d' %(display_id, instance_count)
            while sbol_owned_object_property.find(auto_id):
                instance_count += 1
                auto_id = '%s_%d' %(display_id, instance_count)
                return auto_id
                
        if not self.doc:
            raise ValueError('Insert failed. ComponentDefinition <%s> must be added to a Document before proceeding.' \
                             %self.identity)
        if not cd_to_insert.doc:
            raise ValueError('Insert failed. ComponentDefinition <%s> must be added to a Document before proceeding.' \
                             %cd_to_insert.identity)
        if self.doc.this != cd_to_insert.doc.this:
            raise ValueError('Insert failed. ComponentDefinition <%s> and ComponentDefinition <%s> must belong to ' \
                             'the same Document.' %(self.identity, cd_to_insert.identity))
        if not self.sequence:
            raise ValueError('Insert failed. ComponentDefinition <%s> is not associated with a Sequence. ' \
                             'The sequence property should point to a valid Sequence before proceeding.' %self.identity)
        if not self.sequence.elements:
            raise ValueError('Insert failed. The elements property of Sequence <%s> must be set before proceeding.' \
                             'The sequence property should point to a valid Sequence before proceeding.'
                             %self.sequence.identity)
        if not cd_to_insert.sequence:
            raise ValueError('Insert failed. ComponentDefinition <%s> is not associated with a Sequence. ' \
                             'The sequence property must point to a valid Sequence before proceeding.' \
                             %cd_to_insert.identity)
        if not cd_to_insert.sequence.elements:
            raise ValueError('Insert failed. The elements property of Sequence <%s> must be set before proceeding.' \
                             'The sequence property should point to a valid Sequence before proceeding.'
                             %cd_to_insert.sequence.identity)
            
        orig_len = len(self.sequence.elements)
        insert_len = len(cd_to_insert.sequence.elements)

        # Keep insert_point in bounds
        if insert_point < 1:
            raise ValueError('Insert failed. The insert_point must be a base coordinate equal to or greater than 1')
        if insert_point > orig_len + 1:
            raise ValueError('Insert failed. The insert_point exceeds the length of the target sequence.')

        cd = ComponentDefinition(display_id)
            
        #sa = cd.sequenceAnnotations.create('%s_sa' %self.displayId)
        #if insert_point > 1:
        #    # If insert point is not at the beginning, construct a range
        #    # that precedes the insert point.
        #    range1 = sa.locations.createRange('%s_r1' %self.displayId)
        #    range1.start = 1
        #    range1.end = insert_point - 1
        #range2 = sa.locations.createRange('%s_r2' %self.displayId)
        #range2.start = insert_point + insert_len
        #range2.end = orig_len + insert_len

        self_comp_0 = None
        if insert_point > 1:
            # Now link myself into the structure of the new
            # ComponentDefinition
            self_comp_0 = cd.components.create('%s_comp_0' %self.displayId)
            self_comp_0.definition = self
            source_loc_0 = self_comp_0.sourceLocations.createRange('%s_r0' %self.displayId)
            source_loc_0.start = 1
            source_loc_0.end = insert_point - 1

        # Now link the insert to the new cd
        insert_comp = cd.components.create('%s_comp' %cd_to_insert.displayId)
        insert_comp.definition = cd_to_insert
        #insert_sa = cd.sequenceAnnotations.create('%s_sa' %cd_to_insert.displayId)

        # Add the range to the insert_sa
        #insert_range = insert_sa.locations.createRange('%s_r1' %cd_to_insert.displayId)
        #insert_range.start = insert_point
        #insert_range.end = insert_point + insert_len - 1

        self_comp_1 = None
        if insert_point <= orig_len:
            self_comp_1 = cd.components.create('%s_comp_1' %self.displayId)
            self_comp_1.definition = self
            source_loc_1 = self_comp_1.sourceLocations.createRange('%s_r1' %self.displayId)
            source_loc_1.start = insert_point
            source_loc_1.end = orig_len

        if self_comp_0:
            sc0 = cd.sequenceConstraints.create('%s_constraint_0' %cd.displayId)
            sc0.subject = self_comp_0
            sc0.object = insert_comp
            sc0.restriction = SBOL_RESTRICTION_PRECEDES
         
        if self_comp_1:
            sc1 = cd.sequenceConstraints.create('%s_constraint_1' %cd.displayId)
            sc1.subject = insert_comp
            sc1.object = self_comp_1
            sc1.restriction = SBOL_RESTRICTION_PRECEDES
            
        self.doc.addComponentDefinition(cd)
        return cd
                    
    def compileInsert(self):
        """Compiles a genetic insert by parsing the SBOL and constructing the
        sequence.

        The layout of self is expected to match the SBOL generated by
        ComponentDefinition.insert().
        """
                    
        def pairwise(ranges):
            pairs = []
            for pair in zip(ranges[:-1], ranges[1:]):
                pairs.append(pair)
            return pairs
            
        def getComponentDefinition(sequence_annotation):
            parent_cd = sequence_annotation.parent.cast(ComponentDefinition)
            component = parent_cd.components[sequence_annotation.component]
            definition_cd = sequence_annotation.doc.getComponentDefinition(component.definition)
            return definition_cd
            
        def getRanges(sequence_annotation):
            for loc in sequence_annotation.locations:
                r = sequence_annotation.locations[loc.identity]
                if isinstance(r, Range):
                    yield r

        #  Self must not already have a sequence
        #     We could also allow self to have a sequence and simply
        #     return so we don't overwrite the sequence.
        if self.sequence is not None:
            raise InsertionError('A sequence already exists.')
                        
        #  There must be at least two annotations
        if len(self.sequenceAnnotations) < 2:
            raise InsertionError('Not enough sequence annotations, need at least 2.')
                            
        #  Two annotations must have a component and have at least one location
        annotations = [a for a in self.sequenceAnnotations
                       if a.component is not None and len(a.locations) > 0]
        if len(annotations) < 2:
            raise InsertionError('Not enough annotations, need at least 2 with a component and a location.')
                                
        # There must be two annotations that have CDs that have non-empty sequences
        annotations = [a for a in annotations if getComponentDefinition(a).sequence
                       and getComponentDefinition(a).sequence.elements]
        if len(annotations) < 2:
            raise InsertionError('Not enough linked ComponentDefinitions have sequences.')
                                    
        # Build a list of tuples. Each tuple is (Range, string), with the
        # string containing a substring of the CD's original
        # sequence. These strings are later joined to create the final
        # sequence with insertion.
        ranges = []
        for a in annotations:
            seq = getComponentDefinition(a).sequence.elements
            aranges = list(getRanges(a))
            
            # We really need to do some work here....
            # We need to verify that the ranges cover the entire sequence,
            if sum([r.length() for r in aranges]) != len(seq):
                msg = 'Insufficient ranges for sequence {}: {}'
                raise InsertionError(msg.format(seq, ['Range({}, {})'.format(r.start, r.end) for r in aranges]))

            # and we should break up the sequence now, while we have the information, to match
            # the ranges. Then all we have to do later is append the strings.
            for r in aranges:
                ranges.append((r, seq[:r.length()]))
                seq = seq[r.length():]
                                                
        # Sort the list of tuples by Range start, then end
        ranges.sort(key=lambda tup: (tup[0].start, tup[0].end))
                                                
        # Verify that the ranges are in proper order, have not gaps and no overlaps.
        for rs1, rs2 in pairwise(ranges):
            r1 = rs1[0]
            r2 = rs2[0]
            # print('R({}, {}) <==> R({}, {})'.format(r1.start, r1.end, r2.start, r2.end))
            if not r1.adjoins(r2):
                raise InsertionError('Ranges are not contiguous')
            if not r1.precedes(r2):
                raise InsertionError('Sorting ranges has failed')
            if r1.overlaps(r2):
                raise InsertionError('Ranges overlap')
                                                                
        # Everything looks good, create the final sequence
        new_seq = ''.join([tup[1] for tup in ranges])

        # Now construct the SBOL object(s) to represent this sequence
        self.sequence = Sequence('%s_seq' %self.displayId, new_seq)
        %}
};
        
        
%extend sbol::EnzymeCatalysisInteraction
{
    EnzymeCatalysisInteraction(std::string uri, ComponentDefinition& enzyme, PyObject* substrates, PyObject* products)
    {
        return new sbol::EnzymeCatalysisInteraction(uri, enzyme, convert_list_to_cdef_vector(substrates), convert_list_to_cdef_vector(products));
    };
    
    EnzymeCatalysisInteraction(std::string uri, ComponentDefinition& enzyme, PyObject* substrates, PyObject* products, PyObject* cofactors, PyObject* sideproducts)
    {
        return new sbol::EnzymeCatalysisInteraction(uri, enzyme, convert_list_to_cdef_vector(substrates), convert_list_to_cdef_vector(products), convert_list_to_cdef_vector(cofactors), convert_list_to_cdef_vector(sideproducts));
    };
}
        
        //%extend sbol::Document
        //{
        //    std::string __getitem__(const int nIndex)
        //    {
        //        return $self->operator[](nIndex);
        //    }
        //
        //    ReferencedObject* __iter__()
        //    {
        //        $self->python_iter = Document::iterator($self->begin());
        //        return $self;
        //    }
        //
        //    std::string next()
        //    {
        //        if ($self->python_iter != $self->end())
        //        {
        //            std::string ref = *$self->python_iter;
        //            $self->python_iter++;
        //            if ($self->python_iter == $self->end())
        //            {
        //                PyErr_SetNone(PyExc_StopIteration);
        //            }
        //            return ref;
        //        }
        //        throw (END_OF_LIST);
        //        return NULL;
        //    }
        //    
        //    int __len__()
        //    {
        //        return $self->size();
        //    }
        //};
        
        

//// The following code was experimented with for mapping C++ class structure to Python class structure
//%pythonappend ComponentDefinition %{
//    name = property(name.set, name.get)
//    %}
//
//%extend sbol::Identified{
//    %pythoncode %{
//        __swig_getmethods__["identity"] = _libsbol.TextProperty.get
//        __swig_setmethods__["identity"] = _libsbol.TextProperty.set
//        if _newclass: identity = property(_libsbol.TextProperty.get, _libsbol.URIProperty.set)
//            %}
//};

//%include "std_unordered_map.i"
//namespace std {
//    %template(_UnorderedMapVector) unordered_map<string, string >;
//    //%template(_UnorderedMapOfStringVector) unordered_map<string, string>;
//}
        
//%include "std_function.i"
//namespace std {
//    %template(_ValidationRule) function<void(void *, void *)>;
//    %template(_ValidationRules) vector<function<void(void *, void *)>>;}
//}
        
//typedef const void(*sbol::ValidationRule)(void *, void *);
// %template(_ValidationRules) std::vector<sbol::ValidationRule>;
        
//%pythonappend sbol::Config::parse_extension_objects()
//%{
//    print ("Parsing extension objects")
//%}
//
//%pythonappend sbol::Config::extension_memory_handler(bool swig_thisown)
//%{
//    print ("Entering memory handler")
//    print (args)
//    self.thisown = args[0]
//%}
        
//%pythonappend sbol::Config::extension_memory_handler(bool swig_thisown)
//%{
//    print ("Entering memory handler")
//    print (args)
//    self.thisown = args[0]
//%}




