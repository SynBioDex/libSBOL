#ifndef SBOL_INCLUDED
#define SBOL_INCLUDED

#include "document.h"

//// This is the global SBOL register for classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a constructor
//extern std::unordered_map<std::string, sbol::SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER;
//
//template <class SBOLClass>
//void extend_data_model(std::string uri)
//{
//	SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, ( SBOLObject&(*)() )&create<SBOLClass>));
//};

#endif