/**
 * @file    interaction.h
 * @brief   Interaction class
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

#ifndef INTERACTION_INCLUDED
#define INTERACTION_INCLUDED

#include "identified.h"
#include "participation.h"
#include "measurement.h"

namespace sbol
{
    /// The Interaction class provides more detailed descriptionof how the FunctionalComponents are intended to work together. For example, this class can be used to represent different forms of genetic regulation (e.g., transcriptional activation or repression), processes from the central dogma of biology (e.g. transcription and translation), and other basic molecular interactions (e.g., non-covalent binding or enzymatic phosphorylation).
	class SBOL_DECLSPEC Interaction : public Identified
	{

	public:
        /// Construct an Interaction
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param interaction_type A Systems Biology Ontology term that describes a biochemical interaction
        Interaction(std::string uri = "example", std::string interaction_type = SBO_INTERACTION) : Interaction(SBOL_INTERACTION, uri, interaction_type) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        Interaction(rdf_type type, std::string uri, std::string interaction_type) :
            Identified(type, uri),
            functionalComponents(this, SBOL_FUNCTIONAL_COMPONENTS, '0', '*', { libsbol_rule_18 }),
            types(this, SBOL_TYPES, '1', '*', ValidationRules({}), interaction_type),
            participations(this, SBOL_PARTICIPATIONS, '0', '*', ValidationRules({})),
            measurements(this, SBOL_MEASUREMENTS, '0', '*', ValidationRules({}))
            {
                hidden_properties.push_back(SBOL_FUNCTIONAL_COMPONENTS);
            };
        
        /// The types property is a REQUIRED set of URIs that describes the behavior represented by an Interaction.  The types property MUST contain one or more URIs that MUST identify terms from appropriate ontologies. It is RECOMMENDED that at least one of the URIs contained by the types property refer to a term from the occurring entity branch of the Systems Biology Ontology (SBO). (See http://www.ebi.ac.uk/sbo/main/) The following table provides a list of possible SBO terms for the types property and their corresponding URIs.
        /// | Type                 | URI for SBO Term                                 | LibSBOL symbol           |
        /// | :------------------- | :----------------------------------------------- | :----------------------- |
        /// | Biochemical Reaction | http://identifiers.org/biomodels.sbo/SBO:0000176 | SBO_BIOCHEMICAL_REACTION |
        /// | Inhibition           | http://identifiers.org/biomodels.sbo/SBO:0000169 | SBO_INHIBITION           |
        /// | Stimulation          | http://identifiers.org/biomodels.sbo/SBO:0000170 | SBO_STIMULATION          |
        /// | Genetic Production   | http://identifiers.org/biomodels.sbo/SBO:0000589 | SBO_GENETIC_PRODUCTION   |
        /// | Non-Covalent Binding | http://identifiers.org/biomodels.sbo/SBO:0000177 | SBO_NONCOVALENT_BINDING  |
        /// | Degradation          | http://identifiers.org/biomodels.sbo/SBO:0000179 | SBO_DEGRADATION          |
        /// | Control              | http://identifiers.org/biomodels.sbo/SBO:0000168 | SBO_CONTROL              |
		URIProperty types;
        
        /// The participations property is an OPTIONAL and MAY contain a set of Participation objects, each of which identifies the roles that its referenced FunctionalComponent plays in the Interaction. Even though an Interaction generally contains at least one Participation, the case of zero Participation objects is allowed because it is plausible that a designer might want to specify that an Interaction will exist, even if its participants have not yet been determined.
		OwnedObject<Participation> participations;
        
        OwnedObject<FunctionalComponent> functionalComponents;
        
        /// The measurements property links an Interaction to parameters or measurements and their associated units. For example, an Interaction that represents a chemical reaction may have parameters added to it and each Participation it contains to capture its chemical kinetic rate and the stoichiometries of its reactants and products.
        OwnedObject<Measurement> measurements;
        
        virtual ~Interaction() { owned_objects.erase(SBOL_FUNCTIONAL_COMPONENTS); };
	};
}

#endif
