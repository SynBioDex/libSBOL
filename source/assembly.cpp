#include "assembly.h"

#include <stdio.h>

using namespace std;
using namespace sbol;


int ComponentDefinition::hasUpstreamComponent(Component& current_component)
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {
        int hasUpstreamComponent = 0;
        for (auto i_sc = cd_root.sequenceConstraints.begin(); i_sc != cd_root.sequenceConstraints.end(); i_sc++)
        {
            SequenceConstraint& sc = *i_sc;
            if (sc.object.get() == current_component.identity.get() && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
                hasUpstreamComponent = 1;
        }
        return hasUpstreamComponent;
    }
}

int ComponentDefinition::hasDownstreamComponent(Component& current_component)
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {
        int hasDownstreamComponent = 0;
        for (auto i_sc = cd_root.sequenceConstraints.begin(); i_sc != cd_root.sequenceConstraints.end(); i_sc++)
        {
            SequenceConstraint& sc = *i_sc;
            if (sc.subject.get() == current_component.identity.get() && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
                hasDownstreamComponent = 1;
        }
        return hasDownstreamComponent;
    }
}

Component& ComponentDefinition::getUpstreamComponent(Component& current_component)
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else if (!cd_root.hasUpstreamComponent(current_component))
        throw;
    else
    {
        string upstream_component_id;
        for (auto i_sc = cd_root.sequenceConstraints.begin(); i_sc != cd_root.sequenceConstraints.end(); i_sc++)
        {
            SequenceConstraint& sc = *i_sc;
            if (sc.object.get() == current_component.identity.get() && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
                 upstream_component_id = sc.subject.get();
        }
        Component& upstream_component = components[upstream_component_id];
        return upstream_component;
    }
}

Component& ComponentDefinition::getDownstreamComponent(Component& current_component)
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else if (!cd_root.hasDownstreamComponent(current_component))
        throw;
    else
    {
        string downstream_component_id;
        for (auto i_sc = cd_root.sequenceConstraints.begin(); i_sc != cd_root.sequenceConstraints.end(); i_sc++)
        {
            SequenceConstraint& sc = *i_sc;
            if (sc.subject.get() == current_component.identity.get() && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
                downstream_component_id = sc.object.get();
        }
        Component& downstream_component = components[downstream_component_id];
        return downstream_component;
    }
}

Component& ComponentDefinition::getFirstComponent()
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.components.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {
        Component& arbitrary_component = cd_root.components[0];
        Component* iterator_component = &arbitrary_component;
        while (cd_root.hasUpstreamComponent(*iterator_component))
        {
            iterator_component = &cd_root.getUpstreamComponent(*iterator_component);
        }
        return *iterator_component;
    }
}

Component& ComponentDefinition::getLastComponent()
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.components.size() < 1)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {

        Component& arbitrary_component = cd_root.components[0];
//        Component* iterator_component = &arbitrary_component;
        Component* iterator_component = &cd_root.components[0];
        while (cd_root.hasDownstreamComponent(*iterator_component))
        {
            iterator_component = &cd_root.getDownstreamComponent(*iterator_component);
        }

        return *iterator_component;
    }
}


vector<Component*> ComponentDefinition::getInSequentialOrder()
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 0)
        throw;
    else
    {
        Component* first = &getFirstComponent();
        vector<Component*> sequential_components = { first };

        Component* next = first;
        while (hasDownstreamComponent(*next))
        {
            next = &getDownstreamComponent(*next);
            sequential_components.push_back(next);
        }
        return sequential_components;
    }
}


std::string ComponentDefinition::updateSequence(std::string composite_sequence)
{
    ComponentDefinition& parent_component = *this;
    std::string parent_component_id = parent_component.identity.get();
    if (parent_component.components.size() > 0)
    {

        vector<Component*> subcomponents = getInSequentialOrder();
        for (auto i_c = subcomponents.begin(); i_c != subcomponents.end(); i_c++)
        {
            Component& c = **i_c;
            ComponentDefinition& cdef = doc->get < ComponentDefinition > (c.definition.get());
            Sequence& seq = doc->get < Sequence > (cdef.sequence.get());
            composite_sequence = composite_sequence + cdef.updateSequence(composite_sequence);
        }
        return composite_sequence;
    }
    else
    {
        std::string parent_component_seq = parent_component.sequence.get();
        Sequence& seq = doc->get < Sequence >(parent_component.sequence.get());
        return seq.elements.get();
    }
}

/// @TODO update SequenceAnnotation starts and ends
void ComponentDefinition::assemble(vector<ComponentDefinition*> list_of_components)
{
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Assemble methods require SBOL-compliance enabled");
    if (list_of_components.size() < 2)
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Assemble method expects at least two ComponentDefinitions");
    }
    else
    {
        ComponentDefinition& parent_component = *this;

        vector<Component*> list_of_instances = {};
        for (auto i_com = 0; i_com != list_of_components.size(); i_com++)
        {
            ComponentDefinition& cdef = *list_of_components[i_com];
            Component& c = parent_component.components.create(cdef.displayId.get());
            c.definition.set(cdef.identity.get());
            list_of_instances.push_back(&c);
        }
        for (auto i_com = 1; i_com != list_of_components.size(); i_com++)
        {
            ComponentDefinition& cd_upstream = *list_of_components[i_com - 1];
            ComponentDefinition& cd_downstream = *list_of_components[i_com];
            
            Component& constraint_subject = *list_of_instances[i_com - 1];
            Component& constraint_object = *list_of_instances[i_com];
        
            SequenceConstraint& sc = parent_component.sequenceConstraints.create("constraint" + to_string(i_com));
            sc.subject.set(constraint_subject.identity.get());
            sc.object.set(constraint_object.identity.get());
            sc.restriction.set(SBOL_RESTRICTION_PRECEDES);
        }
    }
}
    
std::string Sequence::assemble(std::string composite_sequence)
{
    // Throw an error if this Sequence is not attached to a Document
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Sequence cannot be assembled because it does not belong to a Document. Add the Sequence to a Document.");
    }
    // Search for ComponentDefinition that this Sequence describes
    ComponentDefinition* parent_cdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_COMPONENT_DEFINITION)
        {
            ComponentDefinition* cdef = (ComponentDefinition*)obj;
            if (cdef->sequence.get() == identity.get())
            {
                parent_cdef = cdef;
            }
        }
    }
    // Throw an error if no ComponentDefinitions in the Document refer to this Sequence
    if (parent_cdef == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Sequence cannot be assembled. There are no ComponentDefinitions in the Document which refer to this Sequence. ");
    }

    ComponentDefinition& parent_component = *parent_cdef;
    if (parent_component.components.size() > 0)
    {
            
        vector<Component*> subcomponents = parent_component.getInSequentialOrder();
        for (auto i_c = subcomponents.begin(); i_c != subcomponents.end(); i_c++)
        {
            Component& c = **i_c;
            ComponentDefinition& cdef = doc->get < ComponentDefinition > (c.definition.get());
            Sequence& seq = doc->get < Sequence > (cdef.sequence.get());
            composite_sequence = composite_sequence + seq.assemble(composite_sequence);
        }
        elements.set(composite_sequence);
        return composite_sequence;
    }
    else
    {
        std::string parent_component_seq = parent_component.sequence.get();
        Sequence& seq = doc->get < Sequence >(parent_component.sequence.get());
        return seq.elements.get();
    }
};

void ModuleDefinition::assemble(std::vector < ModuleDefinition* > list_of_modules)
{
    if (list_of_modules.size() < 1)
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Assemble method expects at least one ModuleDefinition");
    }
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "This method only works when SBOL-compliance is enabled");
    else
    {
        ModuleDefinition& parent_module = *this;
        vector<Module*> list_of_instances = {};
        for (auto i_m = 0; i_m != list_of_modules.size(); i_m++)
        {
            ModuleDefinition& mdef = *list_of_modules[i_m];
            Module& m = parent_module.modules.create(mdef.displayId.get());
            m.definition.set(mdef.identity.get());
            list_of_instances.push_back(&m);
        }
    }
};

FunctionalComponent& ModuleDefinition::setOutput(ComponentDefinition& output)
{
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    string output_fc_id = persistentIdentity.get() + "/" + output.displayId.get() + "/" + version.get();
    if (find(output_fc_id))
    {
        FunctionalComponent& output_fc = functionalComponents[output_fc_id];
        output_fc.direction.set(SBOL_DIRECTION_OUT);
        return output_fc;
    }
    else
    {
        FunctionalComponent& output_fc = functionalComponents.create(output.displayId.get());
        output_fc.definition.set(output.identity.get());
        output_fc.direction.set(SBOL_DIRECTION_OUT);
        return output_fc;
    }
};

FunctionalComponent& ModuleDefinition::setInput(ComponentDefinition& input)
{
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    string input_fc_id = persistentIdentity.get() + "/" + input.displayId.get() + "/" + version.get();
    if (find(input_fc_id))
    {
        FunctionalComponent& input_fc = functionalComponents[input_fc_id];
        input_fc.direction.set(SBOL_DIRECTION_IN);
        return input_fc;
    }
    else
    {
        FunctionalComponent& input_fc = functionalComponents.create(input.displayId.get());
        input_fc.definition.set(input.identity.get());
        input_fc.direction.set(SBOL_DIRECTION_IN);
        return input_fc;
    }
};

//FunctionalComponent& ModuleDefinition::setOutput(ComponentDefinition& output)
//{
//    if (doc == NULL)
//    {
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
//    }
//    
//    // Search for parent ModuleDefinition that contains this ModuleDefinition as a submodule.  Throw an error if the parent ModuleDefinition can't be found
//    ModuleDefinition* parent_mdef = NULL;
//    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject* obj = i_obj->second;
//        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
//        {
//            ModuleDefinition* mdef = (ModuleDefinition*)obj;
//            for (auto i_m = mdef->modules.begin(); i_m != mdef->modules.end(); ++i_m)
//            {
//                Module& m = *i_m;
//                if (m.definition.get() == identity.get())
//                    parent_mdef = mdef;
//            }
//        }
//    }
//    if (parent_mdef == NULL)
//        throw SBOLError(NOT_FOUND_ERROR, "Missing parent ModuleDefinition");
//
//    FunctionalComponent& fc = functionalComponents.create(output.displayId.get());
//    fc.definition.set(output.identity.get());
//    fc.direction.set(SBOL_DIRECTION_OUT);
//    return fc;
//};
//
//FunctionalComponent& ModuleDefinition::setInput(ComponentDefinition& input)
//{
//    if (doc == NULL)
//    {
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
//    }
//    
//    // Search for parent ModuleDefinition that contains this ModuleDefinition as a submodule.  Throw an error if the parent ModuleDefinition can't be found
//    ModuleDefinition* parent_mdef = NULL;
//    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject* obj = i_obj->second;
//        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
//        {
//            ModuleDefinition* mdef = (ModuleDefinition*)obj;
//            cout << "Searching " << mdef->identity.get() << endl;
//            for (auto i_m = mdef->modules.begin(); i_m != mdef->modules.end(); ++i_m)
//            {
//                Module& m = *i_m;
//                cout << identity.get() << "\t" << m.definition.get() << endl;
//                if (m.definition.get() == identity.get())
//                    parent_mdef = mdef;
//            }
//        }
//    }
//    if (parent_mdef == NULL)
//        throw SBOLError(NOT_FOUND_ERROR, "Missing parent ModuleDefinition");
//
//    FunctionalComponent& fc = functionalComponents.create(input.displayId.get());
//    fc.definition.set(input.identity.get());
//    fc.direction.set(SBOL_DIRECTION_IN);
//    return fc;
//};

//void FunctionalComponent::connect(FunctionalComponent& interface_component)
//{
//    if (!isSBOLCompliant())
//        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
//    
//    // Throw an error if this Sequence is not attached to a Document
//    if (doc == NULL)
//    {
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
//    }
//    
//     // Search for parent ModuleDefinition that contains these FunctionalComponents
//    ModuleDefinition* parent_mdef = NULL;
//    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject* obj = i_obj->second;
//        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
//        {
//            ModuleDefinition* mdef = (ModuleDefinition*)obj;
//            for (auto i_fc1 = mdef->modules.begin(); i_fc1 != mdef->modules.end(); ++i_fc1)
//            {
//                FunctionalComponent& subject_fc = *i_fc1;
//                if (subject_fc.identity.get() == identity.get())
//                {
//                    for (auto i_fc2 = mdef->modules.begin(); i_fc2 != mdef->modules.end(); ++i_fc2)
//                    {
//                        FunctionalComponent& object_fc = *i_fc2;
//                        if (object_fc.definition.get() == interface_component.identity.get())
//                        {
//                            parent_mdef = mdef;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    if (parent_mdef == NULL)
//        throw SBOLError(NOT_FOUND_ERROR, "Cannot find Modules that these FunctionalComponents belong to");
//    
//    // Connect the modules
//    MapsTo& connection = subject_module->mapsTos.create(displayId.get() + "test");
//    connection.local.set(identity.get());
//    connection.remote.set(interface_component.identity.get());
//    connection.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
//};

void FunctionalComponent::connect(FunctionalComponent& interface_component)
{
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
   
    // Throw an error if this Sequence is not attached to a Document
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    
    // Search for ModuleDefinition that this FunctionalComponent belongs to. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* subject_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
            {
                FunctionalComponent& fc = *i_fc;
                if (fc.identity.get() == identity.get())
                    subject_mdef = mdef;
            }
        }
    }
    if (subject_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "FunctionalComponent must belong to a ModuleDefinition");

    // The interface component must also belong to a ModuleDefinition. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* object_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
            {
                FunctionalComponent& fc = *i_fc;
                if (fc.identity.get() == interface_component.identity.get())
                    object_mdef = mdef;
            }
        }
    }
    if (object_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "FunctionalComponent must belong to a ModuleDefinition");
    
    // Search for parent ModuleDefinition that contains the subject and object submodules
    // The interface component MUST also belong to a ModuleDefinition. Throw an error if the parent ModuleDefinition can't be found
    ModuleDefinition* parent_mdef = NULL;
    Module* subject_module = NULL;
    Module* object_module = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_m = mdef->modules.begin(); i_m != mdef->modules.end(); ++i_m)
            {
                Module& m = *i_m;
                if (m.definition.get() == subject_mdef->identity.get())
                {
                    for (auto i_n = mdef->modules.begin(); i_n != mdef->modules.end(); ++i_n)
                    {
                        Module& n = *i_n;
                        if (n.definition.get() == object_mdef->identity.get())
                        {
                            parent_mdef = mdef;
                            subject_module = &m;
                            object_module = &n;
                        }
                    }
                }
            }
        }
    }
    if (parent_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "Cannot find Modules that these FunctionalComponents belong to");
    
    // Instantiate FunctionalComponent in parent ModuleDefinition
    FunctionalComponent& bridge_fc = parent_mdef->functionalComponents.create(displayId.get());
    bridge_fc.definition.set(definition.get());
    
    
    // Link the modules through the bridge FunctionalComponent contained in the parent ModuleDefinition
    // This FunctionalComponent is assumed to override the object component
    MapsTo& half_connection1 = subject_module->mapsTos.create(displayId.get());
    half_connection1.local.set(bridge_fc.identity.get());
    half_connection1.remote.set(identity.get());
    if (definition.get() == bridge_fc.definition.get())
        half_connection1.refinement.set(SBOL_REFINEMENT_VERIFY_IDENTICAL);
    else
        half_connection1.refinement.set(SBOL_REFINEMENT_USE_REMOTE);
    MapsTo& half_connection2 = object_module->mapsTos.create(displayId.get());
    half_connection2.local.set(bridge_fc.identity.get());
    half_connection2.remote.set(interface_component.identity.get());
    if (interface_component.definition.get() == bridge_fc.definition.get())
        half_connection2.refinement.set(SBOL_REFINEMENT_VERIFY_IDENTICAL);
    else
        half_connection2.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
    
};

void Participation::define(ComponentDefinition& species, string role)
{
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    // Search for parent ModuleDefinition and parent Interaction
    // The interface component MUST also belong to a ModuleDefinition. Throw an error if the parent ModuleDefinition can't be found
    ModuleDefinition* parent_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_x = mdef->interactions.begin(); i_x != mdef->interactions.end(); ++i_x)
            {
                Interaction& x = *i_x;
                for (auto i_p = x.participations.begin(); i_p != x.participations.end(); ++i_p)
                {
                    Participation& p = *i_p;
                    if (p.identity.get() == identity.get())
                        parent_mdef = mdef;
                }
            }
        }
    }
    if (parent_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "Cannot find parent ModuleDefinition for this Participation");
    

    string species_fc_id = parent_mdef->persistentIdentity.get() + "/" + species.displayId.get() + "/" + species.version.get();
    if (parent_mdef->find(species_fc_id))
    {
        FunctionalComponent& species_fc = parent_mdef->functionalComponents[species_fc_id];
    }
    else
    {
        FunctionalComponent& species_fc = parent_mdef->functionalComponents.create(species.displayId.get());
        species_fc.definition.set(species.identity.get());
        species_fc.direction.set(SBOL_DIRECTION_NONE);
    }
    participant.set(species_fc_id);
    if (role != "")
        roles.add(role);
};

void ComponentDefinition::participate(Participation& species)
{
    species.define(*this);
};

void FunctionalComponent::mask(FunctionalComponent& masked_component)
{
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    
    // Search for ModuleDefinition that this FunctionalComponent belongs to. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* subject_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
            {
                FunctionalComponent& fc = *i_fc;
                if (fc.identity.get() == identity.get())
                {
                    subject_mdef = mdef;
                }

            }
        }
    }
    if (subject_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "FunctionalComponent must belong to a ModuleDefinition");
    // The masked component must also belong to a ModuleDefinition. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* object_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
            {
                FunctionalComponent& fc = *i_fc;
                if (fc.identity.get() == masked_component.identity.get())
                {
                    object_mdef = mdef;
                }
            }
        }
    }
    if (object_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "FunctionalComponent must belong to a ModuleDefinition");

    // Determine the relationship of the parent modules.  Are they hierarchically nested? Are they different parts of the tree?
    int IS_LOCAL = -1;
    Module* parent_m = NULL;
    for (auto i_m = subject_mdef->modules.begin(); i_m != subject_mdef->modules.end(); ++i_m)
    {
        Module& m = *i_m;
        if (m.definition.get() == object_mdef->identity.get())
        {
            IS_LOCAL = 1;
            parent_m = &m;
        }
    }
    for (auto i_m = object_mdef->modules.begin(); i_m != object_mdef->modules.end(); ++i_m)
    {
        Module& m = *i_m;
        if (m.definition.get() == subject_mdef->identity.get())
        {
            IS_LOCAL = 0;
            parent_m = &m;
        }
    }
    if (parent_m == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "These FunctionalComponents are located in unrelated Modules. Perform assembly.");
    
    // Search for a MapsTo connecting these components. If it doesn't exist, create one.
    MapsTo* override_map = NULL;
    for (auto i_map = parent_m->mapsTos.begin(); i_map != parent_m->mapsTos.end(); ++i_map)
    {
        MapsTo& maps_to = *i_map;
        if (IS_LOCAL == 1 && maps_to.local.get() == identity.get())  // If this component is local, set override flag to LOCAL
        {
            maps_to.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
        }
        if (IS_LOCAL == -1 && maps_to.remote.get() == identity.get())  // If this component is remote, set override flag to REMOTE
        {
            maps_to.refinement.set(SBOL_REFINEMENT_USE_REMOTE);
        }
    }
    if (override_map == NULL)
    {
        override_map = &parent_m->mapsTos.create(identity.get());
        if (IS_LOCAL == 1)
        {

            override_map->local.set(identity.get());
            override_map->remote.set(masked_component.identity.get());
            override_map->refinement.set(SBOL_REFINEMENT_USE_LOCAL);
        }
        if (IS_LOCAL == 0)
        {

            override_map->local.set(masked_component.identity.get());
            override_map->remote.set(identity.get());
            override_map->refinement.set(SBOL_REFINEMENT_USE_REMOTE);
        }
    }
};

int FunctionalComponent::isMasked()
{
    if (!isSBOLCompliant())
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
    }
    // Search for parent ModuleDefinition and parent Interaction
    // The interface component MUST also belong to a ModuleDefinition. Throw an error if the parent ModuleDefinition can't be found
    ModuleDefinition* parent_mdef = NULL;
    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
    {
        SBOLObject* obj = i_obj->second;
        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
        {
            ModuleDefinition* mdef = (ModuleDefinition*)obj;
            for (auto i_m = mdef->modules.begin(); i_m != mdef->modules.end(); ++i_m)
            {
                Module& m = *i_m;
                for (auto i_map = m.mapsTos.begin(); i_map != m.mapsTos.end(); ++i_map)
                {
                    MapsTo& maps_to = *i_map;

                    if (maps_to.local.get() == identity.get() && maps_to.refinement.get() == SBOL_REFINEMENT_USE_REMOTE)
                        return 1;
                    if (maps_to.remote.get() == identity.get() && maps_to.refinement.get() == SBOL_REFINEMENT_USE_LOCAL)
                        return 1;
                }
            }
        }
    }
    
    return 0;
};
