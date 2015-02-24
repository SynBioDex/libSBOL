#include <iostream>
#include "sbol.h"
//#include <libxml2/libxml/tree.h>
//#include <libxml2/libxml/parser.h>
using namespace std;
using namespace sbol;

int main() 
{
	//xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
	Identified sbol_obj;
	sbol_obj.set_identity("http://examples.com", "foo");
	cout << "Identity:" << sbol_obj.get_identity() << endl;;
	cerr << "Bye\n";
	return 0;

}
