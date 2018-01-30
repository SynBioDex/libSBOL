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

#include <tuple>

namespace sbol
{
    /// This class represents a biological Design. A Design is a conceptual representation of a biological system that a synthetic biologist intends to build. A Design is the first object created in libSBOL's formalized Design-Build-Test-Analysis workflow.
    class Design : public TopLevel
    {
    friend class Document;
    friend class OwnedObject<Design>;
        
    public:
        /// Construct a new Design from scratch. The structure and function of the Design are not initialized.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Design(std::string uri = "example", std::string version = VERSION_STRING) :
            TopLevel(SYSBIO_URI "#Design", uri, VERSION_STRING),
            characterization(this, SYSBIO_URI "#characterization", SYSBIO_ANALYSIS, '0', '*', { libsbol_rule_7 }),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', ValidationRules({})),
            _function(this, SYSBIO_URI "#_function", SBOL_MODULE_DEFINITION, '1', '1', ValidationRules({}))
        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };
        
        
        /// Constructs a new Design. The structure and function of the Design are initialized. A FunctionalComponent is autoconstructed which correlates the structure and function.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param structure A ComponentDefinition representing the structural aspects of the Design
        /// @param function A ModuleDefiniition representing the functional aspects of the Design
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Design(std::string uri, ComponentDefinition& structure, ModuleDefinition& function, std::string version = VERSION_STRING) :
            TopLevel(SYSBIO_DESIGN, uri, version),
            characterization(this, SYSBIO_URI "#characterization", SYSBIO_ANALYSIS, '0', '*', { libsbol_rule_7 }),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_3 }, structure),
            function(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_4 }, function),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', ValidationRules({}), structure.identity.get()),
            _function(this, SYSBIO_URI "#_function", SBOL_MODULE_DEFINITION, '1', '1', ValidationRules({}), function.identity.get())
        {
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };

        /// The target biological structure for synthesis or other molecular assembly
        OwnedObject < ComponentDefinition > structure;
        
        /// The intended function and predicted behavior of the Design object
        OwnedObject < ModuleDefinition > function;
        
        /// A reference to an Analysis or multiple Analysis objects that contain characterization data, previously verified experimental knowledge, or explanatory models that inform a Design.
        ReferencedObject characterization;
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        ~Design() override;

    private:
        ReferencedObject _structure;
        ReferencedObject _function;
        
    };
    
    template<>
    Design& TopLevel::generate<Design>(std::string uri);

    template<>
    Design& TopLevel::generate<Design>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);
    
    /// A Build is a realization of a Design. For practical purposes, a Build can represent a biological clone, a plasmid, or other laboratory sample. For a given Design, there may be multiple Builds realized in the lab. A Build represents the second step in libSBOL's formalized Design-Build-Test-Analyze workflow.
    class Build : public Implementation
    {
    friend class Document;
    friend class OwnedObject<Build>;
        
    public:
        /// Constructs a new Build from scratch.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Build(std::string uri = "example", std::string version = VERSION_STRING) :
            Implementation(uri, VERSION_STRING),
            design(this, SYSBIO_URI "#design", SYSBIO_DESIGN, '0', '1', { libsbol_rule_8 }),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', ValidationRules({})),
            _behavior(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', ValidationRules({})),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', ValidationRules({}), SYSBIO_BUILD)
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
            }
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };

        /// Constructs a new Build. The structure and behavior of the Build are initialized. A FunctionalComponent is autoconstructed which correlates the structure and function.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param structure A ComponentDefinition representing the experimentally verified structure of the construct as verified by DNA sequencing or other analysis
        /// @param function A ModuleDefiniition representing the observed behavior of the constructed system
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Build(std::string uri, ComponentDefinition& structure, ModuleDefinition& behavior, std::string version = VERSION_STRING) :
            Implementation(uri, version),
            design(this, SYSBIO_URI "#design", SYSBIO_DESIGN, '0', '1', { libsbol_rule_8 }),
            structure(this, SBOL_COMPONENT_DEFINITION, '1', '1', { libsbol_rule_5 }, structure),
            behavior(this, SBOL_MODULE_DEFINITION, '1', '1', { libsbol_rule_6 }, behavior),
            _structure(this, SYSBIO_URI "#_structure", SBOL_COMPONENT_DEFINITION, '1', '1', ValidationRules({}), structure.identity.get()),
            _behavior(this, SBOL_URI "#built", SBOL_MODULE_DEFINITION, '1', '1', ValidationRules({}), behavior.identity.get()),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', ValidationRules({}), SYSBIO_BUILD)
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
            }
            hidden_properties.push_back(SBOL_COMPONENT_DEFINITION);
            hidden_properties.push_back(SBOL_MODULE_DEFINITION);
        };

        /// A reference to a Design object which represents the intended structure and function for this Build
        ReferencedObject design;
        
        /// The experimentally verified structure of the construct as verified by DNA sequencing or other analysis
        OwnedObject < ComponentDefinition > structure;
        
        /// The observed behavior of the constructed system
        OwnedObject < ModuleDefinition > behavior;
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        ~Build() override;
    
    private:
        URIProperty sysbio_type;
        ReferencedObject _structure;
        ReferencedObject _behavior;
    };
  
    template<>
    Build& TopLevel::generate<Build>(std::string uri);
    
    template<>
    Build& TopLevel::generate<Build>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);
    
    /// A Test is a container for experimental data. A Test is the product of the third step of libSBOL's formalized Design-Build-Test-Analyze workflow
    class Test : public Collection
    {
    friend class Document;
    friend class OwnedObject<Test>;
        
    private:
        URIProperty sysbio_type;
        
    public:
        /// Construct a new Test object.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Test(std::string uri = "example", std::string version = VERSION_STRING) :
            Collection(uri, version),
            samples(this, SYSBIO_URI "#samples", SBOL_IMPLEMENTATION, '0', '*', { libsbol_rule_9 }),
            dataFiles(this, SBOL_MEMBERS, SBOL_ATTACHMENT, '0', '*', ValidationRules({})),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', ValidationRules({}), SYSBIO_TEST)
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

        /// References to Builds which were tested in the experiment
        ReferencedObject samples;

        /// References to file Attachments which contain experimental data sets
        ReferencedObject dataFiles;
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

        /// Construct a new Analysis object.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Analysis(std::string uri = "example", std::string version = VERSION_STRING) :
            TopLevel(SYSBIO_ANALYSIS, uri, version),
            rawData(this, SYSBIO_URI "#rawData", SBOL_COLLECTION, '0', '1', { libsbol_rule_10 }),
            dataFiles(this, SBOL_ATTACHMENTS, SBOL_ATTACHMENT, '0', '*', ValidationRules({})),
            consensusSequence(this, SBOL_SEQUENCE, '0', '1', ValidationRules({})),
            fittedModel(this, SBOL_MODEL, '0', '1', ValidationRules({})),
            dataSheet(this, SYSBIO_URI "#dataSheet", SBOL_ATTACHMENT, '0', '1', ValidationRules({})),
            _consensusSequence(this, SYSBIO_URI "#consensusSequence", SBOL_SEQUENCE, '0', '1', ValidationRules({})),
            _fittedModel(this, SYSBIO_URI "#model", SBOL_MODEL, '0', '1', ValidationRules({}))
        {
            hidden_properties.push_back(SYSBIO_URI "#consensusSequence");
            hidden_properties.push_back(SYSBIO_URI "#model");
        }
        
        /// A reference to a Test object which contains the raw data for an Analysis
        ReferencedObject rawData;
        
        /// References to file Attachments which contain experimental data sets
        ReferencedObject dataFiles;
        
        /// A reference to a datasheet file
        ReferencedObject dataSheet;
        
        /// A sequence object that represents a consensus sequence from DNA sequencing data
        OwnedObject < Sequence > consensusSequence;

        /// A Model derived from fitting an experimental data set
        OwnedObject < Model > fittedModel;
        
        /// Compare a consensus Sequence to the target Sequence
        void verifyTarget(Sequence& consensus_sequence);
        
        std::unordered_map < std::string, std::tuple < int, int, float > > reportIdentity();

        std::unordered_map < std::string, std::tuple < int, int, float > > reportError();

        std::unordered_map < std::string, std::tuple < int, int, float > > reportCoverage();

        std::unordered_map < std::string, std::tuple < int, int, float > > reportAmbiguity();

        ~Analysis() override;
    private:
        ReferencedObject _consensusSequence;
        ReferencedObject _fittedModel;

    
    };

    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri);
    
    template<>
    Analysis& TopLevel::generate<Analysis>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);
    
    /// A SampleRoster is a container used to group Builds that are included in an experiment together. A SampleRoster can be used to generate a Test in a Design-Build-Test-Learn workflow.
    class SampleRoster : public Collection
    {
        friend class Document;
        friend class OwnedObject<Test>;
        
    private:
        URIProperty sysbio_type;
        
    public:
        /// Construct a new SampleRoster object.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        SampleRoster(std::string uri = "example", std::string version = VERSION_STRING) :
            Collection(uri, version),
            samples(this, SBOL_MEMBERS, SBOL_IMPLEMENTATION, '0', '*', ValidationRules({ libsbol_rule_15 })),
            sysbio_type(this, SYSBIO_URI "#type", '1', '1', ValidationRules({}), SYSBIO_URI "#SampleRoster")
        {
            // Overwrite the typed URI formed by base constructor by replacing Collection with Test
            if  (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            {
                if (Config::getOption("sbol_typed_uris") == "True")
                {
                    identity.set(getHomespace() + "/SampleRoster/" + displayId.get() + "/" + version);
                    persistentIdentity.set(getHomespace() + "/SampleRoster/" + displayId.get());
                }
            }
        }
        
        /// References to Builds which were tested in an experiment
        ReferencedObject samples;
    };
};



#endif