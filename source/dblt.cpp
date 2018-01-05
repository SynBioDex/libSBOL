/**
 * @file    dblt.cpp
 * @brief   Methods for Design-Build-Test classes
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
 * ------------------------------------------------------------------------>*/

#include "dblt.h"
#include "document.h"

using namespace std;
using namespace sbol;

namespace sbol
{
//template<>
//void Document::add<Design>(Design& design)
//{
//};

//template < class SBOLClass >
//SBOLClass& TopLevel::generate(std::string uri)
//{
//    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
//        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Generate method requires SBOL-compliance enabled");
//    
//    if (doc == NULL)
//    {
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires the progenitor object belong to a Document.");
//    }
//    
//    SBOLClass& new_obj = *new SBOLClass();
//    
//    // Validate that the generated object is TopLevel
//    if (dynamic_cast<TopLevel*>(&new_obj) == NULL)
//        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid template argument. Generate method must generate a TopLevel object");
//    
//    // If object is TopLevel, intialize the URI
//    std::string persistent_id = getHomespace();
//    if (Config::getOption("sbol_typed_uris").compare("True") == 0)
//        persistent_id += "/" + parseClassName(new_obj->getTypeURI());
//    persistent_id =  persistent_id + "/" + uri;
//    std::string obj_id =  persistent_id + "/" + VERSION_STRING;
//    
//    // Check for uniqueness of URI in the Document
//    if (doc && doc->find(obj_id))
//        throw SBOLError(DUPLICATE_URI_ERROR, "Cannote generate " + obj_id + ". An object with that URI is already in the Document");
//    
//    // Initialize SBOLCompliant properties
//    new_obj->identity.set(obj_id);
//    new_obj->persistentIdentity.set(persistent_id);
//    new_obj->displayId.set(uri);
//    new_obj->version.set(VERSION_STRING);
//    
//    doc->add<SBOLClass>(new_obj);
//    
//    Activity& a = doc->activities.create(new_obj.displayId.get() + "_activity");
//    wasGeneratedBy.set(a.identity.get());
//    wasDerivedFrom.set(this->identity.get());
//    
//    Usage& u = a.qualifiedUsage.create(this->displayId.get() + "_usage");
//    u.entity.set(this->identity.get());
//    return new_obj;
//}

void TopLevel::initialize(std::string uri)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Generate method requires SBOL-compliance enabled");
    
    
    // If object is TopLevel, intialize the URI
    std::string persistent_id = getHomespace();
    if (Config::getOption("sbol_typed_uris").compare("True") == 0)
        persistent_id += "/" + parseClassName(this->getTypeURI());
    persistent_id =  persistent_id + "/" + uri;
    std::string obj_id =  persistent_id + "/" + VERSION_STRING;
    
    // Initialize SBOLCompliant properties
    this->identity.set(obj_id);
    this->persistentIdentity.set(persistent_id);
    this->displayId.set(uri);
    this->version.set(VERSION_STRING);
}

template<>
Build& TopLevel::generate<Build>(std::string uri)
{
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires that the progenitor object belong to a Document.");
    
    if (this->type != SBOL_IMPLEMENTATION && this->type != "http://sys-bio.org#Design")
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Build can only be generated from a Design or Build.");
    
    //    Design& design = *(Design *)this;
    //    if ((design.function.size() == 0) || (design.structure.size() == 0))
    //        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "This Design is not complete. Either its structure or function is unspecified.");
    
    Build& build = *new Build(uri);
    
    std::string id;
    if (Config::getOption("sbol_compliant_uris") == "True")
        id = build.displayId.get();
    else
        id = build.identity.get();
    Activity& a = doc->activities.create(id + "_generation");
    wasGeneratedBy.set(a);
    wasDerivedFrom.set(this->identity.get());  // SBOL provenance linkages are made through the child ModuleDefinition
    
    if (Config::getOption("sbol_compliant_uris") == "True")
        id = this->displayId.get();
    else
        id = this->identity.get();
    Usage& u = a.usages.create(id + "_usage");
    u.entity.set(this->identity.get());
    if (this->type == "http://sys-bio.org#Design")
        u.roles.set(SBOL_URI "#design");
    else
        u.roles.set(SBOL_URI "#build");
    
    if (doc)
        doc->add<Build>(build);
    
    return build;
}
    
template<>
Build& TopLevel::generate<Build>(std::string uri, Plan& plan, std::vector < SBOLObject* > usages)
{
    for (auto & obj : usages)
        if (obj->type != SBOL_IMPLEMENTATION)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Build may only use other Builds for generation");

    Build& build = TopLevel::generate<Build>(uri);
    Activity& a = doc->get<Activity>(build.wasGeneratedBy.get());
    
    std::string id;
    if (Config::getOption("sbol_compliant_uris") == "True")
        id = build.displayId.get();
    else
        id = build.identity.get();
    
    Association& asc = a.associations.create(id + "_generation_association");
    asc.roles.set(SBOL_URI "#build");
    asc.plan.set(plan);
    
    if (Config::getOption("sbol_compliant_uris") == "True")
        id = this->displayId.get();
    else
        id = this->identity.get();
    
    for (auto & obj : usages)
    {
        Usage& u = a.usages.create(id + "_usage");
        u.entity.set(this->identity.get());
        u.roles.set(SBOL_URI "#build");
    }
    return build;
};

    template<>
    Design& OwnedObject<Design>::get(std::string uri)
    {
        
    }

    template<>
    Design& Document::get<Design>(std::string uri)
    {
        
    }
};