/**
 * @file    dblt.h
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

#ifndef DBLT_INCLUDED
#define DBLT_INCLUDED

#include "componentdefinition.h"
#include "moduledefinition.h"
#include "collection.h"

namespace sbol
{
    class Design : public TopLevel
    {
    private:
        ReferencedObject _structure;
        ReferencedObject _function;
    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > function;
        
        Design() :
            TopLevel("http://sys-bio.org#Design", "example"),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }),
            _structure(this, "http://sys-bio.org#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, "dummy"),
            _function(this, "http://sys-bio.org#_function", SBOL_MODULE_DEFINITION, '1', '1', {}, "dummy")
        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };

        /// SBOL-compliant constructor. Use when SBOL-compliant and typed URIs are enabled (default state of library).  Creates a new Design, new ComponentDefinition, and new ModuleDefinition from scratch.
        Design(std::string uri) : Design(uri, uri, uri) {};

        /// Open-world constructor
        Design(std::string uri, std::string structure_uri, std::string function_uri) : Design()
        {
            ComponentDefinition& cd = structure.create(structure_uri);
            ModuleDefinition& md = function.create(function_uri);
        };

        /// Constructs a new Design from an already existing ModuleDefinition
        Design(std::string uri, ComponentDefinition& structure, ModuleDefinition& function) :
            TopLevel("http://sys-bio.org#Design", uri),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }, structure),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }, function),
            _structure(this, "http://sys-bio.org#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, structure.identity.get()),
            _function(this, "http://sys-bio.org#_function", SBOL_MODULE_DEFINITION, '1', '1', {}, function.identity.get())
        {
            this->structure.set(structure);
            this->function.set(function);
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        virtual ~Design() {};

    };
    
    class Build : public TopLevel
    {
    private:
        ReferencedObject _structure;
        ReferencedObject _function;

    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > behavior;
        
        /// SBOL-compliant constructor
        Build(std::string uri) : Build(uri, uri, uri) {};
        
        Build(std::string uri, std::string structure_uri, std::string behavior_uri) :
            TopLevel(SBOL_IMPLEMENTATION, uri),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }),
            _structure(this, "http://sys-bio.org#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, "dummy"),
            _function(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', {}, "dummy")
        {
            ComponentDefinition& cd = structure.create(structure_uri);
            ModuleDefinition& md = behavior.create(behavior_uri);
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };


        Build(std::string uri, ComponentDefinition& structure, ModuleDefinition& behavior) :
            TopLevel(SBOL_IMPLEMENTATION, uri),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }, structure),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }, behavior),
            _structure(this, "http://sys-bio.org#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', {}, structure.identity.get()),
            _function(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', {}, behavior.identity.get())

        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        virtual ~Build() {};
    };
  
    class Test : public Collection
    {
    public:
        Test(std::string uri) :
            Collection(SBOL_COLLECTION, uri),
            rawData(this, SBOL_MEMBERS, '0', '*', {})
        {
        }
        URIProperty rawData;
    };

    class Analysis : public TopLevel
    {
    public:
        Analysis(std::string uri = "example") :
            TopLevel(SBOL_COLLECTION, uri),
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
        ~Analysis() {};
    private:
        ReferencedObject _consensusSequence;
        ReferencedObject _fittedModel;

    
    };
    
};



#endif