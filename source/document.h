//#include <libxml/xmlexports.h>
#include "generictoplevel.h"
#include "componentdefinition.h"

#include <raptor2.h>
#include <unordered_map>

namespace sbol {
	class Document {
	private:
		raptor_world *rdf_graph;
	public:

		Document() :
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
		template <class SBOLClass > void add(SBOLClass& sbol_obj);
		void write();
	};

	// Coding pitfall:  It's important that the SBOL object represented by sbol_obj is passed by reference not by value!
	template <class SBOLClass > void Document::add(SBOLClass& sbol_obj)
	{
		SBOLObjects[sbol_obj.identity.get()] = (TopLevel*)&sbol_obj;
	};

}

