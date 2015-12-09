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
		SequenceAnnotation(std::string uri_prefix = SBOL_URI "/SequenceAnnotation", std::string id = "example", int start = -1, int end = -1) : SequenceAnnotation(SBOL_SEQUENCE_ANNOTATION, uri_prefix, id, start, end)
		{
		}
		~SequenceAnnotation() {};
	
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
		SequenceAnnotation(sbol_type type, std::string uri_prefix, std::string id, int start, int end) :
			Identified(type, uri_prefix, id, "", "", ""),
			locations(SBOL_LOCATIONS, this)
		{
		}
	};
}

#endif