#include "toplevel.h"

#include <string>

namespace sbol 
{

	class SequenceAnnotation;

	class ComponentDefinition : public TopLevel
	{

	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
		ComponentDefinition(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string type, std::string role, std::string name, std::string description, std::string version) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, name, description),
			persistentIdentity(uri_prefix + "/" + display_id),
			version(SBOL_VERSION, this, version),
			types(SBOL_TYPE, this, type),
			roles(SBOL_ROLE, this, role),
			sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this)
		{
		}
	public:
		Property<std::string> persistentIdentity;
		Property<std::string> version;
		ListProperty<std::string> types;
		ListProperty<std::string> roles;
		OwnedObjects<SequenceAnnotation> sequenceAnnotations;

		ComponentDefinition(std::string uri_prefix = SBOL_URI "/ComponentDefinition", 
							std::string display_id = "example", 
							std::string type = SO_UNDEFINED, 
							std::string role =  SO_UNDEFINED,
							std::string name = "",
							std::string description = "",
							std::string version = "1.0.0") : 
		ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, type, role, name, description, version)
			{
			}
	};
}