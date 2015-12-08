
#include "sbol.h"

#include <string>

namespace sbol
{
	class SequenceAnnotationExt : public SequenceAnnotation
	{
	public:
		List<URIProperty> roles;

		SequenceAnnotationExt(std::string uri_prefix = SBOL_URI "/SequenceAnnotationExt", std::string id = "example", int start = -1, int end = -1, std::string role = "SO_0000001") : SequenceAnnotationExt(SBOL_SEQUENCE_ANNOTATION, uri_prefix, id, start, end, role)
		{
		}
		~SequenceAnnotationExt() {};
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
		SequenceAnnotationExt(sbol_type type, std::string uri_prefix, std::string id, int start, int end, std::string role) :
			SequenceAnnotation(type, uri_prefix, id, start, end),
			roles(SBOL_ROLES, this, role)
		{
		}
	};
}
