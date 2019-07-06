/**
 * @file    dbtl.cpp
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

#include "dbtl.h"
#include "document.h"

#include <tuple>
#include <cctype>

using namespace std;
using namespace sbol;

namespace sbol
{
    // Design::~Design()
    // {
    //     // Remove these properties to prevent double deletion of child objects by the base destructor
    //     // owned_objects.erase(SBOL_COMPONENT_DEFINITION);
    //     // owned_objects.erase(SBOL_MODULE_DEFINITION);
    // }
    
    // Build::~Build()
    // {
    //     // Remove these properties to prevent double deletion of child objects by the base destructor
    //     // owned_objects.erase(SBOL_COMPONENT_DEFINITION);
    //     // owned_objects.erase(SBOL_MODULE_DEFINITION);
    // }
    
    // Analysis::~Analysis()
    // {
    //     // Remove these properties to prevent double deletion of child objects by the base destructor
    //     // owned_objects.erase(SYSBIO_URI "#consensusSequence");
    //     // owned_objects.erase(SYSBIO_URI "#model");
    // }

/* Specialized templates for Design, Build, Test, Analysis workflows */
    
    template<>
    Design& TopLevel::generate<Design>(std::string uri)
    {
        if (Config::getOption("sbol_compliant_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used in SBOL-compliant mode. Use one of the other generate method signatures or use Config::setOption to enable SBOL-compliant URIs");
        
        if (Config::getOption("sbol_typed_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used with SBOL-typed URIs. Use one of the other generate method signatures or use Config::setOption to enable SBOL-typed URIs");
        
        if (doc == NULL)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires that the progenitor object belong to a Document.");
        
        if (this->type != SYSBIO_ANALYSIS && this->type != SYSBIO_DESIGN)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Object " + this->identity.get() + " cannot generate a Design. A Design can only be generated from an Analysis or another Design.");
        
        Design& design = *new Design(uri);
        design.wasDerivedFrom.set(this->identity.get());
        
        
        if (this->type == SYSBIO_ANALYSIS)
            design.characterization.set(this->identity.get());
        else if (this->type == SYSBIO_DESIGN)
        {
            Design& progenitor = *(Design*)this;
            design.characterization.copy(progenitor.characterization);
        }
        
        // Form URI for auto-constructing an Activity
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = design.displayId.get();
        else
            id = design.identity.get();
        
        // Auto-construct Activity
        Activity& a = doc->activities.create(id + "_generation");
        design.wasGeneratedBy.set(a);
        
        // Form URI for auto-constructing a Usage referring to the generating object
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = this->displayId.get();
        else
            id = this->identity.get();
        Usage& u = a.usages.create(id + "_usage");
        u.entity.set(this->identity.get());
        
        // The generated Design may use an Analysis to learn, or else it uses a Design to design, depending on which type of object generated it.
        if (this->type == SYSBIO_ANALYSIS)
            u.roles.add(SBOL_LEARN);
        else
            u.roles.add(SBOL_DESIGN);
        
        doc->add<Design>(design);
        return design;
    }
 
    template<>
    Design& TopLevel::generate<Design>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages)
    {
        for (auto & obj : usages)
            if (obj->type != SYSBIO_ANALYSIS && obj->type != SYSBIO_DESIGN)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid usages argument. A Design may only use other Designs or Analysis objects for generation");

        Design& design = TopLevel::generate<Design>(uri);
        Activity& a = doc->get<Activity>(design.wasGeneratedBy.get());
    
        // Form URI for auto-constructing an Association
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = design.displayId.get();
        else
            id = design.identity.get();
        
        // Auto-construct Association
        Association& asc = a.associations.create(id + "_generation_association");
        asc.roles.set(SBOL_URI "#design");
        asc.agent.set(agent);
        asc.plan.set(plan);
    
        for (auto & usage : usages)
        {
            if (Config::getOption("sbol_compliant_uris") == "True")
                id = usage->displayId.get();
            else
                id = usage->identity.get();
            Usage& u = a.usages.create(id + "_usage");
            u.entity.set(usage->identity.get());
            if (usage->type == SYSBIO_ANALYSIS)
            {
                u.roles.set(SBOL_LEARN);
                design.characterization.add(u);
            }
            else
                u.roles.set(SBOL_DESIGN);
        }
        
        return design;
    };
    
    
    template<>
    Build& TopLevel::generate<Build>(std::string uri)
    {
        if (Config::getOption("sbol_compliant_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used in SBOL-compliant mode. Use one of the other generate method signatures or use Config::setOption to enable SBOL-compliant URIs");
    
        if (Config::getOption("sbol_typed_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used with SBOL-typed URIs. Use one of the other generate method signatures or use Config::setOption to enable SBOL-typed URIs");
    
        if (doc == NULL)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires that the progenitor object belong to a Document.");
    
        // The progenitor object (this) must be a Design or Build
        if (this->type != SBOL_IMPLEMENTATION && this->type != SYSBIO_DESIGN)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Build can only be generated from a Design or another Build.");
    
        Build& build = *new Build(uri);
        build.wasDerivedFrom.set(this->identity.get());
        
        // Set backpointer to the Design object
        if (this->type == SYSBIO_DESIGN)
            build.design.set(this->identity.get());
        else if (this->type == SBOL_IMPLEMENTATION)
        {
            Build& progenitor = *(Build*)this;
            build.design.copy(progenitor.design);
        }
        
        // Form URI for auto-constructing an Activity
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = build.displayId.get();
        else
            id = build.identity.get();
        
        // Auto-construct Activity
        Activity& a = doc->activities.create(id + "_generation");
        build.wasGeneratedBy.set(a);

        // Form URI for auto-constructing a Usage referring to the generating object
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = this->displayId.get();
        else
            id = this->identity.get();
        Usage& u = a.usages.create(id + "_usage");
        u.entity.set(this->identity.get());
        
        // The generated Build may use a Design to design, or else it uses a Build to build, depending on which type of object generated it.
        if (this->type == "http://sys-bio.org#Design")
            u.roles.set(SBOL_URI "#design");
        else
            u.roles.set(SBOL_URI "#build");

        doc->add<Build>(build);
        return build;
    }
    
    template<>
    Build& TopLevel::generate<Build>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages)
    {
        for (auto & obj : usages)
            if (obj->type != SBOL_IMPLEMENTATION)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid usages argument. A Build may only use other Builds for generation");

        Build& build = TopLevel::generate<Build>(uri);
        Activity& a = doc->get<Activity>(build.wasGeneratedBy.get());
    
        // Form URI for auto-constructing an Association
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = build.displayId.get();
        else
            id = build.identity.get();
        
        // Auto-construct an Association
        Association& asc = a.associations.create(id + "_generation_association");
        asc.roles.set(SBOL_URI "#build");
        asc.agent.set(agent);
        asc.plan.set(plan);
    
        for (auto & usage : usages)
        {
            if (Config::getOption("sbol_compliant_uris") == "True")
                id = usage->displayId.get();
            else
                id = usage->identity.get();
            Usage& u = a.usages.create(id + "_usage");
            u.entity.set(usage->identity.get());
            u.roles.set(SBOL_URI "#build");
        }
        return build;
    };
    
    template<>
    Test& TopLevel::generate<Test>(std::string uri)
    {
        if (Config::getOption("sbol_compliant_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used in SBOL-compliant mode. Use one of the other generate method signatures or use Config::setOption to enable SBOL-compliant URIs");
        
        if (Config::getOption("sbol_typed_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used with SBOL-typed URIs. Use one of the other generate method signatures or use Config::setOption to enable SBOL-typed URIs");
        
        if (doc == NULL)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires that the progenitor object belong to a Document.");
        
        // The progenitor object (this) must be a Build, SampleRoster, or a Test
        if (this->type != SBOL_IMPLEMENTATION && this->type != SBOL_COLLECTION)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Test can only be generated from a Build or another Test.");

        // Generate new Test
        Test& test = *new Test(uri);
        test.wasDerivedFrom.set(this->identity.get());

        // Set Test.samples property
        if (properties.find(SYSBIO_URI "#type") != properties.end())
        {
            if (properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_URI "#SampleRoster>")
            {
                // If the progenitor object is a SampleRoster, set samples property to all the members of the roster
                SampleRoster& roster = *(SampleRoster*)this;
                for (auto sample_id : roster.samples)
                    test.samples.add(sample_id);
            }
            else if (properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_BUILD ">")
            {
                // If the progenitor object is a Build, set samples property to the Build
                test.samples.set(this->identity.get());
            }
        }
        else if (this->type == SBOL_TEST)
        {
            // The progenitor object is another Test
            Test& progenitor = *(Test*)this;
            test.samples.copy(progenitor.samples);
        }
        // Form URI for auto-constructing an Activity
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = test.displayId.get();
        else
            id = test.identity.get();
        
        // Auto-construct Activity
        Activity& a = doc->activities.create(id + "_generation");
        test.wasGeneratedBy.set(a);
        
        // Form URI for auto-constructing a Usage referring to the generating object
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = this->displayId.get();
        else
            id = this->identity.get();
        
        Usage& u = a.usages.create(id + "_usage");
        u.entity.set(this->identity.get());
        
        // The generated Build may use a Design to design, or else it uses a Build to build, depending on which type of object generated it.
        if (this->type == SBOL_IMPLEMENTATION)
            u.roles.set(SBOL_URI "#build");
        else
            u.roles.set(SBOL_URI "#test");
 
        doc->add<Test>(test);
        return test;
    }

    template<>
    Test& TopLevel::generate<Test>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages)
    {
        for (auto & obj : usages)
            if (obj->type != SBOL_IMPLEMENTATION && obj->type != SBOL_COLLECTION)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Test may only use Builds or other Tests for generation");

        Test& test = TopLevel::generate<Test>(uri);
        Activity& a = doc->get<Activity>(test.wasGeneratedBy.get());
    
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = test.displayId.get();
        else
            id = test.identity.get();
        Association& asc = a.associations.create(id + "_generation_association");
        asc.roles.set(SBOL_URI "#test");
        asc.agent.set(agent);
        asc.plan.set(plan);
    
        // Check if the progenitor object is a SampleRoster (collection of Builds)
        if (properties.find(SYSBIO_URI "#type") != properties.end())
            if (properties[SYSBIO_URI "#type"].front() == "<" SYSBIO_URI "#SampleRoster>")
            {
                SampleRoster& roster = *(SampleRoster*)this;
                for (auto sample_id : roster.samples)
                {
                    Identified& sample = this->doc->get<Identified>(sample_id);
                    usages.push_back(&sample);
                }
            }

        for (auto & usage : usages)
        {
            if (Config::getOption("sbol_compliant_uris") == "True")
                id = usage->displayId.get();
            else
                id = usage->identity.get();
            Usage& u = a.usages.create(id + "_usage");
            u.entity.set(usage->identity.get());
            if (usage->type == SBOL_IMPLEMENTATION)
            {
                u.roles.set(SBOL_BUILD);
                test.samples.add(u);
            }
            else
                u.roles.set(SBOL_TEST);
        }
        return test;
    };
    
    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri)
    {
        if (Config::getOption("sbol_compliant_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used in SBOL-compliant mode. Use one of the other generate method signatures or use Config::setOption to enable SBOL-compliant URIs");
        
        if (Config::getOption("sbol_typed_uris") != "True")
            throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method signature must only be used with SBOL-typed URIs. Use one of the other generate method signatures or use Config::setOption to enable SBOL-typed URIs");
        
        if (doc == NULL)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Generate method requires that the progenitor object belong to a Document.");
        
        if (this->type != SBOL_COLLECTION && this->type != SYSBIO_ANALYSIS)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "An Analysis can only be generated from a Test or another Analysis.");
        
        Analysis& analysis = *new Analysis(uri);
        analysis.wasDerivedFrom.set(this->identity.get());
        
        if (this->type == SBOL_COLLECTION)
            analysis.rawData.set(this->identity.get());
        else if (this->type == SYSBIO_ANALYSIS)
        {
            Analysis& progenitor = *(Analysis*)this;
            analysis.rawData.copy(progenitor.rawData);
        }
        
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = analysis.displayId.get();
        else
            id = analysis.identity.get();
        Activity& a = doc->activities.create(analysis.displayId.get() + "_generation");
        analysis.wasGeneratedBy.set(a);
        
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = this->displayId.get();
        else
            id = this->identity.get();
        Usage& u = a.usages.create(id + "_usage");
        u.entity.set(this->identity.get());
        if (this->type == SBOL_COLLECTION)
            u.roles.set(SBOL_URI "#test");
        else
            u.roles.set(SBOL_URI "#learn");
        
        doc->add<Analysis>(analysis);
        return analysis;
    }
    
    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages)
    {
        for (auto & obj : usages)
            if (obj->type != SYSBIO_ANALYSIS)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "An Analysis may only use other Analysis objects for generation");
        
        Analysis& analysis = TopLevel::generate<Analysis>(uri);
        Activity& a = doc->get<Activity>(analysis.wasGeneratedBy.get());
        
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = analysis.displayId.get();
        else
            id = analysis.identity.get();
        Association& asc = a.associations.create(id + "_generation_association");
        asc.roles.set(SBOL_URI "#learn");
        asc.agent.set(agent);
        asc.plan.set(plan);
        
        for (auto & usage : usages)
        {
            if (Config::getOption("sbol_compliant_uris") == "True")
                id = usage->displayId.get();
            else
                id = usage->identity.get();
            Usage& u = a.usages.create(id + "_usage");
            u.entity.set(usage->identity.get());
            u.roles.set(SBOL_URI "#learn");
        }
        return analysis;
    };
    
    
    // template<>
    // Design& OwnedObject<Design>::get(std::string uri)
    // {

    // };

    // template<>
    // Design& OwnedObject<Design>::operator[] (std::string uri)
    // {
    // };

    // template<>
    // Design& OwnedObject<Design>::operator[] (const int nIndex)
    // {
    // };

    // template<>
    // Build& OwnedObject<Build>::get(std::string uri)
    // {

    // };

    // template<>
    // Build& OwnedObject<Build>::operator[] (std::string uri)
    // {
    // };

    // template<>
    // Build& OwnedObject<Build>::operator[] (const int nIndex)
    // {
    // };
    
    // template<>
    // Design& Document::get<Design>(std::string uri)
    // {
    //     Design& design = (Design&)get<TopLevel>(uri);
    //     if (!design.structure.size() && design._structure.size())
    //         if (this->find(design._structure.get()))
    //         {
    //             ComponentDefinition& structure = doc->get<ComponentDefinition>(design._structure.get());
    //             design.owned_objects[SBOL_COMPONENT_DEFINITION].push_back(&structure);
    //             // design.structure.set(doc->get<ComponentDefinition>(design._structure.get()));
    //         }
    //     if (!design.function.size() && design._function.size())
    //         if (this->find(design._function.get()))
    //         {
    //             ModuleDefinition& function = doc->get<ModuleDefinition>(design._function.get());
    //             design.owned_objects[SBOL_MODULE_DEFINITION].push_back(&function);
    //             // design.function.set(doc->get<ModuleDefinition>(design._function.get()));
    //         }
    //     return design;
    // }
    
    // template<>
    // Build& Document::get<Build>(std::string uri)
    // {
    //     Build& build = (Build&)get<TopLevel>(uri);
    //     if (!build.structure.size() && build._structure.size())
    //         if (doc->find(build._structure.get()))
    //         {
    //             ComponentDefinition& structure = doc->get<ComponentDefinition>(build._structure.get());
    //             build.owned_objects[SBOL_COMPONENT_DEFINITION].push_back(&structure);
    //             //build.structure.set(doc->get<ComponentDefinition>(build._structure.get()));
    //         }
    //     if (!build.behavior.size() && build._behavior.size())
    //         if (doc->find(build._behavior.get()))
    //         {
    //             ModuleDefinition& behavior = doc->get<ModuleDefinition>(build._behavior.get());
    //             build.owned_objects[SBOL_URI "#built"].push_back(&behavior);
    //             // build.behavior.set(doc->get<ModuleDefinition>(build._behavior.get()));
    //         }
    //     return build;
    // }
    
    // The Build class requires a specialized adder at the Document level. Since its rdf:type is identical to Implementation, it will get added to the Implementation store by default. It must be moved to the Build store.
    template<>
    void Document::add<Build>(Build& sbol_obj)
    {
        // Call recursive adder
        add<Implementation>((Implementation&)sbol_obj);

        // Move from Implementation store to Build store
        this->owned_objects[SBOL_IMPLEMENTATION].pop_back();
        this->owned_objects[SYSBIO_BUILD].push_back(&sbol_obj);

    }

//    template<>
//    void Document::add<Test>(Test& sbol_obj)
//    {
//        // Call recursive adder
//        add<Collection>((Collection&)sbol_obj);
//
//        // Move from Collection store to Test store
//        this->owned_objects[SBOL_COLLECTION].pop_back();
//        this->owned_objects[SYSBIO_TEST].push_back(&sbol_obj);
//    }
    
//    template<>
//    Build& OwnedObject<Build>::get(std::string uri)
//    {
//        
//    }
//
//    template<>
//    Build& OwnedObject<Build>::set(Build& sbol_obj)
//    {
//        
//    }
//
//    template<>
//    Build& OwnedObject<Build>::add(Build& sbol_obj)
//    {
//        
//    }
//    
    template<>
    Build& OwnedObject<Build>::create(std::string uri)
    {
        Build* child_obj = new Build();

        SBOLObject* parent_obj = this->sbol_owner;
        Document* parent_doc = this->sbol_owner->doc;

        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
        {
            string persistent_id = getHomespace();
            if (Config::getOption("sbol_typed_uris").compare("True") == 0)
                persistent_id += "/" + parseClassName(SYSBIO_BUILD);
            string version = VERSION_STRING;
            
            string child_persistent_id =  persistent_id + "/" + uri;
            string child_id = child_persistent_id + "/" + version;
            
            // Check for uniqueness of URI in the Document
            if (parent_doc && parent_doc->find(child_id))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + child_id + " is already in the Document");
                                                      
            // Initialize SBOLCompliant properties
            child_obj->identity.set(child_id);
            child_obj->persistentIdentity.set(child_persistent_id);
            child_obj->displayId.set(uri);
            child_obj->version.set(version);

            // Add the new object to this OwnedObject property
            // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
            child_obj->parent = parent_obj;  // Set back-pointer to parent object
            std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
            object_store.push_back((SBOLObject*)child_obj);

            // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
            if (parent_doc)
            {
                child_obj->doc = parent_doc;
                parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;
            }
            this->validate(child_obj);
            return *child_obj;
        }
        else
        {
            if (parent_doc && parent_doc->find(uri))
                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + uri + " is already in the Document");
            
            // Add the new object to this OwnedObject property
            Identified* parent_obj = (Identified*)this->sbol_owner;
            child_obj->parent = parent_obj;  // Set back-pointer to parent object
            child_obj->identity.set(uri);
            child_obj->persistentIdentity.set(uri);
            
            this->add(*child_obj);
            if (parent_doc)
                child_obj->doc = parent_doc;
            this->validate(child_obj);
            return *child_obj;
        }
    }

//    template<>
//    Test& OwnedObject<Test>::create(std::string uri)
//    {
//        Test* child_obj = new Test();
//
//        SBOLObject* parent_obj = this->sbol_owner;
//        Document* parent_doc = this->sbol_owner->doc;
//
//        if (Config::getOption("sbol_compliant_uris").compare("True") == 0)
//        {
//            string persistent_id = getHomespace();
//            if (Config::getOption("sbol_typed_uris").compare("True") == 0)
//                persistent_id += "/" + parseClassName(SYSBIO_TEST);
//            string version = VERSION_STRING;
//
//            string child_persistent_id =  persistent_id + "/" + uri;
//            string child_id = child_persistent_id + "/" + version;
//
//            // Check for uniqueness of URI in the Document
//            if (parent_doc && parent_doc->find(child_id))
//                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + child_id + " is already in the Document");
//
//            // Initialize SBOLCompliant properties
//            child_obj->identity.set(child_id);
//            child_obj->persistentIdentity.set(child_persistent_id);
//            child_obj->displayId.set(uri);
//            child_obj->version.set(version);
//
//            // Add the new object to this OwnedObject property
//            // this->add(*child_obj);   Can't use this because the add method is prohibited in SBOLCompliant mode!!!
//            child_obj->parent = parent_obj;  // Set back-pointer to parent object
//            std::vector< sbol::SBOLObject* >& object_store = this->sbol_owner->owned_objects[this->type];
//            object_store.push_back((SBOLObject*)child_obj);
//
//            // The following effectively adds the child object to the Document by setting its back-pointer.  However, the Document itself only maintains a register of TopLevel objects, otherwise the returned object will not be registered
//            if (parent_doc)
//            {
//                child_obj->doc = parent_doc;
//                parent_doc->SBOLObjects[child_id] = (SBOLObject*)child_obj;
//            }
//            this->validate(child_obj);
//            return *child_obj;
//        }
//        else
//        {
//            if (parent_doc && parent_doc->find(uri))
//                throw SBOLError(DUPLICATE_URI_ERROR, "An object with URI " + uri + " is already in the Document");
//
//            // Add the new object to this OwnedObject property
//            Identified* parent_obj = (Identified*)this->sbol_owner;
//            child_obj->parent = parent_obj;  // Set back-pointer to parent object
//            child_obj->identity.set(uri);
//            child_obj->persistentIdentity.set(uri);
//
//            this->add(*child_obj);
//            if (parent_doc)
//                child_obj->doc = parent_doc;
//            this->validate(child_obj);
//            return *child_obj;
//        }
//    }

//
//    template<>
//    Test& Document::get<Test>(std::string uri)
//    {
//        
//    }
//    template<>
//    Test& OwnedObject<Test>::get(std::string uri)
//    {
//        
//    }
//    
//    template<>
//    Test& OwnedObject<Test>::set(Test& sbol_obj)
//    {
//        
//    }
//    
//    template<>
//    Test& OwnedObject<Test>::add(Test& sbol_obj)
//    {
//        
//    }
//
    
#define SO_INSERTION "http://purl.obolibrary.org/obo/SO_0000667"
#define SO_DELETION "http://purl.obolibrary.org/obo/SO_0000159"
#define SO_POSSIBLE_ASSEMBLY_ERROR "http://purl.obolibrary.org/obo/SO_0000702"
#define SO_SUBSTITUTION "http://purl.obolibrary.org/obo/SO_1000002"
#define SO_NUCLEOTIDE_MATCH "http://purl.obolibrary.org/obo/SO_0000347"


    std::string verify_base(char target_base, char actual_base)
    {
        target_base = std::toupper(target_base);
        actual_base = std::toupper(actual_base);
        vector<char> actg = {'A', 'C', 'T', 'G'};

        if (target_base == actual_base)
            return SO_NUCLEOTIDE_MATCH;
        else if (target_base == '-' && actual_base == 'N')
            return SO_POSSIBLE_ASSEMBLY_ERROR;
        else if (target_base == '-' && find(actg.begin(), actg.end(), actual_base) != actg.end())
            return SO_INSERTION;
        else if (find(actg.begin(), actg.end(), target_base) != actg.end() && actual_base == 'N')
            return SO_POSSIBLE_ASSEMBLY_ERROR;
        else if (find(actg.begin(), actg.end(), target_base) != actg.end() && actual_base == '-')
            return SO_DELETION;
        else if (target_base != actual_base)
            return SO_SUBSTITUTION;
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Could not annotate sequences because of invalid base comparison");
    }

    void addQCAnnotations(ComponentDefinition& target, ComponentDefinition& construct)
    {
        Sequence& target_s = target.doc->get<Sequence>(target.sequences.get());
        Sequence& construct_s = construct.doc->get<Sequence>(construct.sequences.get());
        string target_sequence = target_s.elements.get();
        string verified_sequence = construct_s.elements.get();
        
        /* Clip gaps from target and verified sequences */
        string target_clipped = target_sequence;
        string verified_clipped = verified_sequence;
        size_t pos;
        while ((pos = target_clipped.find('-')) != std::string::npos)
            target_clipped = target_clipped.substr(0, pos) + target_clipped.substr(pos + 1, target_clipped.size() - pos);
        while ((pos = verified_clipped.find('-')) != std::string::npos)
            verified_clipped = verified_clipped.substr(0, pos) + verified_clipped.substr(pos + 1, verified_clipped.size() - pos);
        
        /* The following indices mark the beginning coordinates of clipped sequences translated into alignment coordinates. This is necessary, for example, if the target sequence is not fully covered by sequence reads, resulting in gaps padding the beginning and end of the consensus read, or if there are insertions in the verified sequence.
           eg.,
           target: actggtca
           actual: --tggt-- 
         */
        size_t l_verified = verified_sequence.find(verified_clipped[0]);
        size_t l_target = target_sequence.find(target_clipped[0]);
        size_t r_verified = verified_sequence.find_last_of(verified_clipped[verified_clipped.size() - 1]);
        size_t r_target = target_sequence.find_last_of(target_clipped[target_clipped.size() - 1]);
        
        if (Config::getOption("verbose") == "True")
        {
            cout << "Target:    " << target_sequence << endl;
            cout << "Consensus: " << verified_sequence << endl;
            cout << "Target:    " << target_clipped << endl;
            cout << "Consensus: " << verified_clipped << endl;
//
//            cout << (int)l_verified << endl;
//            cout << (int)r_verified << endl;
        }
        
        /* Calculate lengths of sequences */
        size_t L_alignment = verified_sequence.size();
        size_t L_target_clipped = target_clipped.size();
        size_t L_actual = verified_clipped.size();

        /* Map nucleotide coordinates of target sequence to alignment coordinates. Nucleotide coordinates are indexed from one */
        map < int, int > target_map = {};
        size_t i_target = 0;
        for (size_t i_alignment = l_target; i_alignment <= r_target; ++i_alignment)
        {
            char target_base = target_sequence[i_alignment];
            char verified_base = verified_sequence[i_alignment];
            if (target_base != '-')
            {
                i_target += 1;
                //            target_map[i_target] = i_alignment;
                //            assert(target_clipped[i_target] == target_sequence[target_map[i_target]]);
            }
            target_map[i_alignment+1] = i_target;
        }
        
        int region_start = 1;
        int region_end = 1;
        vector < SequenceAnnotation* > variant_annotations;
        int i_annotation = 0;
        
        // Scan alignment base by base and classify regions of interest. Bases are indexed from one not zero
        string verification_code;
        string current_region_classification = verify_base(target_sequence[0], verified_sequence[0]);
        for (int i_base = 1; i_base <= L_alignment; ++i_base)
        {
            verification_code = verify_base(target_sequence[i_base - 1], verified_sequence[i_base - 1]);
            
            if (Config::getOption("verbose") == "True")
                cout << i_base << "\t" << target_map[i_base] << "\t" << target_sequence[i_base - 1] << "\t" << verified_sequence[i_base - 1] << "\t" << verification_code << endl;
            
            if (verification_code.compare(current_region_classification) == 0)
            {
                // Extend region of interest
                ++region_end;
            }
            else
            {
                // Mark end of region of interest
                region_end = i_base - 1;
                
                // Insertions and deletions at the ends are not valid annotations (uncovered by sequence reads)
                if (i_annotation == 0 && current_region_classification.compare(SO_INSERTION) == 0)
                    ;
                else if (i_annotation == 0 && current_region_classification.compare(SO_DELETION) == 0)
                    ;
                else
                {
                    // Annotate region of interest
                    SequenceAnnotation& sa = construct.sequenceAnnotations.create < SequenceAnnotation >("qc" + to_string(i_annotation));
                    sbol::Range& r = sa.locations.create < sbol::Range > ("r");
                    r.start.set(target_map[region_start]);  // Translate region of interest into target coordinates
                    r.end.set(target_map[region_end]);
                    variant_annotations.push_back(&sa);
                    sa.roles.set(current_region_classification);
                    ++i_annotation;
                }

                // Begin a new region
                current_region_classification = verification_code;
                region_start = i_base;
            }
        }
        if (region_end >= L_alignment)
            region_end = L_alignment - 1;  // In case the sequences have perfect identity
        // Annotate final region of interest.  Insertions and deletions are not valid (uncovered by sequence reads)
        if (current_region_classification.compare(SO_INSERTION) == 0 || current_region_classification.compare(SO_DELETION) == 0)
            ;
        else
        {
            SequenceAnnotation& sa = construct.sequenceAnnotations.create < SequenceAnnotation >("qc" + to_string(i_annotation));
            sa.roles.set(current_region_classification);
            sbol::Range& r = sa.locations.create < sbol::Range > ("r");
            r.start.set(target_map[region_start]);
            r.end.set(target_map[++region_end]);
            variant_annotations.push_back(&sa);
        }
        
        if (Config::getOption("verbose") == "True")
        {
            std::cout << "Added QC Annotations:" << std::endl;
            for (auto &ann : variant_annotations)
                for (auto &l : ann->locations)
                {
                    sbol::Range& r = ann->locations.get < sbol::Range >(l.identity.get());
                    cout << ann->roles.get() << "\t" << r.start.get() << "\t" << r.end.get() << endl;
                }
        }
    };


    void Analysis::verifyTarget(Sequence& consensus)
    {
        if (consensusSequence.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target. The consensusSequence property for this Analysis has already been set. Perform a new Analysis or remove the Sequence.");

        if (!doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot verify target. Analysis " + identity.get() + " does not belong to a Document");

        // Retrieve Design by following links back through Analysis
        if (!rawData.size() || !doc->tests.find(rawData.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Test& test = doc->get<Test>(rawData.get());
        if (!test.samples.size() || !doc->builds.find(test.samples.get()) )
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Build& build = doc->get<Build>(test.samples.get());
        if (!build.design.size() || !doc->designs.find(build.design.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Design& design = doc->get<Design>(build.design.get());
        if (!design.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target, because the Design does not specify a target Sequence or the Sequence is not in the Document.");
        
        ComponentDefinition& design_structure = design.structure.get();
        if (!design_structure.sequence.size() || !doc->sequences.find(design_structure.sequences.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot verify target because the Design does not specify a target Sequence or the Sequence is not in the Document.");
        
        Sequence& target = doc->get<Sequence>(design_structure.sequences.get());
        string target_sequence = target.elements.get();
        string verified_sequence = consensus.elements.get();
        if (target_sequence.size() != verified_sequence.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid consensus sequence. Target sequence and consensus sequence are not equal lengths. Perform a sequence alignment first.");

//        // Set consensusSequence property of the Analysis
        consensusSequence.set(consensus);
        
        // Auto-construct Build.structure
        if (!build.structure.size())
        {
            string build_structure_id;
            if (Config::getOption("sbol_compliant_uris") == "True")
                build_structure_id = build.displayId.get();
            else
                build_structure_id = build.identity.get();
            build.structure.create(build_structure_id);
        }
        ComponentDefinition& build_structure = build.structure.get();

        // Set Build sequence to the consensusSequence
        build_structure.sequence.set(consensus);
        
        ::addQCAnnotations(design_structure, build_structure);
    };
    
    
    float calculateIdentity(SequenceAnnotation& target, vector<SequenceAnnotation*> qc_annotations)
    {
        int n_identical = 0;

        if (target.locations.size() == 0)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has no Range specified");
        if (target.locations.size() > 1)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has more than one Range specified");
        sbol::Range& r_target = (sbol::Range&)target.locations[0];
        
        if (Config::getOption("verbose") == "True")
            cout << r_target.start.get() << "\t" << r_target.end.get() << "\t";

        for (auto &p_qc : qc_annotations)
        {
            SequenceAnnotation& qc = *p_qc;
            if (qc.locations.size() == 0)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has no Range specified");
            if (qc.locations.size() > 1)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. A SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has more than one Range specified");
            sbol::Range& r_qc = (sbol::Range&)qc.locations[0];
            
            if (Config::getOption("verbose") == "True")
                cout << r_qc.start.get() << "\t" << r_qc.end.get() << "\t";


            string qc_classification = qc.roles.get();
            if (qc_classification.compare(SO_NUCLEOTIDE_MATCH) == 0)
            {
                n_identical += r_target.contains(r_qc) + r_target.overlaps(r_qc);
                if (Config::getOption("verbose") == "True")
                    cout << "Contains: " << r_target.contains(r_qc) << "\tOverlaps: " <<  r_target.overlaps(r_qc) << "\tIdentical: " << n_identical << "\n\t\t";
            }
            else
                if (Config::getOption("verbose") == "True")
                    cout << "\n\t\t";
        }
        if (Config::getOption("verbose") == "True")
        {
            cout << (float)n_identical << "\t" << (float)r_target.length() << endl;
            cout << "\n";
        }
        return (float)n_identical / (float)r_target.length();
    };

    float calculateError(SequenceAnnotation& target, vector<SequenceAnnotation*> qc_annotations)
    {
        int n_substitution = 0;
        int n_deletion = 0;
        int n_insertion = 0;

        if (target.locations.size() == 0)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate error. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has no Range specified");
        if (target.locations.size() > 1)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate error. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has more than one Range specified");
        sbol::Range& r_target = (sbol::Range&)target.locations[0];
    //    cout << r_target.start.get() << "\t" << r_target.end.get() << "\t";
        
        for (auto &p_qc : qc_annotations)
        {
            SequenceAnnotation& qc = *p_qc;
            if (qc.locations.size() == 0)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate error. SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has no Range specified");
            if (qc.locations.size() > 1)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate error. A SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has more than one Range specified");
            sbol::Range& r_qc = (sbol::Range&)qc.locations[0];
    //        cout << r_qc.start.get() << "\t" << r_qc.end.get();
            
            
            string qc_classification = qc.roles.get();
            if (qc_classification.compare(SO_SUBSTITUTION) == 0)
                n_substitution += r_target.contains(r_qc) + r_target.overlaps(r_qc);
            else if (qc_classification.compare(SO_DELETION) == 0)
                n_deletion += r_target.contains(r_qc) + r_target.overlaps(r_qc);
            else if (qc_classification.compare(SO_INSERTION) == 0)
                n_insertion += r_target.contains(r_qc) + r_target.overlaps(r_qc);
            
    //        else
    //            cout << "\n\t\t";
        }
    //    cout << "\n";
        return (float)(n_substitution + n_deletion + n_insertion) / (float)(r_target.length() + n_insertion);
    };

    float calculateAmbiguity(SequenceAnnotation& target, vector<SequenceAnnotation*> qc_annotations)
    {
        int n_ambiguous = 0;
        
        if (target.locations.size() == 0)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate ambiguity. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has no Range specified");
        if (target.locations.size() > 1)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate ambiguity. SequenceAnnotation " + target.identity.get() + " is invalid for this operation because it has more than one Range specified");
        sbol::Range& r_target = (sbol::Range&)target.locations[0];
    //    cout << r_target.start.get() << "\t" << r_target.end.get() << "\t";
        
        for (auto &p_qc : qc_annotations)
        {
            SequenceAnnotation& qc = *p_qc;
            if (qc.locations.size() == 0)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate ambiguity. SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has no Range specified");
            if (qc.locations.size() > 1)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate ambiguity. A SequenceAnnotation " + qc.identity.get() + " is invalid for this operation because it has more than one Range specified");
            sbol::Range& r_qc = (sbol::Range&)qc.locations[0];
    //        cout << r_qc.start.get() << "\t" << r_qc.end.get();
            
            
            string qc_classification = qc.roles.get();
            if (qc_classification.compare(SO_POSSIBLE_ASSEMBLY_ERROR) == 0)
            {
                n_ambiguous += r_target.contains(r_qc) + r_target.overlaps(r_qc);
    //            cout << SO_POSSIBLE_ASSEMBLY_ERROR << "\n\t\t";
            }
    //        else
    //            cout << "\n\t\t";
        }
    //    cout << "\n";
        return (float)n_ambiguous / (float)r_target.length();
    };

    float calculateCoverage(SequenceAnnotation& target, vector<SequenceAnnotation*> qc_annotations)
    {
        return calculateIdentity(target, qc_annotations) + calculateError(target, qc_annotations) + calculateAmbiguity(target, qc_annotations);
    };

    void get_sequence_annotation_callback(ComponentDefinition* cdef_node, void * user_data)
    {
        vector<SequenceAnnotation*>& cumulative_annotations = *(vector<SequenceAnnotation*>*)user_data;
        vector<SequenceAnnotation*> annotations = cdef_node->sequenceAnnotations.getAll();
        if (annotations.size() > 0)
        {
            cumulative_annotations.reserve(cumulative_annotations.size() + distance(annotations.begin(), annotations.end()));
            cumulative_annotations.insert(cumulative_annotations.end(), annotations.begin(), annotations.end());
        }
    };
    
    std::unordered_map < std::string, std::tuple < int, int, float > > reportQC(ComponentDefinition& target, ComponentDefinition& construct, float (*qc_method)(SequenceAnnotation&, vector<SequenceAnnotation*>))
    {
        std::unordered_map < std::string, std::tuple < int, int, float > > qc_report;  // Maps the URI of the ComponentDefinition to its qc statistic and its start and end coordinates

        vector<SequenceAnnotation*> target_annotations;
        vector<SequenceAnnotation*> qc_annotations;

        // Recursively gather all sub-Components through their SequenceAnnotation
        target.applyToComponentHierarchy(get_sequence_annotation_callback, &target_annotations);
        construct.applyToComponentHierarchy(get_sequence_annotation_callback, &qc_annotations);
        
        if (Config::getOption("verbose") == "True")
        {
            std::cout << "Generating QC report..." << std::endl;
            std::cout << "Found " << target_annotations.size() << " target annotations" << std::endl;
            std::cout << "Found " << qc_annotations.size() << " QC annotations" << std::endl;
        }
        
        for (auto &ann_target : target_annotations)
        {
            ComponentDefinition& parent_cdef = (ComponentDefinition&)*ann_target->parent;
            if (ann_target->locations.size() > 0)
            {
                sbol::Range& r = (sbol::Range&)ann_target->locations[0];
                // Skip over SequenceAnnotations that do not have a corresponding Component
                if (ann_target->component.size())
                {
                    Component& c = parent_cdef.components[ann_target->component.get()];
                    ComponentDefinition& cdef = ann_target->doc->get<ComponentDefinition>(c.definition.get());
                    
                    float qc_statistic = qc_method(*ann_target, qc_annotations);
                    std::tuple < int, int, float > qc = std::make_tuple(r.start.get(), r.end.get(), qc_statistic);
                    qc_report[ cdef.identity.get() ] = qc;
                    
                }
                else if(ann_target->roles.size() > 0)
                {
                    float qc_statistic = qc_method(*ann_target, qc_annotations);
                    std::tuple < int, int, float > qc = std::make_tuple(r.start.get(), r.end.get(), qc_statistic);
                    qc_report[ parent_cdef.identity.get() ] = qc;
                }
            }
        }
        
        // Calculate cumulative statistics at the highest level of the component hierarchy.
        Sequence& target_seq = target.doc->get<Sequence>(target.sequences.get());
        SequenceAnnotation target_sa = SequenceAnnotation("temporary");
        Range& r = target_sa.locations.create<Range>("r");
        r.start.set(1);
        r.end.set(target_seq.elements.get().size());
        float qc_statistic = qc_method(target_sa, qc_annotations);
        std::tuple < int, int, float > qc = std::make_tuple(r.start.get(), r.end.get(), qc_statistic);
        qc_report[ target.identity.get() ] = qc;
        return qc_report;
    };
    
    
    std::unordered_map < std::string, std::tuple < int, int, float > > Analysis::reportIdentity()
    {
        if (!doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot generate QC report. Analysis " + identity.get() + " does not belong to a Document");

        // Retrieve Design by following links back through Analysis
        if (!rawData.size() || !doc->tests.find(rawData.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Test. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Test& test = doc->get<Test>(rawData.get());
        if (!test.samples.size() || !doc->builds.find(test.samples.get()) )
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Build. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Build& build = doc->get<Build>(test.samples.get());
        if (!build.design.size() || !doc->designs.find(build.design.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");

        Design& design = doc->get<Design>(build.design.get());
        
        if (!design.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Design is unspecified.");
        ComponentDefinition& target = design.structure.get();
        
        if (!build.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Build is unspecified.");
        ComponentDefinition& construct = build.structure.get();

        return ::reportQC(target, construct, &::calculateIdentity);
    };
    
    std::unordered_map < std::string, std::tuple < int, int, float > > Analysis::reportError()
    {
        if (!doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot generate QC report. Analysis " + identity.get() + " does not belong to a Document");

        // Retrieve Design by following links back through Analysis
        if (!rawData.size() || !doc->tests.find(rawData.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Test. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Test& test = doc->get<Test>(rawData.get());
        if (!test.samples.size() || !doc->builds.find(test.samples.get()) )
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Build. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Build& build = doc->get<Build>(test.samples.get());
        if (!build.design.size() || !doc->designs.find(build.design.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");

        Design& design = doc->get<Design>(build.design.get());
        
        if (!design.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Design is unspecified.");
        ComponentDefinition& target = design.structure.get();
        
        if (!build.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Build is unspecified.");
        ComponentDefinition& construct = build.structure.get();

        return ::reportQC(target, construct, &::calculateError);
    };
    
    std::unordered_map < std::string, std::tuple < int, int, float > > Analysis::reportCoverage()
    {
        if (!doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot generate QC report. Analysis " + identity.get() + " does not belong to a Document");

        // Retrieve Design by following links back through Analysis
        if (!rawData.size() || !doc->tests.find(rawData.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Test. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Test& test = doc->get<Test>(rawData.get());
        if (!test.samples.size() || !doc->builds.find(test.samples.get()) )
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Build. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Build& build = doc->get<Build>(test.samples.get());
        if (!build.design.size() || !doc->designs.find(build.design.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");

        Design& design = doc->get<Design>(build.design.get());
        
        if (!design.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Design is unspecified.");
        ComponentDefinition& target = design.structure.get();
        
        if (!build.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Build is unspecified.");
        ComponentDefinition& construct = build.structure.get();

        return ::reportQC(target, construct, &::calculateCoverage);
    };
    
    std::unordered_map < std::string, std::tuple < int, int, float > > Analysis::reportAmbiguity()
    {
        if (!doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot generate QC report. Analysis " + identity.get() + " does not belong to a Document");

        // Retrieve Design by following links back through Analysis
        if (!rawData.size() || !doc->tests.find(rawData.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Test. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Test& test = doc->get<Test>(rawData.get());
        if (!test.samples.size() || !doc->builds.find(test.samples.get()) )
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Build. The Analysis is not part of a Design-Build-Test-Analysis workflow.");
        
        Build& build = doc->get<Build>(test.samples.get());
        if (!build.design.size() || !doc->designs.find(build.design.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report because the Analysis is not linked to a Design. The Analysis is not part of a Design-Build-Test-Analysis workflow.");

        Design& design = doc->get<Design>(build.design.get());
        
        if (!design.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Design is unspecified.");
        ComponentDefinition& target = design.structure.get();
        
        if (!build.structure.size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot generate QC report, because the structure property of the Build is unspecified.");
        ComponentDefinition& construct = build.structure.get();

        return ::reportQC(target, construct, &::calculateAmbiguity);
    };
    
    
    
};
