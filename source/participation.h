/**
 * @file    participation.h
 * @brief   Participation class
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

#ifndef PARTICIPATION_INCLUDED
#define PARTICIPATION_INCLUDED

#include "identified.h"
#include "measurement.h"

namespace sbol
{
    // Forward declaration of FunctionalComponent necessary for Participation.participant property
    class FunctionalComponent;
    
    /// Each Participation represents how a particular FunctionalComponent behaves in its parent Interaction.
    /// @ingroup sbol_core_data_model
    class SBOL_DECLSPEC Participation : public Identified
	{
	public:
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param participant A reference to the participating FunctionalComponent in the parent Interaction
        Participation(std::string uri = "example", std::string participant = "", std::string version = VERSION_STRING) : Participation(SBOL_PARTICIPATION, uri, participant, version) {};

        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param species A ComponentDefinition that represents one of the participating species in the parent Interaction
        Participation(std::string uri, ComponentDefinition& species, std::string version = VERSION_STRING) :
            Participation(SBOL_PARTICIPATION, uri, "", version)
            {
            };

        /// Constructor used for defining extension classes
        /// @param type The RDF type for an extension class derived from this one
        Participation(rdf_type type, std::string uri, std::string participant, std::string version) :
            Identified(type, uri, version),
            roles(this, SBOL_ROLES, '0', '*', ValidationRules({})),
            participant(this, SBOL_PARTICIPANT, SBOL_FUNCTIONAL_COMPONENT, '1', '1', ValidationRules({}), participant),
            measurements(this, SBOL_MEASUREMENTS, '0', '*', ValidationRules({}))
            {
            };
        
        /// The roles property is an OPTIONAL set of URIs that describes the behavior of a Participation (and by extension its referenced FunctionalComponent) in the context of its parent Interaction. The roles property MAY contain one or more URIs that MUST identify terms from appropriate ontologies. It is  RECOMMENDED that at least one of the URIs contained by the types property refer to a term from the participant role branch of the SBO. The table below provides a list of possible SBO terms for the roles property and their corresponding URIs.
        /// | Role                  | Systems Biology Ontology Term                    | LibSBOL Symbol         |
        /// | :-------------------- | :----------------------------------------------- | :--------------------- |
        /// | Inhibitor             | http://identifiers.org/biomodels.sbo/SBO:0000020 | SBO_INHIBITOR          |
        /// | Stimulator            | http://identifiers.org/biomodels.sbo/SBO:0000459 | SBO_STIMULATOR         |
        /// | Reactant              | http://identifiers.org/biomodels.sbo/SBO:0000010 | SBO_REACTANT           |
        /// | Product               | http://identifiers.org/biomodels.sbo/SBO:0000011 | SBO_PRODUCT            |
        /// | Ligand                | http://identifiers.org/biomodels.sbo/SBO:0000280 | SBO_LIGAND             |
        /// | Non-covalent Complex  | http://identifiers.org/biomodels.sbo/SBO:0000253 | SBO_NONCOVALENT_COMPLEX|
        /// If a Participation is well described by one of the terms from this table then its roles property MUST contain the URI that identifies this term. Lastly, if the roles property of a Participation contains multiple URIs, then they MUST identify non-conflicting terms. For example, the SBO terms “stimulator” and “inhibitor” would conflict.
		URIProperty roles;
        
        /// The participant property MUST specify precisely one FunctionalComponent object that plays the designated  role in its parent Interaction object.
        ReferencedObject participant;
        
        /// The measurements property links a Participation to parameters or measurements and their associated units. For example, an Interaction that represents a chemical reaction may have parameters added to it and each Participation it contains to capture its chemical kinetic rate and the stoichiometries of its reactants and products.
        OwnedObject<Measurement> measurements;
        
        void define(ComponentDefinition& species, std::string role = "");
        
        
        virtual ~Participation(){};
        
	};
}

#endif
