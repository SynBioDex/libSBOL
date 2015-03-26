#include "sbol.h"

#include <iostream>
#include <vector>
#include <typeinfo>
#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <libxml2/libxml/parser.h>
using namespace std;
using namespace sbol;

int main() 
{
	xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
	sbol::GenericTopLevel sbol_obj = GenericTopLevel("http://examples.com", "documented_obj");
	cout << sbol_obj.identity.get() << endl;
	cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.version.get() << endl;

	SBOLDocument doc = SBOLDocument();
	cout << doc.SBOLObjects.size() << endl;
	sbol_obj.addToDocument(doc);
	cout << doc.SBOLObjects.size() << endl;
	TopLevel& tl = doc.getTopLevel("http://examples.com/documented_obj/1.0.0");

	vector<string> v = sbol_obj.version.split('.');
	return 0;



}
