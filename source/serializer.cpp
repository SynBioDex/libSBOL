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
	sbol::Identified sbol_obj = Identified();
	//sbol_obj.setIdentity("http://examples.com", "foo");
	//cout << "Identity:" << sbol_obj.getIdentity() << endl;;
	cout << sbol_obj.identity.get() << endl;
	cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.minorVersion.get() << endl;
	sbol::Documented sbol_obj_2 = Documented();
	cout << sbol_obj_2.displayID.get() << endl;
	//cerr << "Bye\n";
	return 0;



}
