#include "document.h"

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <raptor2.h>

using namespace sbol;
using namespace std;

unordered_map<string, SBOLObject&(*)()> sbol::SBOL_DATA_MODEL_REGISTER =
{
	// Typecast proxy constructors to a constructor for SBOL
	// This makes some ugly syntax, but library users should never see it.
	make_pair(UNDEFINED, &create<SBOLObject>),
	make_pair(SBOL_COMPONENT_DEFINITION, (SBOLObject&(*)()) &create<ComponentDefinition>),
	make_pair(SBOL_SEQUENCE_ANNOTATION, (SBOLObject&(*)()) &create<SequenceAnnotation>)

};

void Document::parse_objects(void* user_data, raptor_statement* triple)
{

	//Document *doc = (Document *)user_data;
	////vector<raptor_statement > *triples = (vector<raptor_statement > *)user_data;
	////triples->push_back(*triple);
	////user_data = triples;
	////cout << raptor_term_to_string(((vector<raptor_statement > *)user_data)->back().subject) << endl;
	////cout << ((vector<raptor_statement > *)user_data)->size() << endl;

	//string subject = reinterpret_cast<char*>(raptor_term_to_string(triple->subject));
	//string predicate = reinterpret_cast<char*>(raptor_term_to_string(triple->predicate));
	//string object = reinterpret_cast<char*>(raptor_term_to_string(triple->object));

	//// Triples that have a predicate matching the following uri indicate that new SBOL object should be constructred
	//if (predicate.compare("<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>") == 0)
	//{
	//	// Checks if the object has already been created and whether a constructor for this type of object exists
	//	string new_id = subject.substr(1, subject.length() - 2);
	//	string sbol_class = object.substr(1, object.length() - 2);
	//	cout << "Instantiating " << new_id << sbol_class << endl;

	//	if ((doc->SBOLObjects.count(new_id) == 0) && (SBOL_DATA_MODEL_REGISTER.count(sbol_class) == 1))
	//	{

	//		SBOLObject& new_obj = SBOL_DATA_MODEL_REGISTER[ sbol_class ]();
	//		cout << doc->SBOLObjects.size() << endl;

	//	}
	//}

}

void Document::parse_properties(void* user_data, raptor_statement* triple)
{
	Document *doc = (Document *)user_data;

	string subject = reinterpret_cast<char*>(raptor_term_to_string(triple->subject));
	string predicate = reinterpret_cast<char*>(raptor_term_to_string(triple->predicate));
	string object = reinterpret_cast<char*>(raptor_term_to_string(triple->object));

	string sbol_property = predicate.substr(1, subject.length() - 2);
	std::size_t found = sbol_property.find('#');
	if (found != std::string::npos)
		sbol_property = sbol_property.substr(0, found);

	// Triples that have a predicate matching the following uri indicate that new SBOL object should be constructred
	if (predicate.compare(SBOL_URI) == 0)
	{
		// Checks if the object has already been created and whether a constructor for this type of object exists
		string id = subject.substr(1, subject.length() - 2);
		string property_value = object;
		
		cout << id << property_value << endl;
	}

}


void Document::read(std::string filename)
{

	FILE* fh = fopen(filename.c_str(), "rb");
	raptor_parser* rdf_parser = raptor_new_parser(this->rdf_graph, "rdfxml");
	raptor_iostream* ios = raptor_new_iostream_from_file_handle(this->rdf_graph, fh);
	if (ios == NULL) cout << "Invalid file" << endl; else cout << "Valid file" << endl;
	unsigned char *uri_string;
	raptor_uri *uri, *base_uri;
	
	//vector<raptor_statement> *user_data = new vector<raptor_statement>;
	
	// Wipe existing contents of this Document
	raptor_free_world(this->rdf_graph);  //  Probably need to free other objects as well...
	this->rdf_graph = raptor_new_world();
	cout << "Wiping old document" << endl;
	cout << SBOLObjects.size() << endl;
	SBOLObjects.clear();
	cout << this->SBOLObjects.size() << endl;

	void *user_data = this;
	raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_objects);


	//cout << reinterpret_cast<char*>(raptor_term_to_string(((raptor_statement *)user_data)->subject)) << endl;
	//triple = (raptor_statement *)&user_data;
	//cout << raptor_term_to_string(triple->subject) << endl;

	raptor_uri *sbol_uri = raptor_new_uri(this->rdf_graph, (const unsigned char *)SBOL_URI "#");

	raptor_parser_parse_iostream(rdf_parser, ios, sbol_uri);
	raptor_parser_parse_iostream(rdf_parser, ios, NULL);


	//raptor_parser_set_statement_handler(rdf_parser, user_data, this->parse_properties);
	//raptor_parser_parse_iostream(rdf_parser, ios, sbol_uri);
	raptor_free_parser(rdf_parser);

	//raptor_free_uri(base_uri);
	//raptor_free_uri(uri);
	//raptor_free_memory(uri_string);

}


void SBOLObject::serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world)
{
	cout << "Serializing object" << endl;

	// Check if there is an RDF graph associated with this SBOLObject.  Only TopLevel objects can be belong to SBOL Documents, so
	// only TopLevel objects have a valid back-pointer.
	//
	// The only other type of SBOL Object that can serialize besides TopLevel are objects
	// that form a composite with a TopLevel object.  In this case, the TopLevel object will pass the
	// pointer to the RDF graph to its composite objects

	if (doc)
	{
		sbol_world = doc->getWorld();
	}
	if (sbol_world)
	{
		// This RDF triple makes the following statement:
		// "This instance of an SBOL object belongs to class X"
		raptor_statement *triple = raptor_new_statement(sbol_world);
		std::string subject = identity.get();
		std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
		std::string object = type;

		triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
		triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
		triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

		cout << subject << predicate << object << endl;

		// Write the triples
		raptor_serializer_serialize_statement(sbol_serializer, triple);

		// Delete the triple 
		raptor_free_statement(triple);

		for (auto it = properties.begin(); it != properties.end(); ++it)
		{

			// This RDF triple makes the following statement:
			// "This SBOL object has a property called X and its value is Y"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);

			//std::string new_predicate = (SBOL_URI "#" + it->first);
			std::string new_predicate = it->first;
			std::string new_object = it->second.front();

			triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)new_predicate.c_str());
			triple2->object = raptor_new_term_from_literal(sbol_world, (const unsigned char *)new_object.c_str(), NULL, NULL);

			cout << subject << new_predicate << new_object << endl;

			// Write the triples
			raptor_serializer_serialize_statement(sbol_serializer, triple2);

			// Delete the triple 
			raptor_free_statement(triple2);
		}

		// Serialize all properties corresponding to black diamonds in UML diagrams
		// RDF-XML list/container elements
		for (auto i = owned_objects.begin(); i != owned_objects.end(); ++i)
		{
			cout << "Serializing " << owned_objects.size() << " owned_objects" << endl;
			
			// Serialize each object in the object store that belongs to this property
			std::string property_name = i->first;
			vector<SBOLObject*> object_store = i->second;
			
			// This RDF triple makes the following statement:
			// "This instance of an SBOL object has property called X"
			raptor_statement *triple2 = raptor_new_statement(sbol_world);
			subject = identity.get();
			predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
			object = property_name;
			
			triple2->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
			triple2->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
			triple2->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());
			cout << subject << predicate << object << endl;

			// Write the triple2s
			raptor_serializer_serialize_statement(sbol_serializer, triple2);

			// Delete the triple 
			raptor_free_statement(triple2);

			int i_o = 0;
			for (auto o = object_store.begin(); o != object_store.end(); ++o)
			{
				SBOLObject* obj = *o;
				++i_o;
				cout << obj->type << endl;

				// This RDF triple makes the following statement:
				// "This instance of an SBOL object owns another SBOL object"
				raptor_statement *triple = raptor_new_statement(sbol_world);
				std::string subject = identity.get();
				std::string predicate = property_name;
				std::string object = obj->identity.get();
				
				//std::string subject = property_name;
				//std::string predicate = "http://www.w3.org/1999/02/22-rdf-syntax-ns#_" + std::to_string(i_o);
				//std::string object = obj->identity.get();

				//triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple->subject = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)subject.c_str());
				triple->predicate = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)predicate.c_str());
				triple->object = raptor_new_term_from_uri_string(sbol_world, (const unsigned char *)object.c_str());

				cout << subject << predicate << object << endl;

				// Write the triples
				raptor_serializer_serialize_statement(sbol_serializer, triple);

				// Delete the triple 
				raptor_free_statement(triple);

				// Recursive call to serialize child objects
				obj->serialize(sbol_serializer, sbol_world);
			}
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

	// Initialize raptor serializer
	FILE* fh = fopen(filename.c_str(), "wb");
	raptor_world* world = getWorld();
	raptor_serializer* sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	raptor_iostream* ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);
	raptor_uri *sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI "#");
	raptor_uri *purl_uri = raptor_new_uri(world, (const unsigned char *)PURL_URI "#");
	const unsigned char *sbol_prefix = (const unsigned char *)"sbol";
	const unsigned char *purl_prefix = (const unsigned char *)"dcterms";
	raptor_namespace_stack *sbol_namespaces = raptor_new_namespaces(world, 0);
	raptor_namespace *sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_namespace *purl_namespace = raptor_new_namespace_from_uri(sbol_namespaces, purl_prefix, purl_uri, 1);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, purl_namespace);
	raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);
	
	// Iterate through objects in document and serialize them
	for (auto obj_i = SBOLObjects.begin(); obj_i != SBOLObjects.end(); ++obj_i)
	{
		obj_i->second->serialize(sbol_serializer);
	}

	// End serialization 
	raptor_serializer_serialize_end(sbol_serializer);
	raptor_free_serializer(sbol_serializer);
	raptor_free_iostream(ios);
	fclose(fh);
};