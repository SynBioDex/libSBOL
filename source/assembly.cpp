#include "assembly.h"

#include <stdio.h>

using namespace std;
using namespace sbol;

//// @TODO: make this a member function of ComponentDefinition class
//ComponentDefinition& initializeStructure(ComponentDefinition& parent_component, vector<ComponentDefinition*> list_of_subcomponents)
//{
//    if (parent_component.components.size() > 0)
//        // @TODO Allow adding subcomponents to a root object that already has subcomponents
//        cerr << "The parent component appears to have been initialized already."
//        throw;
//    else
//    {
//        cout << "Auto constructing components"
//        // Instantiate parent Component
//        string root_id;
//        if (isSBOLCompliant())
//            root_id = getCompliantURI(parent_component.identity.get(), "Component", to_string(), parent_component.version.get());
//        else
//            root_id = parent_component.identity.get() + "#"
//        Component& root = *new Component(root_id);
//                                         
//        // Instantiate child Components
//        for (auto i_cd = 0; i_cd != list_of_subcomponents.size(); i_cd++)
//        {
//            // Create list of new Component objects from the Definitions contained in list_of_components
//            ComponentDefinition& cd = list_of_subcomponents[i_cd];
//
//    }
//};

void sbol::join(ComponentDefinition& parent_component, vector<ComponentDefinition*> list_of_components)
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
//                string new_uri = "ComponentDefinition/" + component.displayId.get() + "/Component/" + to_string(i_com+1) + "/" + component.version.get();
                string temp_displayId = "ComponentDefinition/" + parent_component.displayId.get() + "/" + cdef.displayId.get();
                Component* component_instance = new Component(temp_displayId, cdef.identity.get(), SBOL_ACCESS_PRIVATE, cdef.version.get());
                component_instance->displayId.set(cdef.displayId.get());
                parent_component.components.add(*component_instance);
                //component.doc->add<Component>(*component_instance);
                list_of_instances.push_back(component_instance);
            }
            for (auto i_com = 1; i_com != list_of_components.size(); i_com++)
            {
                ComponentDefinition& cd_upstream = *list_of_components[i_com - 1];
                ComponentDefinition& cd_downstream = *list_of_components[i_com];
                //string new_seq_constraint_uri = "ComponentDefinition/" + cd_upstream.displayId.get() + "/SequenceConstraint/" + to_string(i_com) + "/" + cd_upstream.version.get();
                
                Component& constraint_subject = *list_of_instances[i_com - 1];
                Component& constraint_object = *list_of_instances[i_com];
                
                string temp_displayId = "ComponentDefinition/" + parent_component.displayId.get() + "/constraint" + to_string(i_com);
                SequenceConstraint& joint = *new SequenceConstraint(temp_displayId, constraint_subject.identity.get(), constraint_object.identity.get(), SBOL_RESTRICTION_PRECEDES, constraint_subject.version.get());
                joint.displayId.set("constraint" + to_string(i_com));
                // @TODO update SequenceAnnotation starts and ends
                parent_component.sequenceConstraints.add(joint);
            }
        }
        else
            throw;
        //@TODO update sequenceAnnotations
    }
}

void sbol::assemble(ComponentDefinition& parent_component, vector<ComponentDefinition*> list_of_subcomponents)
{
    join(parent_component, list_of_subcomponents);
    for (auto i_com = 0; i_com != list_of_subcomponents.size(); i_com++)
    {
        if (isSBOLCompliant())
        {
            //Autoconstruct URI
            ComponentDefinition& subcomponent = *list_of_subcomponents[i_com];
            string new_uri = "ComponentDefinition/" + subcomponent.displayId.get() + "/Component/" + to_string(i_com+1) + "/" + subcomponent.version.get();
            toggleSBOLCompliance();  // Enable constructors with raw URI
            Component& subcomponent_instance = *new Component(new_uri, subcomponent.identity.get(), SBOL_ACCESS_PRIVATE, subcomponent.version.get());
            toggleSBOLCompliance();
            parent_component.components.add(subcomponent_instance);
        }
        else
            throw;
    }
}