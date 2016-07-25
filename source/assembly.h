/// @file assembly.h
/// A suite of high-level methods for the synthetic biologist to perform DNA sequence assembly operations

#ifndef SBOL_ASSEMBLY_INCLUDED
#define SBOL_ASSEMBLY_INCLUDED

#include "document.h"
#include <vector>

namespace sbol
{
    //ComponentDefinition& assemble(std::vector<ComponentDefinition*> list_of_components);
    void join(ComponentDefinition& parent_component, std::vector<ComponentDefinition*> list_of_components);
    void assemble(ComponentDefinition& parent_component, std::vector<ComponentDefinition*> list_of_subcomponents);

    
//void sbol::dissemble(ComponentDefinition& );
//void sbol::attachSubcomponent();
//void sbol::attachSubcomponents();
//void sbol::insertAnnotationAfter();
//void sbol::insertAnnotationBefore();
}

#endif
