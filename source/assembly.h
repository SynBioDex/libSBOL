/// @file assembly.h
/// A suite of high-level methods for the synthetic biologist to perform DNA sequence assembly operations

#ifndef SBOL_ASSEMBLY_INCLUDED
#define SBOL_ASSEMBLY_INCLUDED

#include "document.h"
#include <vector>

namespace sbol
{
    //ComponentDefinition& assemble(std::vector<ComponentDefinition*> list_of_components);
    void assemble(ComponentDefinition& parent_component, std::vector<ComponentDefinition*> list_of_components);

    void updateSequence(ComponentDefinition& parent_component);
    int hasUpstreamComponent(ComponentDefinition& cd_root, Component& current_component);
    Component& getUpstreamComponent(ComponentDefinition& cd_root, Component& current_component);
    int hasDownstreamComponent(ComponentDefinition& cd_root, Component& current_component);
    Component& getDownstreamComponent(ComponentDefinition& cd_root, Component& current_component);
    Component& getFirstComponent(ComponentDefinition& cd_root);
    Component& getLastComponent(ComponentDefinition& cd_root);

    std::vector<Component*> getInSequentialOrder(ComponentDefinition& cd_root);

//void sbol::dissemble(ComponentDefinition& );
//void sbol::attachSubcomponent();
//void sbol::attachSubcomponents();
//void sbol::insertAnnotationAfter();
//void sbol::insertAnnotationBefore();
//void sbol::annotateSubcomponents();

}

#endif
