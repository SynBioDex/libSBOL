/**
 * @file    assembly.cpp
 * @brief   Convenience methods for manipulating primary sequence structure
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/

#include "assembly.h"

#include <stdio.h>

using namespace std;
using namespace sbol;


int ComponentDefinition::hasUpstreamComponent(Component& current_component)
{
    ComponentDefinition& cd_root = *this;
    if (cd_root.sequenceConstraints.size() < 1)
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This component has no sequenceConstrints");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
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
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This component has no sequenceConstraints");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
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
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This component has sequenceConstraints");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
    else if (!cd_root.hasUpstreamComponent(current_component))
        throw SBOLError(SBOL_ERROR_END_OF_LIST, "This component has no upstream component. Use hasUpstreamComponent to catch this error");
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
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This component has no sequenceConstraints");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
    else if (!cd_root.hasDownstreamComponent(current_component))
        throw SBOLError(SBOL_ERROR_END_OF_LIST, "This component has no downstream component. Use hasDownstreamComponent to catch this error");
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
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This ComponentDefinition has no components");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
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
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This ComponentDefinition has no components");
    else if (cd_root.doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "The ComponentDefinition must belong to a Document in order to use this method");
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
    if (cd_root.sequenceConstraints.size() < 1)
        throw SBOLError(SBOL_ERROR_NOT_FOUND, "This component has no sequenceConstraints");
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
            Sequence& seq = doc->get < Sequence > (cdef.sequences.get());
            composite_sequence = composite_sequence + cdef.updateSequence(composite_sequence);
        }
        return composite_sequence;
    }
    else
    {
        std::string parent_component_seq = parent_component.sequences.get();
        Sequence& seq = doc->get < Sequence >(parent_component.sequences.get());
        return seq.elements.get();
    }
}

/// @TODO update SequenceAnnotation starts and ends
void ComponentDefinition::assemble(vector<ComponentDefinition*> list_of_components)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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
            // Instantiate the Component defined by the ComponentDefinition
            ComponentDefinition& cdef = *list_of_components[i_com];
            int instance_count = 0;
            
            // Generate URI of new Component.  Check if an object with that URI is already instantiated.
            string component_id;
            component_id = persistentIdentity.get() + "/" + cdef.displayId.get() + "/" + to_string(instance_count) + "/" + parent_component.version.get();

            while (parent_component.find(component_id) != NULL)
            {
                // Find the last instance assigned
                ++instance_count;
                component_id = persistentIdentity.get() + "/" + cdef.displayId.get() + "/" + to_string(instance_count) + "/" + parent_component.version.get();
            }

            Component& c = parent_component.components.create(cdef.displayId.get() + "/" + to_string(instance_count));
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
            if (cdef->sequences.get() == identity.get())
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
            Sequence& seq = doc->get < Sequence > (cdef.sequences.get());
            composite_sequence = composite_sequence + seq.assemble(composite_sequence);
        }
        elements.set(composite_sequence);
        return composite_sequence;
    }
    else
    {
        std::string parent_component_seq = parent_component.sequences.get();
        Sequence& seq = doc->get < Sequence >(parent_component.sequences.get());
        return seq.elements.get();
    }
};

void ModuleDefinition::assemble(std::vector < ModuleDefinition* > list_of_modules)
{
    if (list_of_modules.size() < 1)
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Assemble method expects at least one ModuleDefinition");
    }
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
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

vector<ComponentDefinition*> ComponentDefinition::applyToComponentHierarchy(void (*callback_fn)(ComponentDefinition *, void *), void* user_data)
{
    /* Assumes parent_component is an SBOL data structure of the general form ComponentDefinition(->Component->ComponentDefinition)n where n+1 is an integer describing how many hierarchical levels are in the SBOL structure */
    /* Look at each of the ComponentDef's SequenceAnnotations, is the target base there? */
    if (!doc)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot traverse Component hierarchy without a Document");

    bool GET_ALL = true;
    vector<ComponentDefinition*> component_nodes;
    if (components.size() == 0)
    {
//        cout << "Adding subcomponent : " << identity.get() << endl;
        component_nodes.push_back(this);  // Add leaf components
        if (callback_fn)
            callback_fn(this, user_data);
    }
    else
    {
        if (GET_ALL)
        {
//            cout << "Adding subcomponent : " << identity.get() << endl;
            component_nodes.push_back(this);  // Add components with children
            if (callback_fn)
                callback_fn(this, user_data);
        }
        for (auto& subc : components)
        {
            if (!doc->find(subc.definition.get()))
            {
//                std::cout << "Not found" << std::endl;
                throw SBOLError(SBOL_ERROR_NOT_FOUND, subc.definition.get() + "not found");
            }
            ComponentDefinition& subcdef = doc->get<ComponentDefinition>(subc.definition.get());
//            std::cout << subcdef.identity.get() << std::endl;
//            cout << "Descending one level : " << subcdef.identity.get() << endl;
            vector < sbol::ComponentDefinition* > subcomponents = subcdef.applyToComponentHierarchy(callback_fn, user_data);
//            cout << "Found " << subcomponents.size() << " components" << std::endl;
            component_nodes.reserve(component_nodes.size() + distance(subcomponents.begin(), subcomponents.end()));
            component_nodes.insert(component_nodes.end(), subcomponents.begin(),subcomponents.end());
        }
    }
    return component_nodes;
};

bool SequenceAnnotation::precedes(SequenceAnnotation& comparand)
{
    if (locations.size() > 0 && comparand.locations.size() > 0)
    {
        Range& this_range = (Range&)locations[0];
        Range& that_range = (Range&)comparand.locations[0];
        return this_range.precedes(that_range);
    }
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceAnnotation has no Range specified");
}

bool SequenceAnnotation::follows(SequenceAnnotation& comparand)
{
    if (locations.size() > 0 && comparand.locations.size() > 0)
    {
        Range& this_range = (Range&)locations[0];
        Range& that_range = (Range&)comparand.locations[0];
        return this_range.follows(that_range);
    }
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceAnnotation has no Range specified");
}

bool SequenceAnnotation::contains(SequenceAnnotation& comparand)
{
    if (locations.size() > 0 && comparand.locations.size() > 0)
    {
        Range& this_range = (Range&)locations[0];
        Range& that_range = (Range&)comparand.locations[0];
        return this_range.contains(that_range);
    }
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceAnnotation has no Range specified");
}

bool SequenceAnnotation::overlaps(SequenceAnnotation& comparand)
{
    if (locations.size() > 0 && comparand.locations.size() > 0)
    {
        Range& this_range = (Range&)locations[0];
        Range& that_range = (Range&)comparand.locations[0];
        return this_range.overlaps(that_range);
    }
    else
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceAnnotation has no Range specified");
}


int Range::precedes(Range& comparand)
{
    if (end.get() < comparand.start.get())
        return comparand.start.get() + 1 - end.get();
    else
        return 0;
}

int Range::follows(Range& comparand)
{
    if (start.get() > comparand.end.get())
        return comparand.end.get() + 1 - start.get();
    else
        return 0;
}

int Range::contains(Range& comparand)
{
    if (start.get() <= comparand.start.get() && end.get() >= comparand.end.get())
        return comparand.length();
    else
        return 0;
}

int Range::overlaps(Range& comparand)
{
    if (start.get() == comparand.start.get() && end.get() == comparand.end.get())
        return 0;
    else if (start.get() <= comparand.start.get() && end.get() <= comparand.end.get() && end.get() > comparand.start.get() )
        return comparand.start.get() + 1 - end.get();
    else if (start.get() >= comparand.start.get() && end.get() >= comparand.end.get() && start.get() < comparand.end.get())
        return comparand.end.get() + 1 - start.get();
    else
        return 0;
}

int Range::length()
{
    return end.get() + 1 - start.get();
}



vector<SequenceAnnotation*> SequenceAnnotation::precedes(std::vector<SequenceAnnotation*> comparand_list)
{
    vector<SequenceAnnotation*> filtered_list = {};
    return filtered_list;
};

std::vector<SequenceAnnotation*> SequenceAnnotation::follows(std::vector<SequenceAnnotation*> comparand_list)
{
    vector<SequenceAnnotation*> filtered_list = {};
    return filtered_list;
};

std::vector<SequenceAnnotation*> SequenceAnnotation::contains(std::vector<SequenceAnnotation*> comparand_list)
{
    vector<SequenceAnnotation*> list_of_contained_annotations;
    
    sbol::Range& r_this = (sbol::Range&)locations[0];
    cout << r_this.start.get() << "\t" << r_this.end.get() << "\t";
    for (auto &ann_comparand : comparand_list)
    {
        if (this->contains(*ann_comparand))
        {
            list_of_contained_annotations.push_back(ann_comparand);
            sbol::Range& r_comparand = (sbol::Range&)ann_comparand->locations[0];
            cout << r_comparand.start.get() << "\t" << r_comparand.end.get() << "\n\t\t";
        }
    }
    cout << endl;
    return list_of_contained_annotations;
};

std::vector<SequenceAnnotation*> SequenceAnnotation::overlaps(std::vector<SequenceAnnotation*> comparand_list)
{
    vector<SequenceAnnotation*> list_of_overlapping_annotations;
    
    sbol::Range& r_this = (sbol::Range&)locations[0];
    cout << r_this.start.get() << "\t" << r_this.end.get() << "\t";
    for (auto &ann_comparand : comparand_list)
    {
        if (this->overlaps(*ann_comparand))
        {
            list_of_overlapping_annotations.push_back(ann_comparand);
            sbol::Range& r_comparand = (sbol::Range&)ann_comparand->locations[0];
            cout << r_comparand.start.get() << "\t" << r_comparand.end.get() << "\n\t\t";
        }
    }
    cout << endl;
    return list_of_overlapping_annotations;
};

int SequenceAnnotation::length()
{
    if (locations.size() == 0)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. SequenceAnnotation " + identity.get() + " is invalid for this operation because it has no Range specified");
    if (locations.size() > 1)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot calculate identity. SequenceAnnotation " + identity.get() + " is invalid for this operation because it has more than one Range specified");
    Range& r_target = (Range&)locations[0];
    return r_target.length();
};

void ComponentDefinition::insertDownstream(Component& upstream, ComponentDefinition& insert)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + identity.get() + " does not belong to a Document. Add this ComponentDefinition to a Document before calling insertDownstream");
    if (doc != insert.doc)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Invalid Document for ComponentDefinition " + insert.identity.get() + " Add the insert to the same Document as the calling object.");
    // If the user makes a mistake and tries to insert a ComponentDefinition that doesn't already belong to this Document
    if (insert.doc == NULL)
        insert.doc = doc;
    
    // Two cases. In first case, insert a Component that already has a downstream Component specified by a SequenceConstraint. Otherwise, append this Component to the end os sequential constraints.
    // Search for an existing SequenceConstraint between upstream and downstream Component
    SequenceConstraint* target_constraint = NULL;
    
    // Search for target_constraint
    for (int i_sc = 0; i_sc < sequenceConstraints.size(); ++i_sc)
    {
        SequenceConstraint& sc = sequenceConstraints[i_sc];
        if (sc.subject.get().compare(upstream.identity.get()) == 0 && sc.restriction.get().compare(SBOL_RESTRICTION_PRECEDES) == 0)
        {
            // If more than one downstream component has been specified, then it is ambiguous where the insert should be placed, so throw an error
            if (target_constraint != NULL)
            {
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceConstraints are ambiguous. The target component may have more than one downstream component specified");
            }
            target_constraint = &sc;
        }
    }

    // Generate URI of a Component to be created.  Check if an object with that URI is already instantiated.
    int instance_count = 0;
    string component_id;
    component_id = persistentIdentity.get() + "/" + insert.displayId.get() + "/" + to_string(instance_count) + "/" + version.get();
    while (find(component_id) != NULL)
    {
        // Find the last instance assigned
        ++instance_count;
        component_id = persistentIdentity.get() + "/" + insert.displayId.get() + "/" + to_string(instance_count) + "/" + version.get();
    }
    // Autoconstruct the new Component
    Component& c_insert = components.create(insert.displayId.get() + "/" + to_string(instance_count));
    c_insert.definition.set(insert.identity.get());
    
    // Generate URI of new SequenceConstraint.  Check if an object with that URI is already instantiated.
    instance_count = 0;
    string sc_id;
    sc_id = persistentIdentity.get() + "/constraint" + to_string(instance_count) + "/" + version.get();
    while (find(sc_id) != NULL)
    {
        // Find the last instance assigned
        ++instance_count;
        sc_id = persistentIdentity.get() + "/constraint" + to_string(instance_count) + "/" + version.get();

    }

    // Autoconstruct the new SequenceConstraint
    SequenceConstraint& sc_new = sequenceConstraints.create("constraint" + to_string(instance_count));
    sc_new.subject.set(upstream.identity.get());
    sc_new.object.set(component_id);
    sc_new.restriction.set(SBOL_RESTRICTION_PRECEDES);
    
    // In case a downstream component was found...
    if (target_constraint)
    {
        target_constraint->subject.set(c_insert.identity.get());
    }

};

void ComponentDefinition::insertUpstream(Component& downstream, ComponentDefinition& insert)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + identity.get() + " does not belong to a Document. Add this ComponentDefinition to a Document before calling insertUpstream");
    if (doc != insert.doc)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Invalid Document for ComponentDefinition " + insert.identity.get() + " Add the insert to the same Document as the calling object.");
    // If the user makes a mistake and tries to insert a ComponentDefinition that doesn't already belong to this Document
    if (insert.doc == NULL)
        insert.doc = doc;
    // Two cases. In first case, insert a Component that already has a downstream Component specified by a SequenceConstraint. Otherwise, append this Component to the end os sequential constraints.
    // Search for an existing SequenceConstraint between upstream and downstream Component
    SequenceConstraint* target_constraint = NULL;
    
    // Search for target_constraint
    for (int i_sc = 0; i_sc < sequenceConstraints.size(); ++i_sc)
    {
        SequenceConstraint& sc = sequenceConstraints[i_sc];
        if (sc.object.get().compare(downstream.identity.get()) == 0 && sc.restriction.get().compare(SBOL_RESTRICTION_PRECEDES) == 0)
        {
            // If more than one downstream component has been specified, then it is ambiguous where the insert should be placed, so throw an error
            if (target_constraint != NULL)
            {
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "SequenceConstraints are ambiguous. The target component may have more than one downstream component specified");
            }
            target_constraint = &sc;
        }
    }
    
    // Generate URI of a Component to be created.  Check if an object with that URI is already instantiated.
    int instance_count = 0;
    string component_id;
    component_id = persistentIdentity.get() + "/" + insert.displayId.get() + "/" + to_string(instance_count) + "/" + version.get();
    while (find(component_id) != NULL)
    {
        // Find the last instance assigned
        ++instance_count;
        component_id = persistentIdentity.get() + "/" + insert.displayId.get() + "/" + to_string(instance_count) + "/" + version.get();
    }
    // Autoconstruct the new Component
    Component& c_insert = components.create(insert.displayId.get() + "/" + to_string(instance_count));
    c_insert.definition.set(insert.identity.get());
    
    // Generate URI of new SequenceConstraint.  Check if an object with that URI is already instantiated.
    instance_count = 0;
    string sc_id;
    sc_id = persistentIdentity.get() + "/constraint" + to_string(instance_count) + "/" + version.get();
    while (find(sc_id) != NULL)
    {
        // Find the last instance assigned
        ++instance_count;
        sc_id = persistentIdentity.get() + "/constraint" + to_string(instance_count) + "/" + version.get();
    }
    
    // Autoconstruct the new SequenceConstraint
    SequenceConstraint& sc_new = sequenceConstraints.create("constraint" + to_string(instance_count));
    sc_new.subject.set(component_id);
    sc_new.object.set(downstream.identity.get());
    sc_new.restriction.set(SBOL_RESTRICTION_PRECEDES);
    
    // In case an upstream component was found...
    if (target_constraint)
    {
        target_constraint->object.set(c_insert.identity.get());
    }

};

void ComponentDefinition::addUpstreamFlank(Component& downstream, std::string elements)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + identity.get() + " does not belong to a Document. Add this ComponentDefinition to a Document before attempting to insert a flanking Component");

    // Generate URI of flanking ComponentDefinition.  Check if an object with that URI is already instantiated.
    ComponentDefinition* flank = NULL;
    int instance_count = 0;
    string flank_display_id = "flank" + to_string(instance_count);
    while (flank == NULL)
    {
        try
        {
            flank = &doc->componentDefinitions.create(flank_display_id);
        }
        catch(SBOLError &e)
        {
            instance_count++;
            flank_display_id = "flank" + to_string(instance_count);
        }
    }
    
    // Set to Sequence Ontology "flanking_sequence"
    flank->roles.set(SO "0000239");

    // Generate URI of flanking Sequence.  Check if an object with that URI is already instantiated.
    Sequence* flank_seq = NULL;
    instance_count = 0;
    flank_display_id = "flank_seq" + to_string(instance_count);
    while (flank_seq == NULL)
    {
        try
        {
            flank_seq = &doc->sequences.create(flank_display_id);
        }
        catch(sbol::SBOLError &e)
        {
            instance_count++;
            flank_display_id = "flank_seq" + to_string(instance_count);
        }
    }
    
    // Assign primary sequence elements
    flank_seq->elements.set(elements);
    
    // Now add the Sequence to the ComponentDefinition
    flank->sequences.set(flank_seq->identity.get());

    // Insert the new flank upstream
    insertUpstream(downstream, *flank);
};

void ComponentDefinition::addDownstreamFlank(Component& upstream, std::string elements)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + identity.get() + " does not belong to a Document. Add this ComponentDefinition to a Document before attempting to insert a flanking Component");
    
    // Generate URI of flanking ComponentDefinition.  Check if an object with that URI is already instantiated.
    ComponentDefinition* flank = NULL;
    int instance_count = 0;
    string flank_display_id = "flank" + to_string(instance_count);
    while (flank == NULL)
    {
        try
        {
            flank = &doc->componentDefinitions.create(flank_display_id);
        }
        catch(SBOLError &e)
        {
            instance_count++;
            flank_display_id = "flank" + to_string(instance_count);
        }
    }
    
    // Set to Sequence Ontology "flanking_sequence"
    flank->roles.set(SO "0000239");
    
    // Generate URI of flanking Sequence.  Check if an object with that URI is already instantiated.
    Sequence* flank_seq = NULL;
    instance_count = 0;
    flank_display_id = "flank_seq" + to_string(instance_count);
    while (flank_seq == NULL)
    {
        try
        {
            flank_seq = &doc->sequences.create(flank_display_id);
        }
        catch(sbol::SBOLError &e)
        {
            instance_count++;
            flank_display_id = "flank_seq" + to_string(instance_count);
        }
    }
    
    // Assign primary sequence elements
    flank_seq->elements.set(elements);
    
    // Now add the Sequence to the ComponentDefinition
    flank->sequences.set(flank_seq->identity.get());
    
    // Insert the new flank upstream
    insertDownstream(upstream, *flank);
};

std::vector<Component*> ComponentDefinition::getPrimaryStructure()
{
    std::vector<Component*> primary_structure;
    Component* c = &getFirstComponent();
    primary_structure.push_back(c);
    while (hasDownstreamComponent(*c))
    {
        c = &getDownstreamComponent(*c);
        primary_structure.push_back(c);
    }
    return primary_structure;
};