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

	Document& doc = Document();


	/* Start SBOL data model testing */

	/* Test constructor chain */
	SBOLObject &obj = SBOLObject();
	Identified &id = Identified();
	TopLevel &top = TopLevel();
	ComponentDefinition &cd = ComponentDefinition("http://examples.com", "cdef_obj");

	/* Test Property constructors.  An ordinary user generally doesn't use these */
	OwnedObject<SequenceAnnotation> sequenceAnnotation = OwnedObject<SequenceAnnotation>();
	List<OwnedObject<SequenceAnnotation>> sequenceAnnotations = List<OwnedObject<SequenceAnnotation>>(SBOL_SEQUENCE_ANNOTATIONS, NULL);

	///* Test getters */
	cout << cd.identity.get() << endl;
	cout << cd.persistentIdentity.get() << endl;
	cout << cd.displayId.get() << endl;
	cout << cd.version.get() << endl;

	/* Check libSBOL's implementation of internal types */
	cout << obj.getTypeURI() << endl;  // URI should match the one produced in the next line of code
	cout << obj.identity.getOwner().getTypeURI() << endl;
	cout << id.getTypeURI() << endl;
	cout << id.identity.getOwner().getTypeURI() << endl;
	cout << top.getTypeURI() << endl;
	cout << top.identity.getOwner().getTypeURI() << endl;
	cout << cd.getTypeURI() << endl;
	cout << cd.identity.getOwner().getTypeURI() << endl;

	/* Check that SBOL Properties are associated with the SBOL Object to which the property belongs.  This is crucial for constructing RDF triples */
	cout << "Check that the SBOL Properties are associated with their Owner Objects through a valid back-pointer." << endl;
	SBOLObject &owner = id.identity.getOwner();
	cout << owner.getTypeURI() << " is owner of " << id.identity.getTypeURI() << endl;

	/* Test registration of objects in the SBOL Document */
	/* There are two alternative methods for adding objects to the doc */
	cout << "Test registration of objects in the SBOL Document" << endl;

	/* All SBOL objects have an 'addToDocument' method */
	cout << "Testing 'addToDocument' method" << endl;
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;
	cout << "Adding " << cd.identity.get() << endl;
	cd.addToDocument(doc);
	cout << "Objects in doc: " << doc.SBOLObjects.size() << endl;

	/* Document objects have an 'add' template function allows user to add any SBOLObject to a document */
	cout << "Test template function implementation for 'add' that allows user to add any SBOLObject to a document" << endl;
	id.identity.set("http://examples.com/Identified/0");
	cout << "Adding " << id.identity.get() << endl;
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

	/* Test ListProperties */
	cout << "Testing list properties" << endl;
	cd.types.add("SO_0000002");
	cd.types.add("SO_0000003");
	cout << cd.types.get(0) << endl;
	cout << cd.types.get(1) << endl;

	/* Test 'add' method for OwnedObjects.  A SequenceAnnotation is an OwnedObject corresponding to white diamond in UML diagram */
	SequenceAnnotation& SA = SequenceAnnotation();
	SA.start.set(1);
	SA.end.set(100);
	cd.sequenceAnnotations.add(SA);

	/* Test reader implementation
	  In order to extend the data model, use: 	
	  extend_data_model<MyExtensionClass>(MY_EXTENSION_CLASS_URI); */
	
	cout << "Testing proxy constructors used by the reader " << endl;
	SBOLObject& some_obj = SBOL_DATA_MODEL_REGISTER[SBOL_COMPONENT_DEFINITION]();
	cout << some_obj.getTypeURI() << endl;

	/* Round trip */
	doc.read("SimpleComponentDefinitionExample.rdf");   // Existing contents of the current document are wiped when the file is imported
	doc.write("test.xml");

	/* Test exception handling and validation rules */
	cd.identity.set(cd.identity.get());  //  Should trigger SBOLError 0 in violation of validation_rule_10202 because the uri

	return 0;
}
