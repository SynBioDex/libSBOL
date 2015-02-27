#include "sbol.h"

#include <iostream>
#include <libxml/parser.h>
#include <libxml/tree.h>
//#include <libxml2/libxml/parser.h>
using namespace std;
using namespace sbol;

int main() 
{
	xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
	sbol::Identified sbol_obj = Identified("http://examples.com", "foobar");
	sbol_obj.setIdentity("http://examples.com", "foo");
	cout << "Identity:" << sbol_obj.getIdentity() << endl;;
	cout << sbol_obj.getTimeStamp() << endl;
	cout << sbol_obj.sbolString.get() << endl;
	sbol_obj.sbolString.set("Good bye SBOL!");
	cout << sbol_obj.sbolString.get() << endl;
	//cerr << "Bye\n";
	
	return 0;



}
