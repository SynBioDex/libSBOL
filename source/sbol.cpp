#include "sbol.h"

using namespace std;
using namespace sbol;

//unordered_map<string, SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER =
//{
//	// Typecast proxy constructors to a constructor for SBOL
//	// This makes some ugly syntax, but library users should never see it.
//	make_pair(UNDEFINED, &create<SBOLObject>),
//	make_pair(SBOL_COMPONENT_DEFINITION, (SBOLObject&(*)()) &create<ComponentDefinition>),
//	make_pair(SBOL_SEQUENCE_ANNOTATION, (SBOLObject&(*)()) &create<SequenceAnnotation>)
//
//};