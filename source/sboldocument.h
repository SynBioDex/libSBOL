//#include <libxml/xmlexports.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "generictoplevel.h"
#include "componentdefinition.h"

#include <unordered_map>

namespace sbol {
	class SBOLDocument {

		static const sbol_type type = SBOL_DOCUMENT;
		xmlDocPtr xml;
	public:

		SBOLDocument() {};
		std::unordered_map<std::string, sbol::TopLevel*> SBOLObjects;
		std::unordered_map<std::string, sbol::TopLevel*> componentDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> models;
		std::unordered_map<std::string, sbol::TopLevel*> moduleDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> sequences;
		std::unordered_map<std::string, sbol::TopLevel*> nameSpaces;

		TopLevel& getTopLevel(std::string);


	};
}

