#include "generictoplevel.h"

#include <unordered_map>

namespace sbol {
	class SBOLDocument {
		//std::string identity;  // @todo make URI type instead of string?
		//      std::string persistentIdentity;  // @todo make URI type instead of string?
		//int majorVersion;
		//int minorVersion;
		//std::string timeStamp;
		static const sbol_type type = SBOL_DOCUMENT;

	public:

		//Identified(std::string uri_prefix, std::string id);
		SBOLDocument() {};
			/*collections = new HashMap<URI, Collection>();
			componentDefinitions = new HashMap<URI, ComponentDefinition>();
			models = new HashMap<URI, Model>();
			moduleDefinitions = new HashMap<URI, ModuleDefinition>();
			sequences = new HashMap<URI, Sequence>();
			nameSpaces = new HashMap<URI, NamespaceBinding>();*/

		std::unordered_map<std::string, sbol::TopLevel*> SBOLObjects;
		std::unordered_map<std::string, sbol::TopLevel*> componentDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> models;
		std::unordered_map<std::string, sbol::TopLevel*> moduleDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> sequences;
		std::unordered_map<std::string, sbol::TopLevel*> nameSpaces;

		TopLevel& getTopLevel(std::string);
		// SBOLDocument::getComponentDefinitions
		// getSBOLObject(uri)
		// doc.SBOLObjects[URI]
		// obj.addToDocument(doc)

	};
}