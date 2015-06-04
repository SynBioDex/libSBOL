//#include <libxml/xmlexports.h>
#include "generictoplevel.h"
#include "componentdefinition.h"

#include <raptor2.h>
#include <unordered_map>

namespace sbol {
	class SBOLDocument {

		sbol_type type = SBOL_DOCUMENT;
		raptor_world *rdf_graph;

	public:

		SBOLDocument() :
			rdf_graph(raptor_new_world())
			{
			};
		std::unordered_map<std::string, sbol::TopLevel*> SBOLObjects;
		std::unordered_map<std::string, sbol::TopLevel*> componentDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> models;
		std::unordered_map<std::string, sbol::TopLevel*> moduleDefinitions;
		std::unordered_map<std::string, sbol::TopLevel*> sequences;
		std::unordered_map<std::string, sbol::TopLevel*> nameSpaces;

		TopLevel& getTopLevel(std::string);
		raptor_world* getWorld();

	};
}

