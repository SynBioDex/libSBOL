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
	doc.read("singleComponentDefinition.rdf");
	ComponentDefinition& cd = doc.get < ComponentDefinition >("http://www.async.ece.utah.edu/pLac/1.0");
	cd.identity.set(cd.identity.get());
	//TopLevel& tl = doc.getTopLevel("http://www.async.ece.utah/edu/pLac");
	doc.write("test.xml");
	///* Start SBOL data model testing */
	//cout << "Begin testing\n";
	//ComponentDefinition &sbol_obj = ComponentDefinition("http://examples.com", "cdef_obj");
	//cout << "Deleted sbol_obj" << endl;
	////ComponentDefinition sbol_obj = ComponentDefinition("http://examples.com", "cdef_obj");

	///* Test Property accessors */
	//cout << "Testing getters\n";
	//cout << sbol_obj.identity.get() << endl;
	////cout << sbol_obj.version.get() << endl;
	//cout << sbol_obj.getTypeURI() << endl << endl;

	///* Test constructor chain */
	//SBOLObject &obj = SBOLObject();
	//Identified &id = Identified();
	//Documented &docum = Documented();
	//TopLevel &top = TopLevel();
	//ComponentDefinition &cdef = ComponentDefinition();

	///* Check libSBOL's implementation of internal types */
	//cout << obj.getTypeURI() << endl;  // URI should match the one produced in the next line of code
	//cout << obj.identity.getOwner().getTypeURI() << endl;
	//cout << id.getTypeURI() << endl;
	//cout << id.identity.getOwner().getTypeURI() << endl;
	//cout << docum.getTypeURI() << endl;
	//cout << docum.identity.getOwner().getTypeURI() << endl;
	//cout << top.getTypeURI() << endl;
	//cout << top.identity.getOwner().getTypeURI() << endl;
	//cout << cdef.getTypeURI() << endl;
	//cout << cdef.identity.getOwner().getTypeURI() << endl;

	///* Check that SBOL Properties are associated with their Owner Objects.  This is crucial for constructing RDF triples */
	//cout << "Check that the SBOL Properties are associated with their Owner Objects through a valid back-pointer." << endl;
	//SBOLObject &owner = id.identity.getOwner();
	//cout << owner.getTypeURI() << " is owner of " << id.identity.getTypeURI() << endl;
	////cout << sbol_obj.timeStamp.getTypeURI() << sbol_obj.timeStamp.getTypeURI() << endl;
	////cout << sbol_obj.version.getTypeURI() << sbol_obj.version.getTypeURI() << endl;

	///* Test registration of objects in the SBOL Document */
	///* There are two alternative methods for adding objects to the doc */
	//cout << "Test registration of objects in the SBOL Document" << endl;
	//Document doc = Document();
	//cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	//sbol_obj.addToDocument(doc);
	//cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	//cout << "Registered object at address " << &sbol_obj << endl;

	///* Test template function implementation for 'add' that allows user to add any SBOLObject to a document */
	//cout << "Test template function implementation for 'add' that allows user to add any SBOLObject to a document" << endl;
	//id.identity.set("http://examples.com/Identified/0");
	//doc.add<Identified>(id);
	//cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;

	///* Test retrieval of objects from the doc */
	//ComponentDefinition *cd = (ComponentDefinition *)doc.SBOLObjects[sbol_obj.identity.get()];
	//cout << "Retrieved object at address " << cd << endl;
	//cd = &doc.get<ComponentDefinition>(sbol_obj.identity.get());
	//cout << "Retrieved object at address " << cd << endl;

	///* Test Maven version properties */
	//cout << "Testing version properties" << endl;
	//TopLevel& tl = doc.getTopLevel("http://examples.com/cdef_obj");
	//cout << tl.identity.get() << endl;
	//cout << tl.getTypeURI() << endl;
	////cout << tl.version.get() << endl;
	////tl.version.set("1.2.3-123");
	////cout << tl.version.get() << endl;

	///* Exception handling*/
	//int e = SBOLError(1, "Test");

	///* Test construction of triples */
	//tl.identity.write();
	//obj.identity.write();
	//id.identity.write();
	//docum.identity.write();

	///* Test template class for ListProperties */
	////cout << "Testing list properties" << endl;
	//////ListProperty<int> lp = ListProperty<int>(1, SBOL_TYPE, NULL);
	////cdef.types.add("SO_xxxxxxxx");
	////cdef.types.add("SO_xxxxxxxy");
	////cdef.types.write();

	///* Test ContainedObjects */
	//cout << "Test Container Objects" << endl;
	////cdef.sequenceAnnotations.add(obj);
	////SBOLObject& obj2 = SBOLObject();
	////cdef.sequenceAnnotations.add(obj2);
	//doc.add<ComponentDefinition>(cdef);
	////vector<SBOLObject> annotations = cdef.sequenceAnnotations.get();

	//SequenceAnnotation& SA = SequenceAnnotation();
	//SA.start.set("10");
	//cout << SA.start.get() << endl;
	//cdef.sequenceAnnotations.add(SA);

	///* Test iterative serialization of all properties in an SBOLObject */
	//cout << "Serializing document" << endl;
	////cdef.serialize();
	//doc.write("test.xml");

	//// Test reader implementation

	//// In order to extend. This associates an SBOL URI with the appropriate constructor call. 	
	////extend_data_model<ComponentDefinition>(SBOL_COMPONENT_DEFINITION);
	//cout << SBOL_DATA_MODEL_REGISTER.size() << endl;

	//cout << "Testing proxy constructor " << endl;
	//SBOLObject& aaa = SBOL_DATA_MODEL_REGISTER[SBOL_COMPONENT_DEFINITION]();
	//cout << aaa.getTypeURI() << endl;
	//doc.read("test.xml");
	//doc.write("test2.xml");
	///* Test memory management with pointers */
	//// ComponentDefinition* cd2 = new ComponentDefinition("http://examples.com", "dummy");
	//// delete cd2;
	return 0;
}
