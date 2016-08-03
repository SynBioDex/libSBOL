#ifndef PARTICIPATION_INCLUDED
#define PARTICIPATION_INCLUDED

#include "identified.h"

namespace sbol
{
    // Forward declaration of FunctionalComponent necessary for Participation.participant property
    class FunctionalComponent;
    
    /// Each Participation represents how a particular FunctionalComponent behaves in its parent Interaction.
    /// @ingroup sbol_core_data_model
    class Participation : public Identified
	{
	public:
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
		List<URIProperty> roles;
        
        /// The participant property MUST specify precisely one FunctionalComponent object that plays the designated  role in its parent Interaction object.
        ReferencedObject participant;

        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param participant A reference to the participating FunctionalComponent in the parent Interaction
        Participation(std::string uri = DEFAULT_NS "/Participation/example", std::string participant = "") : Participation(SBOL_PARTICIPATION, uri, participant) {};

        Participation(std::string uri_prefix, std::string display_id, std::string version, std::string participant) : Participation(SBOL_PARTICIPATION, uri_prefix, display_id, version, participant) {};
        
        virtual ~Participation(){};
	protected:
        Participation(sbol_type type, std::string uri, std::string participant) :
            Identified(type, uri),
            roles(SBOL_ROLES, this),
            participant(SBOL_PARTICIPANT, SBOL_FUNCTIONAL_COMPONENT, this, participant)
            {
            };
        
        Participation(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string participant) :
			Identified(type, uri_prefix, display_id, version),
			roles(SBOL_ROLES, this),
			participant(SBOL_PARTICIPANT, SBOL_FUNCTIONAL_COMPONENT, this, participant)
            {
            };
	};
}

#endif