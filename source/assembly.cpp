#include "assembly.h"

#include <stdio.h>

using namespace std;
using namespace sbol;


int sbol::hasUpstreamComponent(ComponentDefinition& cd_root, Component& current_component)
{
    if (cd_root.sequenceConstraints.size() < 0)
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

int sbol::hasDownstreamComponent(ComponentDefinition& cd_root, Component& current_component)
{
    if (cd_root.sequenceConstraints.size() < 0)
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

Component& sbol::getUpstreamComponent(ComponentDefinition& cd_root, Component& current_component)
{
    if (cd_root.sequenceConstraints.size() < 0)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else if (!hasUpstreamComponent(cd_root, current_component))
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
        Component& upstream_component = cd_root.doc->get<Component>(upstream_component_id);
        return upstream_component;
    }
}

Component& sbol::getDownstreamComponent(ComponentDefinition& cd_root, Component& current_component)
{
    if (cd_root.sequenceConstraints.size() < 0)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else if (!hasDownstreamComponent(cd_root, current_component))
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
        Component& downstream_component = cd_root.doc->get<Component>(downstream_component_id);
        return downstream_component;
    }
}

Component& sbol::getFirstComponent(ComponentDefinition& cd_root)
{
    if (cd_root.components.size() < 0)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {
        Component& arbitrary_component = cd_root.components[0];
        Component& iterator_component = arbitrary_component;
        while (hasUpstreamComponent(cd_root, iterator_component))
        {
            iterator_component = getUpstreamComponent(cd_root, iterator_component);
        }
        return iterator_component;
    }
}

Component& sbol::getLastComponent(ComponentDefinition& cd_root)
{
    if (cd_root.components.size() < 0)
        throw;
    else if (cd_root.doc == NULL)
        throw;
    else
    {
        Component* arbitrary_component = &cd_root.components[0];
        Component* iterator_component = arbitrary_component;
        while (hasDownstreamComponent(cd_root, *iterator_component))
        {
            iterator_component = &getDownstreamComponent(cd_root, *iterator_component);
        }
        return *iterator_component;
    }
}

vector<Component*> sbol::getInSequentialOrder(ComponentDefinition& cd_root)
{
//    if (cd_root.sequenceConstraints.size() < 0)
//        throw;
//    else
//    {
//        while (hasUpstreamComponent(cd_root))
//        {
//            
//        }
//        string upstream_component_id;
//        for (auto i_sc = cd_root.sequenceConstraints.begin(); i_sc != cd_root.sequenceConstraints.end(); i_sc++)
//        {
//            SequenceConstraint& sc = *i_sc;
//            if (sc.object.get() == current_component.identity.get() && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
//                string upstream_component_id = sc.subject.get();
//        }
//        Component& upstream_component = cd_root.doc->get<Component>(upstream_component_id);
//        return upstream_component;
//    }
}

void sbol::updateSequence(ComponentDefinition& parent_component)
{
//    if (parent_component.components.size() > 0)
//    {
//        string upstream_component_uri = "";
//        for (auto i_sc = parent_component.sequenceConstraints.begin(); i_sc != parent_component.end(); i_sc++)
//        {
//            SequenceConstraint& sc = *i_sc;
//            if (upstream_component_uri == "" && sc.restriction.get() == SBOL_RESTRICTION_PRECEDES)
//            {
//                upstream_component_uri = sc.restriction.subject.get();
//            }
//            else if (upstream_component_uri != "" && sc.restriction.get == SBOL_RESTRICTION_PRECEDES)
//            {
//                
//            }
//        }
//        
//        for (auto i_c = parent_component.components.begin(); i_c != parent_component.components.end(); i_c++)
//        {
//            Component& c = *i_c;
//            ComponentDefinition& cdef = parent_component.doc->get<ComponentDefinition>(c.definition.get());
//            updateSequence(cdef);
//            if (cdef.sequence.get() != "")
//            {
//                
//            }
//        }
//    }
}

void sbol::assemble(ComponentDefinition& parent_component, vector<ComponentDefinition*> list_of_components)
{
    if (list_of_components.size() < 2)
    {
        throw;
    }
    else
    {
        if (isSBOLCompliant())
        {
            vector<Component*> list_of_instances = {};
            for (auto i_com = 0; i_com != list_of_components.size(); i_com++)
            {
                ComponentDefinition& cdef = *list_of_components[i_com];
                //string temp_displayId = "ComponentDefinition/" + parent_component.displayId.get() + "/" + cdef.displayId.get();
                //Component* component_instance = new Component(temp_displayId, cdef.identity.get(), SBOL_ACCESS_PRIVATE, cdef.version.get());
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
                
//                string temp_displayId = "ComponentDefinition/" + parent_component.displayId.get() + "/constraint" + to_string(i_com);
//                SequenceConstraint& joint = *new SequenceConstraint(temp_displayId, constraint_subject.identity.get(), constraint_object.identity.get(), SBOL_RESTRICTION_PRECEDES, constraint_subject.version.get());
//                joint.displayId.set("constraint" + to_string(i_com));

                // @TODO update SequenceAnnotation starts and ends
//                parent_component.sequenceConstraints.add(joint);
                
                SequenceConstraint& sc = parent_component.sequenceConstraints.create("constraint" + to_string(i_com));
                sc.subject.set(constraint_subject.identity.get());
                sc.object.set(constraint_object.identity.get());
                sc.restriction.set(SBOL_RESTRICTION_PRECEDES);
            }
        }
        else
            throw;
        //@TODO update sequenceAnnotations
    }
}

