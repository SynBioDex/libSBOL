#define RAPTOR_STATIC
#define SBOL_URI "http://sbolstandard.org/v2#"

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
	raptor_world *world = NULL;
	raptor_serializer* sbol_serializer = NULL;
	unsigned char *uri_string;
	raptor_uri *sbol_uri;
	raptor_uri *subject;
	raptor_term *parent_serialization_object, *nucleotides_property;
	const unsigned char *sbol_prefix;
	raptor_namespace_stack *sbol_namespaces;
	raptor_namespace *sbol_namespace;
	raptor_qname *sequence;

	raptor_statement* triple;
	raptor_statement* triple2;

	world = raptor_new_world();
	FILE* fh = fopen("test.xml", "wb");
	sbol_serializer = raptor_new_serializer(world, "rdfxml-abbrev");
	//raptor_serializer_set_option(sbol_serializer, RAPTOR_OPTION_SCANNING, NULL, 1);
	//raptor_rdfxmla_serialize_set_write_typed_nodes(sbol_serializer, 1);
	ios = raptor_new_iostream_to_file_handle(world, fh);
	raptor_serializer_start_to_iostream(sbol_serializer, NULL, ios);

	sbol_uri = raptor_new_uri(world, (const unsigned char *)SBOL_URI);
	sbol_prefix = (const unsigned char *)"sbol";
	sbol_namespaces = raptor_new_namespaces(world, 0);
	sbol_namespace = raptor_new_namespace_from_uri(sbol_namespaces, sbol_prefix, sbol_uri, 1);
	raptor_serializer_set_namespace_from_namespace(sbol_serializer, sbol_namespace);
	raptor_serializer_start_to_file_handle(sbol_serializer, NULL, fh);
	
	
	/* qnames */
	//sequence = raptor_new_qname(sbol_namespaces, (const unsigned char *)"Sequence", (const unsigned char *)"atcg");
	//sequence = raptor_new_qname_from_namespace_local_name(world, sbol_namespace, (const unsigned char *)"Sequence", (const unsigned char *)"atcg");
	//sequence = raptor_new_qname_from_namespace_local_name(world, sbol_namespace, (const unsigned char *)"Sequence", NULL); // does not result in a typed node
	//sequence = raptor_new_qname_from_namespace_uri(sbol_namespaces, raptor_new_uri(world, (const unsigned char *)"qname test"), 1);  // fails
	//int i = raptor_qname_write(sequence, ios);  // empty file
	//cout << "qname failure code:" << i << endl << raptor_qname_format_as_xml(sequence, NULL) << endl;
	


	/* Make a triple with URI subject, URI predicate, literal object */
	parent_serialization_object = raptor_new_term_from_uri_string(world, (const unsigned char *)"http://examples.com/sequence");

	triple = raptor_new_statement(world);
	triple->subject = parent_serialization_object;
	triple->predicate = raptor_new_term_from_uri(world, raptor_new_uri(world, (const unsigned char *)"http://www.w3.org/1999/02/22-rdf-syntax-ns#type"));
	//	triple->predicate = raptor_new_term_from_uri(world, sbol_obj.identity.get());
	triple->object = raptor_new_term_from_uri_string(world, (const unsigned char *)SBOL_URI "Sequence"); 
	
	
	//raptor_new_term_from_literal(world,
	//	(const unsigned char*)"An example literal",
	//	NULL,
	//	(const unsigned char*)"en");

	nucleotides_property = raptor_new_term_from_uri_string(world, (const unsigned char *)SBOL_URI "nucleotides");
	triple2 = raptor_new_statement(world);
	triple2->subject = parent_serialization_object;
	triple2->predicate = nucleotides_property;
	triple2->object = raptor_new_term_from_literal(world,
			(const unsigned char*)"An example literal",
			NULL,
			(const unsigned char*)"en");

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

	sbol::ComponentDefinition sbol_obj = ComponentDefinition("http://examples.com", "cdef_obj");
	cout << sbol_obj.identity.get() << endl;
	cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.version.get() << endl;

	SBOLDocument doc = SBOLDocument();
	cout << doc.SBOLObjects.size() << endl;
	sbol_obj.addToDocument(doc);
	cout << doc.SBOLObjects.size() << endl;
	
	// Should catch an error because the object is a ComponentDefinition
	TopLevel& tl = doc.getTopLevel("http://examples.com/cdef_obj/1.0.0");
	cout << tl.version.get() << endl;
	tl.version.set("1.2.3-123");
	cout << tl.version.get() << endl;
	int e = SBOLError(1, "Test");
	getchar();
	return 0;

}
