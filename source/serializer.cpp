#include "sbol.h"

#include <iostream>
#include <vector>
//#include <typeinfo>
#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <libxml2/libxml/parser.h>
using namespace std;
using namespace sbol;

int main() 
{
	//xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
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
