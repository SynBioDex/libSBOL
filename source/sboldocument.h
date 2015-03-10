#include <unordered_map>

namespace sbol {
	class TopLevel;
	class SBOLDocument {
		//std::string identity;  // @todo make URI type instead of string?
		//      std::string persistentIdentity;  // @todo make URI type instead of string?
		//int majorVersion;
		//int minorVersion;
		//std::string timeStamp;

	public:

		//Identified(std::string uri_prefix, std::string id);
		SBOLDocument();
			/*collections = new HashMap<URI, Collection>();
			componentDefinitions = new HashMap<URI, ComponentDefinition>();
			models = new HashMap<URI, Model>();
			moduleDefinitions = new HashMap<URI, ModuleDefinition>();
			sequences = new HashMap<URI, Sequence>();
			nameSpaces = new HashMap<URI, NamespaceBinding>();*/

		std::unordered_map<std::string, sbol::TopLevel*> SBOLObjects;
		// SBOLDocument::getComponentDefinitions
		// getSBOLObject(uri)
		// doc.SBOLObjects[URI]
		// obj.addToDocument(doc)

	};
}