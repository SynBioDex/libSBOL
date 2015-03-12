#include "sbol.h"

#include <iostream>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <libxml2/libxml/parser.h>
using namespace std;
using namespace sbol;

int main() 
{
	xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
	sbol::TopLevel sbol_obj = TopLevel("http://examples.com", "documented_obj");
	cout << sbol_obj.identity.get() << endl;
	cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.version.get() << endl;

	SBOLDocument doc = SBOLDocument();
	cout << doc.SBOLObjects.size() << endl;
	sbol_obj.addToDocument(doc);
	cout << doc.SBOLObjects.size() << endl;
	TopLevel& tl = doc.getTopLevel("http://examples.com/documented_obj/1.0.0");
	//cout << tl.identity.get() << endl;
	//TopLevel& tl = doc.getTopLevel("http://examples.com/documented_obj/1.0.0");
	//cout << tl.identity.get() << endl;
	vector<string> v = sbol_obj.version.split('.');
	//cout << v[0] << endl;
	return 0;



}
