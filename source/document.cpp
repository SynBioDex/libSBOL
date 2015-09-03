#include "document.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <raptor2.h>

using namespace sbol;
using namespace std;

void SBOLObject::serialize(raptor_serializer* sbol_serializer)
{
	//raptor_serializer* sbol_serializer = NULL;
	//unsigned char *uri_string;
	//raptor_uri *sbol_uri, *subject;
	//raptor_term *parent_serialization_object, *nucleotides_property;
	//const unsigned char *sbol_prefix;
	//raptor_namespace_stack *sbol_namespaces;
	//raptor_namespace *sbol_namespace;
	for (auto it = properties.begin(); it != properties.end(); ++it)
	{
		if (doc)
		{
			cout << "Serializing object" << endl;
			raptor_world *sbol_world = doc->getWorld();

			//std::string test = "http://sbolstandard.org/examples/example1";
			//const unsigned char *subject = (const unsigned char *)test.c_str();
			//const unsigned char *predicate = (const unsigned char *)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
			//const unsigned char *object = (const unsigned char *)"http://sbolstandard.org/v2#Sequence";

			//raptor_statement *triple = raptor_new_statement(sbol_world);

			//triple->subject = raptor_new_term_from_uri_string(sbol_world, subject);
			//triple->predicate = raptor_new_term_from_uri_string(sbol_world, predicate);
			//triple->object = raptor_new_term_from_uri_string(sbol_world, object);

			//raptor_statement *triple2 = raptor_new_statement(sbol_world);

			//const unsigned char *new_predicate = (const unsigned char *)(SBOL_URI "#nucleotides");
			//const unsigned char *new_object = (const unsigned char *)"atcg";

			//triple2->subject = raptor_new_term_from_uri_string(sbol_world, subject);
			//triple2->predicate = raptor_new_term_from_uri_string(sbol_world, new_predicate);
			//triple2->object = raptor_new_term_from_literal(sbol_world, new_object, NULL, NULL);

			raptor_statement *triple = raptor_new_statement(sbol_world);

			// This RDF triple makes the following statement:
			// "This instance of an SBOL object belongs to the identified class"
			//const unsigned char *subject = (const unsigned char *)identity.get().c_str();
			//const unsigned char *predicate = (const unsigned char *)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
			//const unsigned char *object = (const unsigned char *)type.c_str();
			std::string subject = identity.get();
			std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
			std::string object = type;


			cout << identity.get() << '\n' << subject << endl;
			cout << "http://www.w3.org/1999/02/22-rdf-syntax-ns#type" << '\n' << predicate << endl;
			cout << type << '\n' << object << endl;
			triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
			triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());
			
			raptor_statement *triple2 = raptor_new_statement(sbol_world);

			std::string new_predicate = (SBOL_URI "#" + it->first);
			std::string new_object = it->second.front();

			cout << (SBOL_URI "#" + it->first) << '\n' << new_predicate << endl;
			cout << it->second.front() << '\n' << new_object << endl;

			triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)new_predicate.c_str());
			triple2->object = raptor_new_term_from_literal(sbol_world, (const unsigned char *)new_object.c_str(), NULL, NULL);

			// Write the triple
			raptor_serializer_serialize_statement(sbol_serializer, triple);
			raptor_serializer_serialize_statement(sbol_serializer, triple2);
			// Delete the triple 
			//delete subject;
			//delete predicate;
			//delete object;
			//raptor_free_statement(triple);

			//raptor_free_serializer(sbol_serializer);
			//raptor_free_iostream(ios);
			//raptor_free_uri(sbol_uri);
			//raptor_free_memory(uri_string);
			//raptor_free_world(world);
		}
	}
}

void TopLevel::addToDocument(Document& doc)
{
	//doc.SBOLObjects[this->identity.get()] = this;
	doc.add(*this);
};

TopLevel& Document::getTopLevel(string uri)
{
    // @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return *(this->SBOLObjects[uri]);
};

raptor_world* Document::getWorld()
{
	// @TODO validate if object is TopLevel or else trigget a libSBOL error
	// @TODO return libSBOL error if URI not found
	return (this->rdf_graph);
};

void Document::write(std::string filename)
{
	TopLevel *tl;
	FILE* fh = fopen(filename.c_str(), "wb");
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	raptor_iostream* ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);
	raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	const unsigned char *sbol_prefix = (const unsigned char *)"sbol";
	raptor_namespace_stack *sbol_namespaces = raptor_new_namespaces(world, 0);
	raptor_namespace *sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);

	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		obj_i->second->serialize(sbol_serializer);
	}

	// End serialization 
	raptor_serializer_serialize_end(sbol_serializer);
};