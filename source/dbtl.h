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
#include "experiment.h"

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
        virtual ~Design() {};

    private:
        ReferencedObject _structure;
        ReferencedObject _function;
        
    };
    
    template<>
    Design& TopLevel::generate<Design>(std::string uri);

    template<>
    Design& TopLevel::generate<Design>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);

    // template<>
    // Design& OwnedObject<Design>::get(std::string uri);

    // template<>
    // Design& OwnedObject<Design>::operator[] (std::string uri);

    // template<>
    // Design& OwnedObject<Design>::operator[] (const int nIndex);

    
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
        virtual ~Build() {};
    
    // private:
        URIProperty sysbio_type;
        ReferencedObject _structure;
        ReferencedObject _behavior;
    };
  
    template<>
    Build& TopLevel::generate<Build>(std::string uri);
    
    template<>
    Build& TopLevel::generate<Build>(std::string uri, Agent& agent, Plan& plan, std::vector < Identified* > usages);

    // template<>
    // Build& OwnedObject<Build>::get(std::string uri);
    
    // template<>
    // Build& OwnedObject<Build>::operator[] (std::string uri);

    // template<>
    // Build& OwnedObject<Build>::operator[] (const int nIndex);
    
    /// A Test is a container for experimental data. A Test is the product of the third step of libSBOL's formalized Design-Build-Test-Analyze workflow
    class Test : public ExperimentalData
    {
    friend class Document;
    friend class OwnedObject<Test>;
        
    public:
        /// Construct a new Test object.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Test(std::string uri = "example", std::string version = VERSION_STRING) :
            ExperimentalData(uri, version),
            samples(this, SYSBIO_URI "#samples", SBOL_IMPLEMENTATION, '0', '*', { libsbol_rule_9 }),
            dataFiles(this, SBOL_ATTACHMENTS, SBOL_ATTACHMENT, '0', '*', ValidationRules({}))
//            sysbio_type(this, SYSBIO_URI "#type", '1', '1', ValidationRules({}), SYSBIO_TEST)
        {
//            // Overwrite the typed URI formed by base constructor by replacing Collection with Test
//            if  (Config::getOption("sbol_compliant_uris").compare("True") == 0)
//            {
//                if (Config::getOption("sbol_typed_uris") == "True")
//                {
//                    identity.set(getHomespace() + "/" + getClassName(SYSBIO_TEST) + "/" + displayId.get() + "/" + version);
//                    persistentIdentity.set(getHomespace() + "/" + getClassName(SYSBIO_TEST) + "/" + displayId.get());
//                }
//            }
        }

        /// References to Builds which were tested in the experiment
        ReferencedObject samples;

        /// References to file Attachments which contain experimental data sets
        ReferencedObject dataFiles;

        virtual ~Test() {};
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
            rawData(this, SYSBIO_URI "#rawData", SBOL_EXPERIMENTAL_DATA, '0', '1', { libsbol_rule_10 }),
            dataFiles(this, SBOL_ATTACHMENTS, SBOL_ATTACHMENT, '0', '*', ValidationRules({})),
            consensusSequence(this, SYSBIO_URI "#consensusSequence", '0', '1', ValidationRules({})),
            fittedModel(this, SYSBIO_URI "#model", '0', '1', ValidationRules({})),
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

        virtual ~Analysis() {};
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
    
//    class Repressor : public FunctionalComponent
//    {
//    public:
//        Repressor(std::string uri = "example") :
//            FunctionalComponent(uri)
//        {
//        }
//    };
//
//    class TargetPromoter : public FunctionalComponent
//    {
//    public:
//        TargetPromoter(std::string uri = "example") :
//            FunctionalComponent(uri)
//        {
//        }
//    };
//
//    class Activator : public FunctionalComponent
//    {
//    public:
//        Activator(std::string uri = "example") :
//            FunctionalComponent(uri)
//        {
//        }
//    };
//
//    class Inducer : public FunctionalComponent
//    {
//    public:
//        Inducer(std::string uri = "example") :
//            FunctionalComponent(uri)
//        {
//        }
//    };
//    
//    class Gene : public FunctionalComponent
//    {
//    public:
//        Gene(std::string uri = "example") :
//        FunctionalComponent(uri)
//        {
//        }
//    };
//
//    class GeneProduct : public FunctionalComponent
//    {
//    public:
//        GeneProduct(std::string uri = "example") :
//        FunctionalComponent(uri)
//        {
//        }
//    };
    
//    template<>
//    FunctionalComponent& OwnedObject<Repressor>::get();
//
//    template<>
//    FunctionalComponent& OwnedObject<TargetPromoter>::get();
//
//    template<>
//    FunctionalComponent& OwnedObject<Activator>::get();
//
//    template<>
//    FunctionalComponent& OwnedObject<Inducer>::get();
//
//    template<>
//    FunctionalComponent& OwnedObject<Gene>::get();
//
//    template<>
//    FunctionalComponent& OwnedObject<GeneProduct>::get();
//    
//    template<>
//    void OwnedObject<Repressor>::set(ComponentDefinition& sbol_obj);
//    
//    template<>
//    OwnedObject<TargetPromoter>::set();
//    
//    template<>
//    OwnedObject<Activator>::set();
//    
//    template<>
//    OwnedObject<Inducer>::set();
//
//    template<>
//    OwnedObject<Gene>::set();
//
//    template<>
//    OwnedObject<GeneProduct>::set();

    
    
    template <class SBOLClass>
    class AliasedProperty : public OwnedObject<SBOLClass>
    {
    public:
        rdf_type alias;

        AliasedProperty(void *property_owner, rdf_type sbol_uri, rdf_type alias_uri, char lower_bound, char upper_bound, ValidationRules validation_rules) :
            OwnedObject<SBOLClass>(property_owner, sbol_uri, lower_bound, upper_bound, validation_rules),
            alias(alias_uri)
        {
            this->sbol_owner->hidden_properties.push_back(alias_uri);
        };
        
        ~AliasedProperty()
        {
            this->sbol_owner->owned_objects.erase(alias);
        }

        void set(SBOLClass& sbol_obj)
        {
            OwnedObject<SBOLClass>(this->sbol_owner, this->type, this->lowerBound, this->upperBound, this->validationRules).add(sbol_obj);
            OwnedObject<SBOLClass>(this->sbol_owner, this->alias, this->lowerBound, this->upperBound, this->validationRules).set(sbol_obj);
        };
        
        void add(SBOLClass& sbol_obj)
        {
            OwnedObject<SBOLClass>(this->sbol_owner, this->type, this->lowerBound, this->upperBound, this->validationRules).add(sbol_obj);
            OwnedObject<SBOLClass>(this->sbol_owner, this->alias, this->lowerBound, this->upperBound, this->validationRules).add(sbol_obj);
        };
        
        SBOLClass& get(std::string uri = "")
        {
            SBOLClass& obj = OwnedObject<SBOLClass>(this->sbol_owner, this->alias, this->lowerBound, this->upperBound, this->validationRules).get(uri);
            return obj;
        };

        SBOLClass& create(std::string uri)
        {
            SBOLClass& obj = OwnedObject<SBOLClass>(this->sbol_owner, this->type, this->lowerBound, this->upperBound, this->validationRules).create(uri);
            OwnedObject<SBOLClass>(this->sbol_owner, this->alias, this->lowerBound, this->upperBound, this->validationRules).add(obj);
            return obj;
        };
        
        SBOLClass& define(SBOLObject& definition_object)
        {
            SBOLClass& obj = OwnedObject<SBOLClass>(this->sbol_owner, this->type, this->lowerBound, this->upperBound, this->validationRules).define(definition_object);
            OwnedObject<SBOLClass>(this->sbol_owner, this->alias, this->lowerBound, this->upperBound, this->validationRules).add(obj);
            return obj;
        };
        
        int size()
        {
            std::size_t size = this->sbol_owner->owned_objects[this->alias].size();
            return (int)size;
        }
        
        int __len__()
        {
            return this->size();
        }
    };
    
//    class RepressorModule : public ModuleDefinition
//    {
//    public:
//        RepressorModule(std::string uri, ComponentDefinition& repressor, ComponentDefinition& target_promoter, ComponentDefinition& target_cds, ComponentDefinition& product) :
//            ModuleDefinition(uri),
//            repressor(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#repressor", '0', '1', ValidationRules({})),
//            targetPromoter(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#targetPromoter", '0', '1', ValidationRules({}))
//            targetCDS(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#targetPromoter", '0', '1', ValidationRules({}))
//            product(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#targetPromoter", '0', '1', ValidationRules({}))
//
//        {
//            FunctionalComponent& repressor_fc = this->repressor.define(repressor);
//            FunctionalComponent& target_promoter_fc = this->targetPromoter.define(target_promoter);
//            FunctionalComponent& target_cds_fc = this->targetCDS.define(target_cds);
//            FunctionalComponent& product_fc = this->product.define(product);
//
//            Interaction& repression = this->moduleDefinitions.create(uri + "_repression");
//            Participation& repressor_participation = repression.participations.create("repressor");
//            Participation& target_promoter_participation = repression.participations.create("target_promoter");
//            repression.types.set(SBO_INHIBITION);
//            repressor_participation.roles.set(SBO_INHIBITOR);
//            target_promoter_participation.roles.set(SBO_PROMOTER);
//
//            Interaction& gene_production = this->moduleDefinitions.create(uri + "_gene_production");
//            Participation& target_cds_participation = gene_production.participations.create("target_cds");
//            Participation& product_participation = gene_production.participations.create("product");
//            gene_production.types.set(SBO_GENE_PRODUCTION);
//            
//            
//            target_cds_participation.participant.set(input);
//            target_promoter_participation.participant.set(mediator);
//            
//            
//            input_participation.roles.set();
//            mediator_participation.roles.set();
//        }
//        AliasedProperty<FunctionalComponent> repressor;
//        AliasedProperty<FunctionalComponent> targetPromoter;
//        
//    };
    
    class TranscriptionalRepressionInteraction : public Interaction
    {
    public:
        TranscriptionalRepressionInteraction(std::string uri, ComponentDefinition& repressor, ComponentDefinition& target_promoter) :
            Interaction(SBOL_INTERACTION, uri, SBO_INHIBITION),
            repressor(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#repressor", '0', '1', ValidationRules({})),
            targetPromoter(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#targetPromoter", '0', '1', ValidationRules({}))
        {
            if (!repressor.types.find(BIOPAX_PROTEIN))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid repressor specified for TranscriptionalRepressionInteraction. The repressor must have type BIOPAX_PROTEIN");
            if (!target_promoter.types.find(BIOPAX_DNA))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid target promoter specified for TranscriptionalRepressionInteraction. The promoter must have type BIOPAX_DNA");

            FunctionalComponent& repressor_fc = this->repressor.define(repressor);
            FunctionalComponent& promoter_fc = this->targetPromoter.define(target_promoter);

            Participation& repressor_participation = this->participations.create(uri + "_repressor");
            repressor_participation.roles.set(SBO_INHIBITOR);
            repressor_participation.participant.set(repressor_fc);
//
            Participation& promoter_participation = this->participations.create(uri + "_promoter");
            promoter_participation.roles.set(SBO_PROMOTER);
            promoter_participation.participant.set(promoter_fc);
            
            this->repressor.addValidationRule(libsbol_rule_19);
            this->targetPromoter.addValidationRule(libsbol_rule_19);
        }
        AliasedProperty<FunctionalComponent> repressor;
        AliasedProperty<FunctionalComponent> targetPromoter;
    };

    class SmallMoleculeInhibitionInteraction : public Interaction
    {
    public:
        SmallMoleculeInhibitionInteraction(std::string uri, ComponentDefinition& ligand, ComponentDefinition& transcription_factor) :
            Interaction(SBOL_INTERACTION, uri, SBO_INHIBITION),
            ligand(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#ligand", '0', '1', ValidationRules({})),
            transcriptionFactor(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#transcriptionFactor", '0', '1', ValidationRules({}))
        {
            if (!ligand.types.find(BIOPAX_SMALL_MOLECULE))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid small molecule ligand specified for SmallMoleculeInhibitionInteraction. The repressor must have type BIOPAX_SMALL_MOLECULE");
            if (!transcription_factor.types.find(BIOPAX_PROTEIN))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid transcription factor specified for SmallMoleculeInhibitionInteraction. The transcription factor must have type BIOPAX_PROTEIN");
            
            FunctionalComponent& ligand_fc = this->ligand.define(ligand);
            FunctionalComponent& transcription_factor_fc = this->transcriptionFactor.define(transcription_factor);
            
            Participation& ligand_participation = this->participations.create(uri + "_ligand");
            ligand_participation.roles.set(SBO_INHIBITOR);
            ligand_participation.participant.set(ligand_fc);
            
            Participation& transcription_factor_participation = this->participations.create(uri + "_transcription_factor");
            transcription_factor_participation.roles.set(SBO_INHIBITED);
            transcription_factor_participation.participant.set(transcription_factor_fc);
            
            this->ligand.addValidationRule(libsbol_rule_19);
            this->transcriptionFactor.addValidationRule(libsbol_rule_19);
        }
        AliasedProperty<FunctionalComponent> ligand;
        AliasedProperty<FunctionalComponent> transcriptionFactor;
    };
    
    class GeneProductionInteraction : public Interaction
    {
    public:
        GeneProductionInteraction(std::string uri, ComponentDefinition& gene, ComponentDefinition& product) :
            Interaction(SBOL_INTERACTION, uri, SBO_GENETIC_PRODUCTION),
            gene(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#gene", '0', '1', ValidationRules({})),
            product(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#product", '0', '1', ValidationRules({}))
        {
            if (!gene.types.find(BIOPAX_DNA))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid coding sequence specified for GeneProductionInteraction. The coding sequence must have type BIOPAX_DNA");
            if (!(product.types.find(BIOPAX_PROTEIN) || product.types.find(BIOPAX_RNA)))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid gene product specified for GeneProductionInteraction. The product be of type BIOPAX_PROTEIN or BIOPAX_RNA");
            
            FunctionalComponent& gene_fc = this->gene.define(gene);
            FunctionalComponent& product_fc = this->product.define(product);
            
            Participation& gene_participation = this->participations.create(uri + "_gene");
            gene_participation.roles.set(SBO "0000645");
            gene_participation.participant.set(gene_fc);
            
            Participation& product_participation = this->participations.create(uri + "_product");
            product_participation.roles.set(SBO_PRODUCT);
            product_participation.participant.set(product_fc);
            
            this->gene.addValidationRule(libsbol_rule_19);
            this->product.addValidationRule(libsbol_rule_19);
        }
        AliasedProperty<FunctionalComponent> gene;
        AliasedProperty<FunctionalComponent> product;
    };
    
    class TranscriptionalActivationInteraction : public Interaction
    {
    public:
        TranscriptionalActivationInteraction(std::string uri, ComponentDefinition& activator, ComponentDefinition& target_promoter) :
            Interaction(SBOL_INTERACTION, uri, SBO_STIMULATION),
            activator(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#activator", '0', '1', ValidationRules({})),
            targetPromoter(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#targetPromoter", '0', '1', ValidationRules({}))
        {
            if (!activator.types.find(BIOPAX_PROTEIN))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid repressor specified for TranscriptionalRepressionInteraction. The repressor must have type BIOPAX_PROTEIN");
            if (!target_promoter.types.find(BIOPAX_DNA))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid target promoter specified for TranscriptionalRepressionInteraction. The promoter must have type BIOPAX_DNA");

            FunctionalComponent& activator_fc = this->activator.define(activator);
            FunctionalComponent& promoter_fc = this->targetPromoter.define(target_promoter);

            Participation& activator_participation = this->participations.create(uri + "_activator");
            activator_participation.roles.set(SBO_STIMULATOR);
            activator_participation.participant.set(activator_fc);

            Participation& promoter_participation = this->participations.create(uri + "_promoter");
            promoter_participation.roles.set(SBO_PROMOTER);
            promoter_participation.participant.set(promoter_fc);
            
            this->activator.addValidationRule(libsbol_rule_19);
            this->targetPromoter.addValidationRule(libsbol_rule_19);
        }
        AliasedProperty<FunctionalComponent> activator;
        AliasedProperty<FunctionalComponent> targetPromoter;
    };

    class SmallMoleculeActivationInteraction : public Interaction
    {
    public:
        SmallMoleculeActivationInteraction(std::string uri, ComponentDefinition& ligand, ComponentDefinition& transcription_factor) :
            Interaction(SBOL_INTERACTION, uri, SBO_STIMULATION),
            ligand(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#ligand", '0', '1', ValidationRules({})),
            transcriptionFactor(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#transcriptionFactor", '0', '1', ValidationRules({}))
        {
            if (!ligand.types.find(BIOPAX_SMALL_MOLECULE))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid small molecule ligand specified for SmallMoleculeInhibitionInteraction. The repressor must have type BIOPAX_SMALL_MOLECULE");
            if (!transcription_factor.types.find(BIOPAX_PROTEIN))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid transcription factor specified for SmallMoleculeInhibitionInteraction. The transcription factor must have type BIOPAX_PROTEIN");
    
            FunctionalComponent& ligand_fc = this->ligand.define(ligand);
            FunctionalComponent& transcription_factor_fc = this->transcriptionFactor.define(transcription_factor);
            
            Participation& ligand_participation = this->participations.create(uri + "_ligand");
            ligand_participation.roles.set(SBO_STIMULATOR);
            ligand_participation.participant.set(ligand_fc);
            
            Participation& transcription_factor_participation = this->participations.create(uri + "_transcription_factor");
            transcription_factor_participation.roles.set(SBO_STIMULATED);
            transcription_factor_participation.participant.set(transcription_factor_fc);
            
            this->ligand.addValidationRule(libsbol_rule_19);
            this->transcriptionFactor.addValidationRule(libsbol_rule_19);
        }
        AliasedProperty<FunctionalComponent> ligand;
        AliasedProperty<FunctionalComponent> transcriptionFactor;
    };
    
    class EnzymeCatalysisInteraction : public Interaction
    {
    public:
        EnzymeCatalysisInteraction(std::string uri, ComponentDefinition& enzyme, std::vector<ComponentDefinition*> substrates, std::vector<ComponentDefinition*> products) : EnzymeCatalysisInteraction(uri, enzyme, substrates, products, {}, {}) {};
        
        EnzymeCatalysisInteraction(std::string uri, ComponentDefinition& enzyme, std::vector<ComponentDefinition*> substrates, std::vector<ComponentDefinition*> products, std::vector<ComponentDefinition*> cofactors, std::vector<ComponentDefinition*> sideproducts) :
            Interaction(SBOL_INTERACTION, uri, SBO_CONVERSION),
            enzyme(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#enzyme", '0', '1', ValidationRules({})),
            substrates(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#substrates", '0', '*', ValidationRules({})),
            products(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#products", '0', '*', ValidationRules({})),
            cofactors(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#cofactors", '0', '*', ValidationRules({})),
            sideproducts(this, SBOL_FUNCTIONAL_COMPONENTS, SYSBIO_URI "#sideproducts", '0', '*', ValidationRules({}))
        {
            if (!enzyme.types.find(BIOPAX_PROTEIN))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid enzyme specified for EnzymaticCatalysisInteraction. The enzyme must have type BIOPAX_PROTEIN");
            for (auto & S : substrates)
                if (!S->types.find(BIOPAX_SMALL_MOLECULE))
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid substrates specified for EnzymeCatalysisInteraction. Substrates must have type BIOPAX_SMALL_MOLECULE");
            for (auto & P : products)
                if (!P->types.find(BIOPAX_SMALL_MOLECULE))
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid products specified for EnzymeCatalysisInteraction. Products must have type BIOPAX_SMALL_MOLECULE");
            for (auto & C : cofactors)
                if (!C->types.find(BIOPAX_SMALL_MOLECULE))
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid cofactors specified for EnzymeCatalysisInteraction. Cofactors must have type BIOPAX_SMALL_MOLECULE");
            for (auto & X : sideproducts)
                if (!X->types.find(BIOPAX_SMALL_MOLECULE))
                    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid sideproducts specified for EnzymeCatalysisInteraction. Sideproducts must have type BIOPAX_SMALL_MOLECULE");
            
            FunctionalComponent& enzyme_fc = this->enzyme.define(enzyme);
            Participation& enzyme_participation = this->participations.create(uri + "_enzyme");
            enzyme_participation.roles.set(SBO_ENZYME);
            enzyme_participation.participant.set(enzyme_fc);
            
            for (int i = 0; i < substrates.size(); ++i)
            {
                ComponentDefinition& S = *substrates[i];
                FunctionalComponent& substrate_fc = this->substrates.define(S);
                Participation& substrate_participation = this->participations.create(uri + "_substrate_" + std::to_string(i));
                substrate_participation.roles.set(SBO_SUBSTRATE);
                substrate_participation.participant.set(substrate_fc);
            }
            for (int i = 0; i < products.size(); ++i)
            {
                ComponentDefinition& P = *products[i];
                FunctionalComponent& product_fc = this->products.define(P);
                Participation& product_participation = this->participations.create(uri + "_product_" + std::to_string(i));
                product_participation.roles.set(SBO_PRODUCT);
                product_participation.participant.set(product_fc);
            }
            for (int i = 0; i < cofactors.size(); ++i)
            {
                ComponentDefinition& C = *cofactors[i];
                FunctionalComponent& cofactor_fc = this->cofactors.define(C);
                Participation& cofactor_participation = this->participations.create(uri + "_cofactor_" + std::to_string(i));
                cofactor_participation.roles.set(SBO_COFACTOR);
                cofactor_participation.participant.set(cofactor_fc);
            }
            for (int i = 0; i < sideproducts.size(); ++i)
            {
                ComponentDefinition& X = *sideproducts[i];
                FunctionalComponent& sideproduct_fc = this->sideproducts.define(X);
                Participation& sideproduct_participation = this->participations.create(uri + "_sideproduct_" + std::to_string(i));
                sideproduct_participation.roles.set(SBO_SIDEPRODUCT);
                sideproduct_participation.participant.set(sideproduct_fc);
            }
            this->enzyme.addValidationRule(libsbol_rule_19);
            this->substrates.addValidationRule(libsbol_rule_19);
            this->products.addValidationRule(libsbol_rule_19);
            this->cofactors.addValidationRule(libsbol_rule_19);
            this->sideproducts.addValidationRule(libsbol_rule_19);

        }
        
        AliasedProperty<FunctionalComponent> enzyme;
        AliasedProperty<FunctionalComponent> substrates;
        AliasedProperty<FunctionalComponent> products;
        AliasedProperty<FunctionalComponent> cofactors;
        AliasedProperty<FunctionalComponent> sideproducts;
    };
    
};



#endif
