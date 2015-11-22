#define RAPTOR_STATIC

#include "sbol.h"
#include "validation.h"

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

	// Test getter and setter.  Verify that validation rules are executed when setter is called.
	Document& doc = Document();

	// Round trip
	//doc.read("singleComponentDefinition.rdf");
	//ComponentDefinition& cd = doc.get < ComponentDefinition >("http://www.async.ece.utah.edu/pLac/1.0");
	//doc.write("test.xml");

	/* Start SBOL data model testing */

	/* Test constructor chain */
	SBOLObject &obj = SBOLObject();
	Identified &id = Identified();
	Documented &docum = Documented();
	TopLevel &top = TopLevel();
	ComponentDefinition &cd = ComponentDefinition("http://examples.com", "cdef_obj");

	/* Test the getters and print the ComponentDefinition's properties */
	cout << cd.identity.get() << endl;
	cout << cd.persistentIdentity.get() << endl;
	cout << cd.displayID.get() << endl;
	cout << cd.version.get() << endl;

	/* Check libSBOL's implementation of internal types */
	cout << obj.getTypeURI() << endl;  // URI should match the one produced in the next line of code
	cout << obj.identity.getOwner().getTypeURI() << endl;
	cout << id.getTypeURI() << endl;
	cout << id.identity.getOwner().getTypeURI() << endl;
	cout << docum.getTypeURI() << endl;
	cout << docum.identity.getOwner().getTypeURI() << endl;
	cout << top.getTypeURI() << endl;
	cout << top.identity.getOwner().getTypeURI() << endl;
	cout << cd.getTypeURI() << endl;
	cout << cd.identity.getOwner().getTypeURI() << endl;

	/* Check that SBOL Properties are associated with their Owner Objects.  This is crucial for constructing RDF triples */
	cout << "Check that the SBOL Properties are associated with their Owner Objects through a valid back-pointer." << endl;
	SBOLObject &owner = id.identity.getOwner();
	cout << owner.getTypeURI() << " is owner of " << id.identity.getTypeURI() << endl;

	/* Test registration of objects in the SBOL Document */
	/* There are two alternative methods for adding objects to the doc */
	cout << "Test registration of objects in the SBOL Document" << endl;
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	cd.addToDocument(doc);
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;

	/* Test template function implementation for 'add' that allows user to add any SBOLObject to a document */
	cout << "Test template function implementation for 'add' that allows user to add any SBOLObject to a document" << endl;
	id.identity.set("http://examples.com/Identified/0");
	doc.add<Identified>(id);
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;

	/* Test Maven version properties */
	cout << "Testing version properties" << endl;
	TopLevel& tl = doc.getTopLevel("http://examples.com/cdef_obj");
	cout << tl.identity.get() << endl;
	cout << tl.getTypeURI() << endl;
	//cout << tl.version.get() << endl;
	//tl.version.set("1.2.3-123");
	//cout << tl.version.get() << endl;

	/* Test construction of triples */
	tl.identity.write();
	obj.identity.write();
	id.identity.write();
	docum.identity.write();

	/* Test ListProperties */
	cout << "Testing list properties" << endl;
	cd.types.add("SO_0000002");
	cd.types.add("SO_0000003");

	/* Test ContainedObjects */
	cout << "Test Container Objects" << endl;
	SequenceAnnotation& SA = SequenceAnnotation();
	SA.start.set("10");
	cout << SA.start.get() << endl;
	cd.sequenceAnnotations.add(SA);

	/* Test iterative serialization of all properties in an SBOLObject */
	cout << "Serializing document" << endl;
	doc.write("test.xml");

	//// Test reader implementation
	//  In order to extend the data model, use: 	
	//  extend_data_model<ComponentDefinition>(SBOL_COMPONENT_DEFINITION);
	
	//cout << SBOL_DATA_MODEL_REGISTER.size() << endl;

	//cout << "Testing proxy constructors used by the reader " << endl;
	//SBOLObject& aaa = SBOL_DATA_MODEL_REGISTER[SBOL_COMPONENT_DEFINITION]();
	//cout << aaa.getTypeURI() << endl;

	// Test exception handling
	//cd.identity.set(cd.identity.get());  //  Should trigger SBOLError 0 in violation of validation_code_10202

	///* Test memory management with pointers */
	//// ComponentDefinition* cd2 = new ComponentDefinition("http://examples.com", "dummy");
	//// delete cd2;
	return 0;
}
