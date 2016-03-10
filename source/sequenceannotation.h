#ifndef ANNOTATION_INCLUDED
#define ANNOTATION_INCLUDED

#include "toplevel.h"
#include "location.h"

#include <string>

namespace sbol 
{
	class SequenceAnnotation : public Identified
	{
	public:
		List<OwnedObject<Location>> locations;
        
        SequenceAnnotation(std::string uri = DEFAULT_NS "/SequenceAnnotation/example") : SequenceAnnotation(SBOL_SEQUENCE_ANNOTATION, uri) {};

        SequenceAnnotation(std::string uri_prefix, std::string display_id, std::string version) : SequenceAnnotation(SBOL_SEQUENCE_ANNOTATION, uri_prefix, display_id, version) {};

        
        ~SequenceAnnotation() {};
	
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
        SequenceAnnotation(sbol_type type, std::string uri) :
            Identified(type, uri),
            locations(SBOL_LOCATIONS, this)
            {
            };
        
        SequenceAnnotation(sbol_type type, std::string uri_prefix, std::string display_id, std::string version) :
			Identified(type, uri_prefix, display_id, version),
			locations(SBOL_LOCATIONS, this)
            {
            };
	};
    

}

#endif