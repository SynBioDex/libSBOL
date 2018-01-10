/**
 * @file    dbtl.h
 * @brief   Contains the interface for Design-Build-Test classes
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

#ifndef DBTL_INCLUDED
#define DBTL_INCLUDED

#include "componentdefinition.h"
#include "moduledefinition.h"
#include "collection.h"
#include "implementation.h"

namespace sbol
{
    ///
    class Design : public TopLevel
    {
    friend class Document;
    friend class OwnedObject<Design>;
        
    private:
        ReferencedObject _structure;
        ReferencedObject _function;
        
    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > function;

//        /// Default constructor
//        Design() :
//            TopLevel(SYSBIO_URI "#Design", "example", VERSION_STRING),
//            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }),
//            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }),
//            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, "dummy"),
//            _function(this, SYSBIO_URI "#_function", SBOL_MODULE_DEFINITION, '1', '1', {}, "dummy")
//        {
//            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
//            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
//        };

//        /// Open-world constructor
//        Design(std::string uri, std::string structure_uri, std::string function_uri, std::string version = VERSION_STRING) : Design()
//        {
//            this->version.set(version);
//            this->identity.set(uri);
//            ComponentDefinition& cd = structure.create(structure_uri);
//            ModuleDefinition& md = function.create(function_uri);
//        };

//        /// SBOL-compliant constructor. Use when SBOL-compliant and typed URIs are enabled (default state of library).  Creates a new Design, new ComponentDefinition, and new ModuleDefinition from scratch.
//        Design(std::string uri, std::string version = VERSION_STRING) :
//            Design(uri, uri, uri, version)
//        {
//            displayId.set(uri);
//            if (Config::getOption("sbol_typed_uris") == "True")
//            {
//                identity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get() + "/" + version);
//                persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
//            }
//            else
//            {
//                identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
//                persistentIdentity.set(getHomespace() + "/" + displayId.get());
//            }
//        };
     
        /// Construct a new Design from scratch. The structure and function of the Design are not initialized.
        Design(std::string uri = "example", std::string version = VERSION_STRING) :
            TopLevel(SYSBIO_URI "#Design", uri, VERSION_STRING),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}),
            _function(this, SYSBIO_URI "#_function", SBOL_MODULE_DEFINITION, '1', '1', {})
        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        
        /// Constructs a new Design. The structure and function of the Design are initialized. A FunctionalComponent is autoconstructed which correlates the structure and function.
        /// @param structure A ComponentDefinition representing the structural aspects of the Design
        /// @param function A ModuleDefiniition representing the functional aspects of the Design
        Design(std::string uri, ComponentDefinition& structure, ModuleDefinition& function) :
            TopLevel(SYSBIO_DESIGN, uri),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }, structure),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }, function),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, structure.identity.get()),
            _function(this, SYSBIO_URI "#_function", SBOL_MODULE_DEFINITION, '1', '1', {}, function.identity.get())
        {
            this->structure.set(structure);
            this->function.set(function);
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        ~Design() override;

    };
    
    template<>
    Design& TopLevel::generate<Design>(std::string uri);

    template<>
    Design& TopLevel::generate<Design>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);
    
    class Build : public Implementation
    {
    friend class Document;
    friend class OwnedObject<Build>;
    private:
        URIProperty sysbio_type;
        ReferencedObject _structure;
        ReferencedObject _behavior;

    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > behavior;

        Build(std::string uri = "example", std::string version = VERSION_STRING) :
            Implementation(uri, VERSION_STRING),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, "dummy"),
            _behavior(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', {}, "dummy"),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', {}, SYSBIO_BUILD)
        {
            // Overwrite the typed URI formed by base constructor by replacing Implementation with Build
            if  (Config::getOption("sbol_compliant_uris") == "True")
            {
                displayId.set(uri);
                if (Config::getOption("sbol_typed_uris") == "True")
                {
                    identity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get() + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get());
                }
//                else
//                {
//                    identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
//                    persistentIdentity.set(getHomespace() + "/" + displayId.get());
//                }
            }
//            else
//            {
//                this->version.set(version);
//                this->identity.set(uri);
//            }
        };
        
//        // Default constructor
//        Build() :
//            Implementation("example", VERSION_STRING),
//            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }),
//            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }),
//            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, "dummy"),
//            _behavior(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', {}, "dummy"),
//            sysbio_type(this, SYSBIO_URI "#type", '1', '1', {}, SYSBIO_BUILD)
//        {
//            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
//            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
//        }
//        
//        /// SBOL-compliant constructor
//        Build(std::string uri, std::string version = VERSION_STRING) :
//            Build(uri, uri, uri, version)
//        {
//            if  (Config::getOption("sbol_compliant_uris") == "True" && Config::getOption("sbol_typed_uris") == "True")
//            {
//                displayId.set(uri);
//                identity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get() + "/" + version);
//                persistentIdentity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get());
//            }
//            else
//                throw SBOLError(SBOL_ERROR_COMPLIANCE, "Cannot construct Build. This constructor method requires both SBOL-compliant and SBOL-typed URIs. Use Config::setOption to configure these options or use the alternate constructor method.");
//        };
//        
//        Build(std::string uri, std::string structure_uri, std::string behavior_uri, std::string version = VERSION_STRING) :
//            Build()
//        {
//            if  (Config::getOption("sbol_compliant_uris") == "True")
//            {
//                displayId.set(uri);
//                if (Config::getOption("sbol_typed_uris") == "True")
//                {
//                    identity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get() + "/" + version);
//                    persistentIdentity.set(getHomespace() + "/" + getClassName(SYSBIO_BUILD) + "/" + displayId.get());
//                }
//                else
//                {
//                    identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
//                    persistentIdentity.set(getHomespace() + "/" + displayId.get());
//                }
//            }
//            else
//            {
//                this->version.set(version);
//                this->identity.set(uri);
//            }
//            ComponentDefinition& cd = structure.create(structure_uri);
//            ModuleDefinition& md = behavior.create(behavior_uri);
//        };


        Build(std::string uri, ComponentDefinition& structure, ModuleDefinition& behavior, std::string version = VERSION_STRING) :
            Implementation(uri, version),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }, structure),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }, behavior),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, structure.identity.get()),
            _behavior(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', {}, behavior.identity.get()),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', {}, SYSBIO_BUILD)
        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        ~Build() override;
    };
  
    template<>
    Build& TopLevel::generate<Build>(std::string uri);
    
    template<>
    Build& TopLevel::generate<Build>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);
    
    class Test : public Collection
    {
    friend class Document;
    friend class OwnedObject<Test>;
    private:
        URIProperty sysbio_type;
    public:
        Test(std::string uri = "example", std::string version = VERSION_STRING) :
            Collection(uri, version),
            rawData(this, SBOL_MEMBERS, '0', '*', {}),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', {}, SYSBIO_TEST)
        {
            // Overwrite the typed URI formed by base constructor by replacing Collection with Test
            if  (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            {
                if (Config::getOption("sbol_typed_uris") == "True")
                {
                    identity.set(getHomespace() + "/" + getClassName(SYSBIO_TEST) + "/" + displayId.get() + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + getClassName(SYSBIO_TEST) + "/" + displayId.get());
                }
            }
        }
        
        URIProperty rawData;
    };

    template<>
    Test& TopLevel::generate<Test>(std::string uri);
    
    template<>
    Test& TopLevel::generate<Test>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);

    
    class Analysis : public TopLevel
    {
    friend class Document;
    friend class OwnedObject<Analysis>;
    public:
        
        Analysis(std::string uri = "example", std::string version = VERSION_STRING) :
            TopLevel(SYSBIO_ANALYSIS, uri, version),
            consensusSequence(this, SBOL_SEQUENCE, '0', '1', {}),
            fittedModel(this, SBOL_MODEL, '0', '1', {}),
            dataSheet(this, SYSBIO_URI "#dataSheet", SBOL_ATTACHMENT, '0', '1', {}),
            processedData(this, SBOL_MEMBERS, '0', '*', {}),
            _consensusSequence(this, SYSBIO_URI "#consensusSequence", SBOL_SEQUENCE, '0', '1', {}),
            _fittedModel(this, SYSBIO_URI "#model", SBOL_MODEL, '0', '1', {})
        {
            hidden_properties.push_back(SYSBIO_URI "#consensusSequence");
            hidden_properties.push_back(SYSBIO_URI "#model");
        }
        OwnedObject < Sequence > consensusSequence;
        OwnedObject < Sequence > fittedModel;
        ReferencedObject dataSheet;
        URIProperty processedData;
        ~Analysis() override;
    private:
        ReferencedObject _consensusSequence;
        ReferencedObject _fittedModel;

    
    };

    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri);
    
    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);

};



#endif