#ifndef INTERACTION_INCLUDED
#define INTERACTION_INCLUDED

#include "identified.h"
#include "participation.h"

namespace sbol
{
    /// The Interaction class provides more detailed descriptionof how the FunctionalComponents are intended to work together. For example, this class can be used to represent different forms of genetic regulation (e.g., transcriptional activation or repression), processes from the central dogma of biology (e.g. transcription and translation), and other basic molecular interactions (e.g., non-covalent binding or enzymatic phosphorylation).
	class Interaction : public Identified
	{

	public:
		List<URIProperty> types;
		List<OwnedObject<Participation>> participations;
		
        Interaction(std::string uri = DEFAULT_NS "/Interaction/example", std::string interaction_type = SBO_INTERACTION) : Interaction(SBOL_INTERACTION, uri, interaction_type) {};
        
        Interaction(std::string uri_prefix, std::string display_id, std::string version, std::string interaction_type) : Interaction(SBOL_INTERACTION, uri_prefix, display_id, version, interaction_type) {};
        
        virtual ~Interaction() {};
        
	protected:
        Interaction(sbol_type type, std::string uri, std::string interaction_type) :
            Identified(type, uri),
            types(SBOL_TYPES, this, interaction_type),
            participations(SBOL_PARTICIPATIONS, this)
            {
            };
        Interaction(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string interaction_type) :
			Identified(type, uri_prefix, display_id, version),
			types(SBOL_TYPES, this, interaction_type),
			participations(SBOL_PARTICIPATIONS, this)
			{
            };
	};
}

#endif