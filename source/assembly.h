/// @file assembly.h
/// A suite of high-level methods for the synthetic biologist to perform DNA sequence assembly operations

#ifndef SBOL_ASSEMBLY_INCLUDED
#define SBOL_ASSEMBLY_INCLUDED

#include "document.h"
#include <vector>

namespace sbol
{

//    void assemble(ComponentDefinition& parent_component, std::vector<ComponentDefinition*> list_of_components);



    std::vector<Component*> getInSequentialOrder(ComponentDefinition& cd_root);

//void sbol::dissemble(ComponentDefinition& );
//void sbol::attachSubcomponent();
//void sbol::attachSubcomponents();
//void sbol::insertAnnotationAfter();
//void sbol::insertAnnotationBefore();
//void sbol::annotateSubcomponents();

}

#endif
