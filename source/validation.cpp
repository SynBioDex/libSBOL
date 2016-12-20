#include "sbol.h"
#include <iostream>

using namespace sbol;
using namespace std;

/* An SBOL document MUST declare the use of the following XML namespace: http://sbols.org/v2#. */
void sbol::sbolRule10101(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(SBOL_URI "#") == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " SBOL_URI "#");
}

/* An SBOL document MUST declare the use of the following XML namespace: http://www.w3.org/1999/02/22-rdf-syntax-ns#.*/
void sbol::sbolRule10102(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(RDF_URI) == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " RDF_URI);
}

/* The identity property of an Identified object MUST be globally unique. */
void sbol::sbol_rule_10202(void *sbol_obj, void *arg)
{
	Identified *identified_obj = (Identified *)sbol_obj;
	string new_id;

	if (arg != NULL)
	{
		new_id = *static_cast<std::string*>(arg);
	}
	if (identified_obj->doc)
	{
		if (identified_obj->doc->SBOLObjects.find(new_id) != identified_obj->doc->SBOLObjects.end())  // If the new identity is already in the document throw an error
		{
			throw SBOLError(DUPLICATE_URI_ERROR, "Duplicate URI");
		}
	}
};

/*	The definition property MUST NOT refer to the same ComponentDefinition as the one that contains the
ComponentInstance.Furthermore, ComponentInstance objects MUST NOT form a cyclical chain of references
via their definition properties and the ComponentDefinition objects that contain them.For example, consider
the ComponentInstance objects A and B and the ComponentDefinition objects X and Y.The reference chain "X
contains A, A is defined by Y, Y contains B, and B is defined by X" is cyclical. */
void sbol::libsbol_rule_1(void *sbol_obj, void *arg)
{
	cout << "Testing internal validation rules" << endl;
};