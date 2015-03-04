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
	cout << sbol_obj.identity.get() << endl;
	cout << sbol_obj.timeStamp.get() << endl;
	cout << sbol_obj.version.get() << endl;
	sbol::Documented sbol_obj_2 = Documented();
	cout << sbol_obj_2.displayID.get() << endl;
	Identified clone = sbol_obj.clone();
	cout << sbol_obj.identity.get() << endl;
	//cerr << "Bye\n";
	return 0;



}
