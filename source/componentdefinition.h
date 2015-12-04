#include "toplevel.h"
#include "sequenceannotation.h"
#include "component.h"
#include <string>

namespace sbol 
{

	//class SequenceAnnotation;

	class ComponentDefinition : public TopLevel
	{
	public:
		List<URIProperty> types;
		List<URIProperty> roles;
		//OwnedObjects<SequenceAnnotation> sequenceAnnotations;
		ReferencedObject sequence;
		List<OwnedObject<SequenceAnnotation>> sequenceAnnotations;
		List<OwnedObject<Component>> components;


		ComponentDefinition(std::string uri_prefix = SBOL_URI "/ComponentDefinition",
			std::string display_id = "example",
			std::string type = SO_UNDEFINED,
			std::string role = SO_UNDEFINED,
			std::string name = "",
			std::string description = "",
			std::string version = "1.0.0") :
			ComponentDefinition(SBOL_COMPONENT_DEFINITION, uri_prefix, display_id, type, role, name, description, version)
		{
		}
	protected:
		// This protected constructor is a delegate constructor.  It initializes ComponentDefinitions with the corresponding sbol_type_uri 
		ComponentDefinition(sbol_type sbol_type_uri, std::string uri_prefix, std::string display_id, std::string type, std::string role, std::string name, std::string description, std::string version) :
			TopLevel(sbol_type_uri, uri_prefix, display_id, name, description, version),
			types(SBOL_TYPE, this, type),
			roles(SBOL_ROLE, this, role),
			sequence(SBOL_SEQUENCE_PROPERTY, this, ""),
			sequenceAnnotations(SBOL_SEQUENCE_ANNOTATIONS, this),
			components(SBOL_COMPONENTS, this)
		{
		}
	};
}