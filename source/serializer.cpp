#define RAPTOR_STATIC

#include "sbol.h"

#include <iostream>
#include <vector>

#include <raptor2.h>

using namespace std;
using namespace sbol;

#pragma message "XMLPUBVAR = " QUOTE(XMLPUBVAR)
#pragma message "__MINGW32__ = " QUOTE(__MINGW32__)
#pragma message "_WIN32 = " QUOTE(_WIN32)
#pragma message "LIBXML_STATIC = " QUOTE(LIBXML_STATIC)

int main() 
{
	raptor_iostream *ios;
	//raptor_world *world = NULL;
	//raptor_world *world;
	raptor_serializer* sbol_serializer = NULL;
	unsigned char *uri_string;
	raptor_uri *sbol_uri, *subject;
	raptor_term *parent_serialization_object, *nucleotides_property;
	const unsigned char *sbol_prefix;
	raptor_namespace_stack *sbol_namespaces;
	raptor_namespace *sbol_namespace;
	raptor_statement *triple, *triple2;
	std::string test;

	/* Start SBOL data model testing */
	cout << "Begin testing\n";
	sbol::ComponentDefinition sbol_obj = ComponentDefinition("http://examples.com", "cdef_obj");
	//sbol::ComponentDefinition sbol_obj = ComponentDefinition();

	cout << "Testing getters\n";
	cout << sbol_obj.identity.get() << endl;
	//cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.version.get() << endl;
	cout << sbol_obj.getTypeURI() << endl;

	/* Check libSBOL's implementation of internal types */
	SBOLObject &obj = SBOLObject();
	Identified &id = Identified();
	Documented &docum = Documented();
	cout << obj.getTypeURI() << endl;
	cout << id.getTypeURI() << endl;
	cout << docum.getTypeURI() << endl;

	/* Check that SBOL Properties are associated with their Owner Objects.  This is crucial for constructing RDF triples */
	cout << id.identity.getTypeURI() << endl;
	SBOLObject &owner = id.identity.getOwner();

	cout << owner.getTypeURI() << endl;
	//cout << sbol_obj.timeStamp.getTypeURI() << sbol_obj.timeStamp.getTypeURI() << endl;
	//cout << sbol_obj.version.getTypeURI() << sbol_obj.version.getTypeURI() << endl;

	/* Test registration of objects in the SBOL Document */
	/* There are two alternative methods for adding objects to the doc */
	cout << "Test registration of objects in the SBOL Document" << endl;
	Document doc = Document();
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	sbol_obj.addToDocument(doc);
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	cout << "Registered object at address " << &sbol_obj << endl;

	/* Test template function implementation for 'add' that allows user to add any SBOLObject to a document */
	cout << "Test template function implementation for 'add' that allows user to add any SBOLObject to a document" << endl;
	id.identity.set("http://examples.com/Identified/0");
	doc.add<Identified>(id);
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;

	/* Test retrieval of objects from the doc */
	ComponentDefinition *cd = (ComponentDefinition *)doc.SBOLObjects[sbol_obj.identity.get()];
	cout << "Retrieved object at address " << cd << endl;

	/* Test iteration through document registry and export of URIs */
	cout << "Testing iteration through document registry and export of URIs" << endl;
	doc.write();

	/* Test Maven version properties */
	// Should catch an error because the object is a ComponentDefinition
	cout << "Testing version properties" << endl;
	TopLevel& tl = doc.getTopLevel("http://examples.com/cdef_obj/1.0.0");
	cout << tl.getTypeURI() << endl;
	cout << tl.version.get() << endl;
	tl.version.set("1.2.3-123");
	cout << tl.version.get() << endl;

	/* Exception handling*/
	int e = SBOLError(1, "Test");

	/* Begin serialization testing */
	raptor_world* world = doc.getWorld();
	FILE* fh = fopen("test.xml", "wb");
	sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);

	sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI);
	sbol_prefix = (const unsigned char *)"sbol";
	sbol_namespaces = raptor_new_namespaces(world, 0);
	sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);


	/* Make a triple with URI subject, URI predicate, literal object */
	parent_serialization_object = raptor_new_term_from_uri_string(world, (const unsigned char *)"http://examples.com/sequence");

	triple = raptor_new_statement(world);
	triple->subject = parent_serialization_object;
	triple->predicate = raptor_new_term_from_uri(world, raptor_new_uri(world, (const unsigned char *)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type"));
	//	triple->predicate = raptor_new_term_from_uri(world, sbol_obj.identity.get());
	triple->object = raptor_new_term_from_uri_string(world, (const unsigned char *)SBOL_URI "Sequence");

	nucleotides_property = raptor_new_term_from_uri_string(world, (const unsigned char *)SBOL_URI "nucleotides");

	triple2 = raptor_new_statement(world);
	triple2->subject = parent_serialization_object;
	triple2->predicate = nucleotides_property;
	triple2->object = raptor_new_term_from_literal(world,
		(const unsigned char*)"An example literal",
		NULL,
		NULL);

	////triple2->predicate = RAPTOR_TERM_TYPE_URI;
	////	triple->predicate = raptor_new_term_from_uri(world, sbol_obj.identity.get());

	/* Write the triple */
	raptor_serializer_serialize_statement(sbol_serializer, triple2);

	raptor_serializer_serialize_statement(sbol_serializer, triple);

	///* End serialization */
	raptor_serializer_serialize_end(sbol_serializer);

	///* Delete the triple */
	//raptor_free_statement(triple);
	raptor_free_serializer(sbol_serializer);
	raptor_free_iostream(ios);
	//raptor_free_uri(sbol_uri);
	//raptor_free_memory(uri_string);
	//raptor_free_world(world);

	getchar();
	return 0;
}
