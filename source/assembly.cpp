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
#include <algorithm>
#include <unordered_map>
#include <queue>

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
    if (cd_root.components.size() == 1)
        return { &cd_root.components[0] };
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

//void ComponentDefinition::assemble(vector<string> list_of_uris, Document& doc)
//{
//    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
//        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Assemble methods require SBOL-compliance enabled");
//    ComponentDefinition& parent_component = *this;
//    if (parent_component.doc == NULL)
//        doc.add<ComponentDefinition>(parent_component);
//    else if (parent_component.doc != &doc)
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot assemble " + identity.get() + " because it does not belong to the target Document");
//    std::vector<ComponentDefinition*> list_of_components;
//    for (auto & uri : list_of_uris)
//    {
//        ComponentDefinition& cdef = doc.componentDefinitions.get(uri);
//        list_of_components.push_back(&cdef);
//    }
//    assemble(list_of_components, doc);
//}

void ComponentDefinition::assemble(vector<string>& list_of_uris, string assembly_standard)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Assemble methods require SBOL-compliance enabled");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot perform assembly operation on ComponentDefinition because it does not belong to a Document. You may pass a Document as an optional second argument to this method. Otherwise add this ComponentDefinition to a Document");
    }
    ComponentDefinition& parent_component = *this;
    std::vector<ComponentDefinition*> list_of_components;
    for (auto & uri : list_of_uris)
    {
        ComponentDefinition& cdef = doc->componentDefinitions.get(uri);
        list_of_components.push_back(&cdef);
    }
    assemble(list_of_components);
}

void ComponentDefinition::assemblePrimaryStructure(vector<string>& primary_structure, string assembly_standard)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Assemble methods require SBOL-compliance enabled");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot perform assembly operation on ComponentDefinition because it does not belong to a Document. You may pass a Document as an optional second argument to this method. Otherwise add this ComponentDefinition to a Document");
    }
    ComponentDefinition& parent_component = *this;
    std::vector<ComponentDefinition*> list_of_components;
    for (auto & uri : primary_structure)
    {
        ComponentDefinition& cdef = doc->componentDefinitions.get(uri);
        list_of_components.push_back(&cdef);
    }
    assemblePrimaryStructure(list_of_components, assembly_standard);
};

void ComponentDefinition::assemblePrimaryStructure(vector<ComponentDefinition*>& primary_structure, string assembly_standard)
{
    assemble(primary_structure, assembly_standard);
    linearize(primary_structure);
};

void ComponentDefinition::assemblePrimaryStructure(vector<ComponentDefinition*>& primary_structure, Document& doc, string assembly_standard)
{
    assemble(primary_structure, doc, assembly_standard);
    linearize(primary_structure);
};

/// @TODO update SequenceAnnotation starts and ends
void ComponentDefinition::assemble(vector<ComponentDefinition*>& list_of_components, Document& doc, string assembly_standard)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "Assemble methods require SBOL-compliance enabled");

    ComponentDefinition& parent_component = *this;
    if (parent_component.doc == NULL)
        doc.add<ComponentDefinition>(parent_component);
    
    if (assembly_standard == IGEM_STANDARD_ASSEMBLY)
    {
        ComponentDefinition* scar;
        ComponentDefinition* alternate_scar;
        ComponentDefinition* scar_instance;
        try
        {
            scar = &doc.componentDefinitions.create("scar");
            Sequence* scar_seq = &doc.sequences.create("scar_seq");
            scar_seq->elements.set("tactagag");
            scar->sequences.set(scar_seq->identity.get());
        }
        catch(SBOLError& e)
        {
            scar = &doc.componentDefinitions["scar"];
        }
        try
        {
            alternate_scar = &doc.componentDefinitions.create("alternate_scar");
            Sequence* alternate_scar_seq = &doc.sequences.create("alternate_scar_seq");
            alternate_scar_seq->elements.set("tactag");
            alternate_scar->sequences.set(alternate_scar_seq->identity.get());
        }
        catch(SBOLError& e)
        {
            alternate_scar = &doc.componentDefinitions["alternate_scar"];
        }
        vector<ComponentDefinition*> temp_list_of_components = list_of_components;
        list_of_components.clear();
        for (int i = 0; i < (temp_list_of_components.size() - 1); ++i)
        {
            ComponentDefinition& cd_upstream = *temp_list_of_components[i];
            ComponentDefinition& cd_downstream = *temp_list_of_components[i+1];
            if (cd_upstream.roles.size() && cd_downstream.roles.size() && cd_upstream.roles.get() == SO_RBS && cd_downstream.roles.get() == SO_CDS)
                scar_instance = alternate_scar;
            else
                scar_instance = scar;
            list_of_components.push_back(&cd_upstream);
            list_of_components.push_back(scar_instance);
        }
        list_of_components.push_back(temp_list_of_components[temp_list_of_components.size() - 1]);
    }

    vector<Component*> list_of_instances = {};
    for (auto i_com = 0; i_com != list_of_components.size(); i_com++)
    {
        // Instantiate the Component defined by the ComponentDefinition
        ComponentDefinition& cdef = *list_of_components[i_com];
        int instance_count = 0;
            
        if (cdef.doc == NULL)
            doc.add<ComponentDefinition>(cdef);
        else if (cdef.doc != &doc)
            throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + cdef.identity.get() + " cannot be assembled because it belongs to a different Document than the calling object.");
            
            
        // Generate URI of new Component.  Check if an object with that URI is already instantiated.
        string component_id;
        component_id = persistentIdentity.get() + "/" + cdef.displayId.get() + "_" + to_string(instance_count) + "/" + parent_component.version.get();

        while (parent_component.find(component_id) != NULL)
        {
            // Find the last instance assigned
            ++instance_count;
            component_id = persistentIdentity.get() + "/" + cdef.displayId.get() + "_" + to_string(instance_count) + "/" + parent_component.version.get();
        }

        Component& c = parent_component.components.create(cdef.displayId.get() + "_" + to_string(instance_count));
        c.definition.set(cdef.identity.get());
        list_of_instances.push_back(&c);
        string def = cdef.identity.get();
        parent_component.components.validate(&def);   // Validate.  This is useful for extension methods which use the assemble method
    }
}


void ComponentDefinition::assemble(vector<ComponentDefinition*>& list_of_components, string assembly_standard)
{
    // Throw an error if this ComponentDefinition is not attached to a Document
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot perform assembly operation on ComponentDefinition because it does not belong to a Document.");
    }
    assemble(list_of_components, *doc, assembly_standard);
}

std::string Sequence::compile()
{
    assemble();
    return elements.get();
}

std::string ComponentDefinition::compile()
{
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot perform compile operation on ComponentDefinition because it does not belong to a Document.");
    }
    Sequence* seq;
    if (sequences.size() == 0)
    {
        if (Config::getOption("sbol_compliant_uris") == "True")
        {
            string display_id = displayId.get();
            if (Config::getOption("sbol_typed_uris") == "False")
                display_id = display_id + "_seq";
            seq = &doc->sequences.create(display_id);
            sequence.set(*seq);
            sequences.set(seq->identity.get());

        } else
        {
            seq = &doc->sequences.create(identity.get() + "_seq");
            sequence.set(*seq);
            sequences.set(seq->identity.get());
        }
    }
    else 
    {
        seq = &doc->get<Sequence>(sequences.get());
    }
    return seq->compile();
}


ComponentDefinition& Sequence::synthesize(std::string clone_id)
{
    // Throw an error if this Sequence is not attached to a Document
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Sequence cannot be synthesized because it does not belong to a Document. Add the Sequence to a Document.");
    }
    ComponentDefinition* target;
    for (auto & cd : doc->componentDefinitions)
        if (cd.sequences.get().compare(identity.get()) == 0)
            target = &cd;
    ComponentDefinition& design = *target;
    ComponentDefinition& build = design.simpleCopy < ComponentDefinition > (clone_id);
    build.wasDerivedFrom.set(design.identity.get());
    return build;
}

string Sequence::assemble(string composite_sequence)
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
            if (cdef->sequences.size() && cdef->sequences.get() == identity.get())
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
    if (parent_component.components.size() == 1)
    {
        Component& c = parent_component.components[0];
        ComponentDefinition& cdef = doc->get < ComponentDefinition > (c.definition.get());
        Sequence& seq = doc->get < Sequence > (cdef.sequences.get());
        
        // Check for regularity -- only one SequenceAnnotation per Component is allowed
        vector < SBOLObject* > sequence_annotations = parent_component.find_property_value(SBOL_COMPONENT_PROPERTY, c.identity.get());
        if (sequence_annotations.size() > 1)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Sequence cannot be assembled. Component " + c.identity.get() + " is irregular. More than one SequenceAnnotation is associated with this Component");
        
        // Auto-construct a SequenceAnnotation for this Component if one doesn't already exist
        if (sequence_annotations.size() == 0)
        {
            string sa_id;
            if (Config::getOption("sbol_compliant_uris") == "True")
                sa_id = cdef.displayId.get();
            else
                sa_id = cdef.identity.get();
            SequenceAnnotation& sa = parent_component.sequenceAnnotations.create<SequenceAnnotation>(sa_id + "_annotation");
            sa.component.set(c);
            sequence_annotations.push_back((SBOLObject*)&sa);

        }
        SequenceAnnotation& sa = *(SequenceAnnotation*)sequence_annotations[0];

        // Check for regularity -- only one Range per SequenceAnnotation is allowed
        vector < Range* > ranges;
        if (sa.locations.size() > 0)
        {
            // Look for an existing Range that can be re-used
            for (auto & l : sa.locations)
                if (l.type == SBOL_RANGE)
                    ranges.push_back((Range*)&l);
        }
        else
        {
            // Auto-construct a Range
            string range_id;
            if (Config::getOption("sbol_compliant_uris") == "True")
                range_id = sa.displayId.get();
            else
                range_id = sa.identity.get();
            Range& r = sa.locations.create<Range>(range_id + "_range");
            ranges.push_back((Range*)&r);
        }
        if (ranges.size() > 1)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Sequence cannot be assembled. SequenceAnnotation " + sa.identity.get() + " is irregular. More than one Range is associated with this SequenceAnnotation");
        
        Range& r = *ranges[0];
        r.start.set((int)composite_sequence.size() + 1);
        r.end.set((int)composite_sequence.size() + (int)seq.elements.get().size());
                  
        // Validate parent sequence element are same as this one
        return seq.elements.get();
    }

    else if (parent_component.components.size() > 1)
    {
        // Recurse into subcomponents and assemble their sequence
        size_t composite_sequence_initial_size = composite_sequence.size();
        vector<Component*> subcomponents = parent_component.getInSequentialOrder();
        for (auto i_c = subcomponents.begin(); i_c != subcomponents.end(); i_c++)
        {
            Component& c = **i_c;
            ComponentDefinition& cdef = doc->get < ComponentDefinition > (c.definition.get());
            if (cdef.sequences.size() == 0)
            {
                if (Config::getOption("sbol_compliant_uris") == "True")
                {
                    Sequence& seq = doc->sequences.create(cdef.displayId.get());
                    cdef.sequence.set(seq);
                    cdef.sequences.set(seq.identity.get());
                } else
                {
                    Sequence& seq = doc->sequences.create(cdef.identity.get() + "_seq");
                    cdef.sequence.set(seq);
                    cdef.sequences.set(seq.identity.get());
                }
            }
            Sequence& seq = doc->get < Sequence > (cdef.sequences.get());
            
            // Check for regularity -- only one SequenceAnnotation per Component is allowed
            vector < SBOLObject* > sequence_annotations = parent_component.find_property_value(SBOL_COMPONENT_PROPERTY, c.identity.get());
            if (sequence_annotations.size() > 1)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Sequence cannot be assembled. Component " + c.identity.get() + " is irregular. More than one SequenceAnnotation is associated with this Component");
            
            // Auto-construct a SequenceAnnotation for this Component if one doesn't already exist
            if (sequence_annotations.size() == 0)
            {
                string sa_id;
                int sa_instance = 0;
                if (Config::getOption("sbol_compliant_uris") == "True")
                    sa_id = cdef.displayId.get();
                else
                    sa_id = cdef.identity.get();
                SequenceAnnotation* sa = NULL;
                while (sa == NULL)
                {
                    try
                    {
                        sa = &parent_component.sequenceAnnotations.create<SequenceAnnotation>(sa_id + "_annotation_" + to_string(sa_instance));
                    }
                    catch(SBOLError& e)
                    {
                        if (e.error_code() == SBOL_ERROR_URI_NOT_UNIQUE)
                            ++sa_instance;
                        else
                            throw SBOLError(e.error_code(), e.what());
                    }
                }
                sa->component.set(c);
                sequence_annotations.push_back((SBOLObject*)sa);
            }
            SequenceAnnotation& sa = *(SequenceAnnotation*)sequence_annotations[0];
            
            // Check for regularity -- only one Range per SequenceAnnotation is allowed
            vector < Range* > ranges;
            if (sa.locations.size() > 0)
            {
                // Look for an existing Range that can be re-used
                for (auto & l : sa.locations)
                    if (l.type == SBOL_RANGE)
                        ranges.push_back((Range*)&l);
            }
            else
            {
                // Auto-construct a Range
                string range_id;
                if (Config::getOption("sbol_compliant_uris") == "True")
                    range_id = sa.displayId.get();
                else
                    range_id = sa.identity.get();
                Range& r = sa.locations.create<Range>(range_id + "_range");
                ranges.push_back((Range*)&r);
            }
            if (ranges.size() > 1)
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Sequence cannot be assembled. SequenceAnnotation " + sa.identity.get() + " is irregular. More than one Range is associated with this SequenceAnnotation");
            
                                
            Range& r = *ranges[0];
            r.start.set((int)composite_sequence.size() + 1);
                                
            composite_sequence = composite_sequence + seq.assemble(composite_sequence);  // Recursive call
            //composite_sequence = composite_sequence + seq.assemble();  // Recursive call
                                
            r.end.set((int)composite_sequence.size());
        }
        string subsequence = composite_sequence.substr(composite_sequence_initial_size, composite_sequence.size());                        
        elements.set(subsequence);
        return subsequence;
    }
    else
    {
        std::string parent_component_seq = parent_component.sequences.get();
        Sequence& seq = doc->get < Sequence >(parent_component.sequences.get());
        if (seq.elements.size() == 0)
            return "";
        else
            return seq.elements.get();
    }
};

void ModuleDefinition::assemble(vector < ModuleDefinition* > list_of_modules)
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

void ModuleDefinition::setOutput(FunctionalComponent& output)
{
    ModuleDefinition* parent_mdef = (ModuleDefinition*)output.parent;
    if (parent_mdef != this)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot set output. FunctionalComponent " + output.identity.get() + " does not belong to ModuleDefinition " + this->identity.get());
    output.direction.set(SBOL_DIRECTION_OUT);
};

void ModuleDefinition::setInput(FunctionalComponent& input)
{
    ModuleDefinition* parent_mdef = (ModuleDefinition*)input.parent;
    if (parent_mdef != this)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot set input. FunctionalComponent " + input.identity.get() + " does not belong to ModuleDefinition " + this->identity.get());
    input.direction.set(SBOL_DIRECTION_IN);
};

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

void ModuleDefinition::connect(FunctionalComponent& output, FunctionalComponent& input)
{
    ModuleDefinition* parent_mdef = (ModuleDefinition*)this;

    ModuleDefinition* subject_mdef = (ModuleDefinition*)output.parent;
    if (!subject_mdef)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The output does not belong to a ModuleDefinition" );

    ModuleDefinition* object_mdef = (ModuleDefinition*)input.parent;
    if (!object_mdef)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The input does not belong to a ModuleDefinition" );
 
    // Instantiate FunctionalComponent in parent ModuleDefinition
    Module* subject_module = NULL;
    Module* object_module = NULL;
    for (auto & m : parent_mdef->modules)
    {
        if (m.definition.get() == subject_mdef->identity.get())
            subject_module = &m;
        if (m.definition.get() == object_mdef->identity.get())
            object_module = &m;
    }
    if (!subject_module)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The output does not belong to a sub-Module of ModuleDefinition " + parent_mdef->identity.get() );
    if (!object_module)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The input does not belong to a sub-Module of ModuleDefinition " + parent_mdef->identity.get() );
    
    if (input.direction.get() != SBOL_DIRECTION_IN && input.direction.get() != SBOL_DIRECTION_NONE)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The input component must have direction SBOL_DIRECTION_IN");
    if (output.direction.get() != SBOL_DIRECTION_OUT && output.direction.get() != SBOL_DIRECTION_NONE)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot connect " + output.identity.get() + " to " + input.identity.get() + ". The output component must have direction SBOL_DIRECTION_OUT");
    
    // Generate URI of new FunctionalComponent for the connection.  Check if an object with that URI is already instantiated.
    string connection_id;
    int instance_count = 0;
    if (Config::getOption("sbol_compliant_uris") == "True")
        connection_id = parent_mdef->persistentIdentity.get() + "/connection_" + to_string(instance_count) + "/" + parent_mdef->version.get();
    else
        connection_id = parent_mdef->identity.get() + "_connection_" + to_string(instance_count);
    while (parent_mdef->find(connection_id))
    {
        // Find the last instance assigned
        ++instance_count;
        if (Config::getOption("sbol_compliant_uris") == "True")
            connection_id = parent_mdef->persistentIdentity.get() + "/connection_" + to_string(instance_count) + "/" + parent_mdef->version.get();
        else
            connection_id = parent_mdef->identity.get() + "_connection_" + to_string(instance_count);
    }
    FunctionalComponent& bridge_fc = parent_mdef->functionalComponents.create("");
    bridge_fc.identity.set(connection_id);
    bridge_fc.displayId.set("connection_" + to_string(instance_count));
    
    // Link the modules through the bridge FunctionalComponent contained in the parent ModuleDefinition
    // If the input and output do not share the same definition, then the output will be assumed to override the input component
    bridge_fc.definition.set(output.definition.get());

    string output_id;
    if (Config::getOption("sbol_compliant_uris") == "True")
        output_id = output.displayId.get();
    else
        output_id = output.identity.get();
    MapsTo& half_connection1 = subject_module->mapsTos.create(output_id);
    half_connection1.local.set(bridge_fc.identity.get());
    half_connection1.remote.set(output.identity.get());
    
    string input_id;
    if (Config::getOption("sbol_compliant_uris") == "True")
        input_id = input.displayId.get();
    else
        input_id = input.identity.get();
    MapsTo& half_connection2 = object_module->mapsTos.create(input_id);
    half_connection2.local.set(bridge_fc.identity.get());
    half_connection2.remote.set(input.identity.get());
    
    if (input.definition.get() == output.definition.get())
    {
        half_connection1.refinement.set(SBOL_REFINEMENT_VERIFY_IDENTICAL);
        half_connection2.refinement.set(SBOL_REFINEMENT_VERIFY_IDENTICAL);
    }
    else
    {
        half_connection1.refinement.set(SBOL_REFINEMENT_USE_REMOTE);
        half_connection2.refinement.set(SBOL_REFINEMENT_USE_LOCAL);
    }
    
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

ComponentDefinition& ComponentDefinition::build()
{
	return *new ComponentDefinition();
};

void ComponentDefinition::participate(Participation& species)
{
    species.define(*this);
};

void FunctionalComponent::mask(FunctionalComponent& masked_component)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");
//    if (doc == NULL)
//    {
//        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "These FunctionalComponents cannot be connected because they do not belong to a Document.");
//    }
    
    // Search for ModuleDefinition that this FunctionalComponent belongs to. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* subject_mdef = (ModuleDefinition*)this->parent;
//    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject* obj = i_obj->second;
//        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
//        {
//            ModuleDefinition* mdef = (ModuleDefinition*)obj;
//            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
//            {
//                FunctionalComponent& fc = *i_fc;
//                if (fc.identity.get() == identity.get())
//                {
//                    subject_mdef = mdef;
//                }
//            }
//        }
//    }
    if (subject_mdef == NULL)
        throw SBOLError(NOT_FOUND_ERROR, "FunctionalComponent must belong to a ModuleDefinition");
    // The masked component must also belong to a ModuleDefinition. Throw an error if the ModuleDefinition can't be found
    ModuleDefinition* object_mdef = (ModuleDefinition*)masked_component.parent;
//    for (auto i_obj = doc->SBOLObjects.begin(); i_obj != doc->SBOLObjects.end(); ++i_obj)
//    {
//        SBOLObject* obj = i_obj->second;
//        if (obj->getTypeURI() == SBOL_MODULE_DEFINITION)
//        {
//            ModuleDefinition* mdef = (ModuleDefinition*)obj;
//            for (auto i_fc = mdef->functionalComponents.begin(); i_fc != mdef->functionalComponents.end(); ++i_fc)
//            {
//                FunctionalComponent& fc = *i_fc;
//                if (fc.identity.get() == masked_component.identity.get())
//                {
//                    object_mdef = mdef;
//                }
//            }
//        }
//    }
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
        int instance_count = 0;
        string map_id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            map_id = parent_m->persistentIdentity.get() + "/" + parent_m->displayId.get() + "_map_" + to_string(instance_count) + "/" + version.get();
        else
            map_id = parent_m->identity.get() + "_map_" + to_string(instance_count);
        while (parent_m->find(map_id))
        {
            // Find the last instance assigned
            ++instance_count;
        }
        if (Config::getOption("sbol_compliant_uris") == "True")
            override_map = &parent_m->mapsTos.create(parent_m->displayId.get() + "_map_" + to_string(instance_count));
        else
            override_map = &parent_m->mapsTos.create(parent_m->identity.get() + "_map_" + to_string(instance_count));

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

vector<ModuleDefinition*> ModuleDefinition::applyToModuleHierarchy(void (*callback_fn)(ModuleDefinition *, void *), void* user_data)
{
    /* Assumes parent_component is an SBOL data structure of the general form ComponentDefinition(->Component->ComponentDefinition)n where n+1 is an integer describing how many hierarchical levels are in the SBOL structure */
    /* Look at each of the ComponentDef's SequenceAnnotations, is the target base there? */
    if (!doc)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot traverse Component hierarchy without a Document");
    
    bool GET_ALL = true;
    vector<ModuleDefinition*> module_nodes;
    if (modules.size() == 0)
    {
        //        cout << "Adding subcomponent : " << identity.get() << endl;
        module_nodes.push_back(this);  // Add leaf components
        if (callback_fn)
            callback_fn(this, user_data);
    }
    else
    {
        if (GET_ALL)
        {
            //            cout << "Adding subcomponent : " << identity.get() << endl;
            module_nodes.push_back(this);  // Add components with children
            if (callback_fn)
                callback_fn(this, user_data);
        }
        for (auto& subm : modules)
        {
            if (!doc->find(subm.definition.get()))
            {
                //                std::cout << "Not found" << std::endl;
                throw SBOLError(SBOL_ERROR_NOT_FOUND, subm.definition.get() + "not found");
            }
            ModuleDefinition& submdef = doc->get<ModuleDefinition>(subm.definition.get());
            //            std::cout << subcdef.identity.get() << std::endl;
            //            cout << "Descending one level : " << subcdef.identity.get() << endl;
            vector < sbol::ModuleDefinition* > submodules = submdef.applyToModuleHierarchy(callback_fn, user_data);
            //            cout << "Found " << subcomponents.size() << " components" << std::endl;
            module_nodes.reserve(module_nodes.size() + distance(submodules.begin(), submodules.end()));
            module_nodes.insert(module_nodes.end(), submodules.begin(),submodules.end());
        }
    }
    return module_nodes;
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
        return comparand.start.get() - end.get();
    else
        return 0;
}

int Range::follows(Range& comparand)
{
    if (start.get() > comparand.end.get())
        return comparand.end.get() - start.get();
    else
        return 0;
}

int Range::adjoins(Range& comparand)
{
    if (comparand.end.get() + 1 == start.get())
        return 1;
    if (end.get() + 1 == comparand.start.get())
        return 1;
    return 0;
}

int Range::contains(Range& comparand)
{
    if (start.get() <= comparand.start.get() && end.get() >= comparand.end.get())
    {
        return comparand.length();
    }
    else
        return 0;
}

int Range::overlaps(Range& comparand)
{
    if (start.get() == comparand.start.get() && end.get() == comparand.end.get())
        return 0;
    else if (start.get() < comparand.start.get() && end.get() < comparand.end.get() && end.get() >= comparand.start.get() )
        return end.get() - comparand.start.get() + 1;
    else if (start.get() > comparand.start.get() && end.get() > comparand.end.get() && start.get() <= comparand.end.get())
        return comparand.end.get() - start.get() + 1;
    else if (comparand.contains(*this))
        return comparand.contains(*this);
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
//    cout << r_this.start.get() << "\t" << r_this.end.get() << "\t";
    for (auto &ann_comparand : comparand_list)
    {
        if (this->contains(*ann_comparand))
        {
            list_of_contained_annotations.push_back(ann_comparand);
            sbol::Range& r_comparand = (sbol::Range&)ann_comparand->locations[0];
            cout << r_comparand.start.get() << "\t" << r_comparand.end.get() << "\n\t\t";
        }
    }
//    cout << endl;
    return list_of_contained_annotations;
};

std::vector<SequenceAnnotation*> SequenceAnnotation::overlaps(std::vector<SequenceAnnotation*> comparand_list)
{
    vector<SequenceAnnotation*> list_of_overlapping_annotations;
    
    sbol::Range& r_this = (sbol::Range&)locations[0];
//    cout << r_this.start.get() << "\t" << r_this.end.get() << "\t";
    for (auto &ann_comparand : comparand_list)
    {
        if (this->overlaps(*ann_comparand))
        {
            list_of_overlapping_annotations.push_back(ann_comparand);
            sbol::Range& r_comparand = (sbol::Range&)ann_comparand->locations[0];
            cout << r_comparand.start.get() << "\t" << r_comparand.end.get() << "\n\t\t";
        }
    }
//    cout << endl;
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

std::vector<ComponentDefinition*> ComponentDefinition::getPrimaryStructure()
{
    std::vector<ComponentDefinition*> primary_structure;
    Component* c = &getFirstComponent();
    ComponentDefinition* cd = &c->doc->componentDefinitions.get(c->definition.get());
    primary_structure.push_back(cd);
    while (hasDownstreamComponent(*c))
    {
        c = &getDownstreamComponent(*c);
        ComponentDefinition* cd = &c->doc->componentDefinitions.get(c->definition.get());
        primary_structure.push_back(cd);
    }
    return primary_structure;
};



int Sequence::length()
{
    return elements.get().length();
};

// Driver function to sort the Ranges
// by start coordinate then by second element of pairs
bool compare_ranges(sbol::Range *a, sbol::Range *b)
{
    if (a->start.get() < b->start.get()) return true;
    if (a->start.get() > b->start.get()) return false;
    
    if (a->end.get() < b->end.get()) return true;
    return false;
}

void is_regular(ComponentDefinition* cdef_node, void * user_data)
{
    // Assumes is_complete

    struct ARG_LIST { bool * IS_REGULAR; string* msg; } args = *(struct ARG_LIST *)user_data;
    
    Sequence& seq = cdef_node->doc->get<Sequence>(cdef_node->sequences.get());
    
    std::vector< sbol::Range* > ranges;  // Contains a list of primary sequence intervals for which new Components, CDefs, and Sequences will be instantiated
    for (auto & ann : cdef_node->sequenceAnnotations)
    {
        if ((ann.locations.size() == 0) || (ann.locations.size() > 1) || (ann.locations[0].type.compare(SBOL_RANGE)))
        {
            *args.msg = *args.msg + "SequenceAnnotation " + ann.identity.get() + " is irregular. A regular SequenceAnnotation contains a single Range.\n";
            *args.IS_REGULAR = false;
        }
        else
        {
            Range& r = ann.locations.get<Range>();
            r.parent = &ann;  // This is a kludge.  For some reason the parent is not properly set, perhaps when copying the parent ComponentDefinition
            ranges.push_back(&r);
        }
    }
    
    sort(ranges.begin(), ranges.end(), compare_ranges);

    if (ranges.size() > 1)
    {
        std::vector < sbol::Range* > nested_ranges;
        for (auto i_r = ranges.begin(); i_r != std::prev(ranges.end()); ++i_r)
        {
            Range& r_a = **i_r;
            Range& r_b = **(std::next(i_r));
            if (r_b.contains(r_a))
            {
                *args.msg = *args.msg + "Found nested Ranges. Range " + r_b.identity.get() + " contains " + r_a.identity.get() + "\n";
                *args.IS_REGULAR = false;
            }
            else if (r_a.contains(r_b))
            {
                *args.msg = *args.msg + "Found nested Ranges. Range " + r_a.identity.get() + " contains " + r_b.identity.get() + "\n";
                *args.IS_REGULAR = false;
            }
            else if (r_a.overlaps(r_b))
            {
                *args.msg = *args.msg + "Found overlappings Ranges. Range " + r_a.identity.get() + " and " + r_b.identity.get() + " overlap.\n";
                *args.IS_REGULAR = false;
            }
            else if (!r_a.adjoins(r_b))
            {
                *args.msg = *args.msg + "Found gap between Ranges. Range " + r_a.identity.get() + " and " + r_b.identity.get() + " are separated by a gap.\n";
                *args.IS_REGULAR = false;
            }
        }
    }
    
    // Validate sum of Range intervals is equal to primary sequence length, in case there is a gap at the end or a Range's interval exceeds the primary sequence length
    int sum_of_ranges = 0;
    for (auto & r : ranges)
    {
        sum_of_ranges += r->length();
    }
    if (seq.length() != sum_of_ranges)
    {
        *args.msg = *args.msg + "The sum of Range lengths is inconsistent with the Sequence length. (" + to_string(sum_of_ranges) + " != " + to_string(seq.length()) + ")\n";
        *args.IS_REGULAR = false;
    }
    
    // Check if Range's interval exceeds the primary sequence length
    Range& r_last = **std::prev(ranges.end());
    if (r_last.end.get() > seq.length())
    {
        *args.msg = *args.msg + "The end coordinate of the last Range exceeds the end coordinate of the Sequence. (" + to_string(r_last.end.get()) + " != " + to_string(seq.length()) + ")\n";
        *args.IS_REGULAR = false;
    }
    
    if (!*args.IS_REGULAR)
    {
        args.msg->erase(args.msg->length() - 1);  // Remove trailing newline
        return;
    }
    
    // Confirm regularity
    *args.msg = "Regular.";
    *args.IS_REGULAR = true;
    return;

};

void is_complete(ComponentDefinition* cdef_node, void * user_data)
{
    
    struct ARG_LIST { bool * IS_COMPLETE; string* msg; } args = *(struct ARG_LIST *)user_data;

    if (cdef_node->doc->find(cdef_node->sequences.get()))
    {
        *args.msg = "Complete.";
        *args.IS_COMPLETE = true;

    }
    else
    {
        *args.msg = "Incomplete.";
        *args.IS_COMPLETE = false;
        return;
    }
};


bool ComponentDefinition::isRegular()
{
    string dummy;
    isRegular(dummy);
    std::cout << dummy << std::endl;
    return isRegular(dummy);
}

bool ComponentDefinition::isRegular(std::string &msg)
{
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "ComponentDefinition " + identity.get() + " does not belong to a Document. Cannot verify complete.");
    
    if (!isComplete())
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Incomplete. Cannot verify regular.");
    
    bool IS_REGULAR;
    struct ARG_LIST { bool * IS_REGULAR; string *msg; } args = { &IS_REGULAR, &msg };
    vector<ComponentDefinition*> cdefs = this->applyToComponentHierarchy(is_regular,  &args);
    msg = *args.msg;
    return IS_REGULAR;
};

bool ComponentDefinition::isComplete()
{
    string dummy;
    isComplete(dummy);
    cout << dummy << endl;
    return isComplete(dummy);
}

bool ComponentDefinition::isComplete(std::string &msg)
{
    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot verify complete. ComponentDefinition " + identity.get() + " does not belong to a Document.");
    
    bool IS_COMPLETE;
    struct ARG_LIST { bool * IS_COMPLETE; string *msg; } args = { &IS_COMPLETE, &msg };
    vector<ComponentDefinition*> cdefs = this->applyToComponentHierarchy(is_complete,  &args);
    msg = *args.msg;
    return IS_COMPLETE;
};

//bool ComponentDefinition::disassemble()
//{
//    string dummy;
//    disassemble(dummy);
//    cout << dummy << endl;
//    return disassemble(dummy);
//}

void nest_ranges(std::vector < sbol::Range* > ranges, ComponentDefinition* cdef_node, std::string nucleotides)
{
    std::cout << "Nesting Ranges" << std::endl;
    if (ranges.size() <= 1)
    {
        std::cout << "Stopping iteration" << std::endl;
        return;
    }
    std::vector < sbol::Range* > processed_ranges;
    std::vector < SequenceAnnotation* > removed_anns;

    std::cout << "Iterating pairwise through Ranges" << std::endl;
    Range& r_a = **ranges.begin();
    Range& r_b = **std::next(ranges.begin());

    std::cout << cdef_node->identity.get() << std::endl;
    std::cout << r_a.start.get() << r_a.end.get() << std::endl;
    std::cout << r_b.start.get() << r_b.end.get() << std::endl;

    if (r_b.contains(r_a))
    {
        // Nest ranges
        std::cout << "Nesting Range A inside B" << std::endl;
        std::cout << r_a.start.get() << "\t"  << r_a.end.get() << "\t"  << r_b.start.get() << "\t"  << r_b.end.get() << std::endl;
    
        SequenceAnnotation& ann_a = *(SequenceAnnotation*)r_a.parent;
        SequenceAnnotation& ann_b = *(SequenceAnnotation*)r_b.parent;
    
        std::cout << "Removing old Annotation and Range ";
        std::cout << ann_a.identity.get() << std::endl;
        ann_a.locations.remove(r_a.identity.get());
        cdef_node->sequenceAnnotations.remove(ann_a.identity.get());
        std::cout << "Removed" << std::endl;

        if (ann_b.component.size() == 0)
        {
            std::cout << "Instantiating new Component for annotation B : " << ann_b.identity.get() << std::endl;
    
            std::string display_id = ann_b.displayId.get();
            size_t index = display_id.find("annotation");
            if (index != std::string::npos)
            {
                display_id.replace(index, 10, "component");
            }
            std::cout << "Instantiating Sequence " << display_id << std::endl;
            Sequence& subseq = cdef_node->doc->sequences.create(display_id + "seq");
//            subseq.elements.set(nucleotides.substr(r_b.start.get() - 1, r_b.end.get() - r_b.start.get() + 1));
    
            std::cout << "Instantiating ComponentDefinition " << display_id << std::endl;
            ComponentDefinition& cd = cdef_node->doc->componentDefinitions.create(display_id);
            cd.name.set(ann_b.name.get());
            cd.sequences.set(subseq);
    
            Component& c = cdef_node->components.create(display_id);
            c.definition.set(cd);
            c.name.set(ann_b.name.get());
    
            ann_b.component.set(c.identity.get());
    
                   std::cout << "Created subcomponent has been instantiated, creating nested Range" << std::endl;
            SequenceAnnotation& new_ann = cd.sequenceAnnotations.create(ann_a.displayId.get());
            Range& new_range = new_ann.locations.create<Range>(r_a.displayId.get());
            new_range.start.set(r_a.start.get());
            new_range.end.set(r_a.end.get());
        }
        else
        {
            std::cout << "Subcomponent already instantiated for B. Creating nested Range" << std::endl;
            Component& c = cdef_node->components.get(ann_b.component.get());
            ComponentDefinition& cd = cdef_node->doc->get<ComponentDefinition>(c.definition.get());
            SequenceAnnotation& new_ann = cd.sequenceAnnotations.create(ann_a.displayId.get());
            Range& new_range = new_ann.locations.create<Range>(r_a.displayId.get());
            new_range.start.set(r_a.start.get());
            new_range.end.set(r_a.end.get());
            std::cout << "Created nested Range " << new_range.start.get() << new_range.end.get() << std::endl;
    
            // Should call recursive function here
        }
    
        std::cout << "Freeing old Annotation and Range" << std::endl;
        removed_anns.push_back(&ann_a);
        for (auto i_r = std::next(ranges.begin()); i_r != ranges.end(); ++i_r)
        {
            processed_ranges.push_back(*i_r);
        }
    }
    else if (r_a.contains(r_b))
    {
        std::cout << "Nesting Range B inside A" << std::endl;
        std::cout << r_a.start.get() << "\t"  << r_a.end.get() << "\t"  << r_b.start.get() << "\t"  << r_b.end.get() << std::endl;
    
        SequenceAnnotation& ann_a = *(SequenceAnnotation*)r_a.parent;
        SequenceAnnotation& ann_b = *(SequenceAnnotation*)r_b.parent;
    
//                std::cout << "Removing old Annotation and Range" << std::endl;
        ann_b.locations.remove(r_b.identity.get());
        cdef_node->sequenceAnnotations.remove(ann_b.identity.get());
        
        if (ann_a.component.size() == 0)
        {
            std::cout << "Instantiating new Component for annotation A : " << ann_a.identity.get() << std::endl;
    
            std::string display_id = ann_a.displayId.get();
            size_t index = display_id.find("annotation");
            if (index != std::string::npos)
            {
                display_id.replace(index, 10, "component");
            }
//                    std::cout << "Instantiating Sequence " << display_id << std::endl;
            Sequence& subseq = cdef_node->doc->sequences.create(display_id + "seq");
            subseq.elements.set(nucleotides.substr(r_a.start.get() - 1, r_a.end.get() - r_a.start.get() + 1));

//                    std::cout << "Instantiating ComponentDefinition " << display_id << std::endl;
            ComponentDefinition& cd = cdef_node->doc->componentDefinitions.create(display_id);
            cd.name.set(ann_a.name.get());
            cd.sequences.set(subseq);
    
            Component& c = cdef_node->components.create(display_id);
            c.definition.set(cd);
            c.name.set(ann_a.name.get());
    
            ann_a.component.set(c.identity.get());
    
//                    std::cout << "Now that subcompnent has been instantiated, creating nested Range" << std::endl;
            SequenceAnnotation& new_ann = cd.sequenceAnnotations.create(ann_b.displayId.get());
            Range& new_range = new_ann.locations.create<Range>(r_b.displayId.get());
            new_range.start.set(r_b.start.get());
            new_range.end.set(r_b.end.get());

            std::cout << "Created nested Range " << new_range.start.get() << "\t" << new_range.end.get() << std::endl;
        }
        else
        {
//                    std::cout << "Subcomponent already instantiated. Creating nested Range" << std::endl;
            Component& c = cdef_node->components.get(ann_a.component.get());
            ComponentDefinition& cd = cdef_node->doc->get<ComponentDefinition>(c.definition.get());
            SequenceAnnotation& new_ann = cd.sequenceAnnotations.create(ann_b.displayId.get());
            Range& new_range = new_ann.locations.create<Range>(r_b.displayId.get());
            new_range.start.set(r_b.start.get());
            new_range.end.set(r_b.end.get());
            std::cout << "Created nested Range " << new_range.start.get() << "\t" << new_range.end.get() << std::endl;
        }
    
        std::cout << "Freeing old Annotation and Range" << std::endl;
        processed_ranges.push_back(&r_a);
        for (auto i_r = std::next(std::next(ranges.begin())); i_r != ranges.end(); ++i_r)
            processed_ranges.push_back(*i_r);
        removed_anns.push_back(&ann_b);
    }
    else
    {
        std::cout << "Range " << r_a.start.get() << "\t" << r_a.end.get() << " is Regular" << std::endl;
        for (auto i_r = std::next(ranges.begin()); i_r != ranges.end(); ++i_r)
            processed_ranges.push_back(*i_r);
    }
    std::cout << "Processed ranges" << std::endl;
    for (auto i_r : processed_ranges)
        std::cout << i_r << std::endl;
    std::cout << "Removed ranges" << std::endl;

    for (auto i_a : removed_anns)
    {
        SequenceAnnotation& ann = *i_a;
        Range& r = ann.locations.get<Range>();
        std::cout << &r << std::endl;
        
    }

    nest_ranges(processed_ranges, cdef_node, nucleotides);
    for (auto & removed_ann : removed_anns)
        removed_ann->close();
}

vector<SequenceAnnotation*> ComponentDefinition::sortSequenceAnnotations()
{
    vector<Range*> unsorted_ranges;
    vector<SequenceAnnotation*> sorted_annotations;
    for (auto & ann : sequenceAnnotations)
    {
        for (auto & l : ann.locations)
        {
            if (l.type == SBOL_RANGE)
                unsorted_ranges.push_back((Range*)&l);
        }
    }
    sort(unsorted_ranges.begin(), unsorted_ranges.end(), compare_ranges);
    for (auto & r : unsorted_ranges)
    {
        sorted_annotations.push_back((SequenceAnnotation*)r->parent);
    }
    return sorted_annotations;
};


void disassemble(ComponentDefinition * cdef_node, int range_start)
{
//    std::cout << "Dissembling " << cdef_node->identity.get() << " at " << range_start << std::endl;

//    std::cout << "Getting sequence ";
    Sequence& seq = cdef_node->doc->get<Sequence>(cdef_node->sequences.get());
    std::string nucleotides = seq.elements.get();
    int start_reference = range_start;
    int end_reference = start_reference + nucleotides.length() - 1;
    std::cout << nucleotides << std::endl;

    // Validate only one Range per SequenceAnnotation
//    std::cout << "Validating ranges" << std::endl;
    if (cdef_node->sequenceAnnotations.size() == 0)
        return;
    std::vector< sbol::Range* > ranges;
    for (auto & ann : cdef_node->sequenceAnnotations)
    {
        if ((ann.locations.size() == 0) || (ann.locations.size() > 1) || (ann.locations[0].type.compare(SBOL_RANGE)))
            return;
        Range& r = ann.locations. template get<Range>();
        r.parent = &ann;  // This is a kludge.  For some reason the parent is not properly set, perhaps when copying the parent ComponentDefinition
        ranges.push_back(&r);
    }
    
//    std::cout << "Sorting " << to_string(ranges.size()) << " ranges" << std::endl;
    sort(ranges.begin(), ranges.end(), compare_ranges);
    
//    std::cout << "Ranges sorted " << std::endl;
    // Check if Ranges are ordered
    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

    std::vector < sbol::Range* > regularized_ranges;

    if (ranges.size() == 1)
    {
//        std::cout << "Only one Range found" << std::endl;

        // This needs to be fixed as the start and end depending where in the hierarchy the Range is located
        Range& r = *ranges[0];
        r.start.set(start_reference);
        r.end.set(start_reference + seq.length() - 1);
    }
    else
    {
        // Remove nested and overlapping ranges, this should be implemented as a recursiv
//        std::cout << "Checking for overlaps" << std::endl;

        for (auto i_r = ranges.begin(); i_r != std::prev(ranges.end()); ++i_r)
        {

            Range& r_a = **i_r;
            Range& r_b = **std::next(i_r);
//            std::cout << "Iterating pairwise" << std::endl;
            std::cout << r_a.start.get() << "\t" << r_a.end.get() << "\t" << r_b.start.get() << "\t" << r_b.end.get() << std::endl;

            if (r_a.overlaps(r_b) && !r_a.contains(r_b) && !r_b.contains(r_a))
            {
                std::cout << "Overlapping ranges for Remove A or B?" << std::endl;
                
                SequenceAnnotation* ann_a = (SequenceAnnotation*)r_a.parent;
                SequenceAnnotation* ann_b = (SequenceAnnotation*)r_b.parent;
                std::cout << "A: " << ann_a->name.get() << "\t" << "B: " << ann_b->name.get() << std::endl;
                char c = getchar();
                if (c == 'A')
                {
                    regularized_ranges.push_back(&r_b);
                    Location& loc = ann_a->locations.remove(r_a.identity.get());
                }
                else if (c == 'B')
                {
                    regularized_ranges.push_back(&r_a);
                    Location& loc = ann_b->locations.remove(r_b.identity.get());
                }
                // Should call recursive function here
            }
            else if (i_r == (ranges.end() - 2))
            {
//                std::cout << "Adding two" << std::endl;

                regularized_ranges.push_back(&r_a);
                regularized_ranges.push_back(&r_b);
            }
            else
            {
//                std::cout << "Adding one" << std::endl;
                regularized_ranges.push_back(&r_a);

            }
        }
//        std::cout << "Freeing overlap annotations" << std::endl;

        std::vector < SequenceAnnotation* > stale_anns;
        for (auto & r : ranges)
            if ( std::find(regularized_ranges.begin(), regularized_ranges.end(), r) == regularized_ranges.end() )
            {
                stale_anns.push_back((SequenceAnnotation*)r->parent);
            }
        for (auto & stale_ann : stale_anns)
        {
            cdef_node->sequenceAnnotations.remove(stale_ann->identity.get());
            stale_ann->close();
        }
        


        ranges = regularized_ranges;
        for (auto & r : ranges)
            std::cout << r->start.get() << "\t" << r->end.get() << std::endl;


        nest_ranges(ranges, cdef_node, nucleotides);
//        std::cout << "Leaving " << cdef_node->identity.get() << std::endl;

    }

    ranges.clear();
    for (auto & ann : cdef_node->sequenceAnnotations)
    {
        Range& r = ann.locations. template get<Range>();
        r.parent = &ann;  // This is a kludge.  For some reason the parent is not properly set, perhaps when copying the parent ComponentDefinition
        ranges.push_back(&r);
    }
    
//    std::cout << "Sorting " << to_string(ranges.size()) << " ranges" << std::endl;
    sort(ranges.begin(), ranges.end(), compare_ranges);

    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

//    std::cout << "Checking for initial gap starting from " << start_reference << std::endl;
    // Fill gap if first Range does not begin at the Sequence start
    Range& r_first = **ranges.begin();
    if (r_first.start.get() > start_reference)
    {
        int r_new_start = start_reference;
        int r_new_end = r_first.start.get() - 1;
        int l = r_new_end - r_new_start + 1;
        string flanking_seq = nucleotides.substr(r_new_start - 1, l);
//        std::cout << "Adding initial Range from " << r_new_start << " to " << r_new_end << std::endl;

        // Generate URI of new SequenceAnnotation.  Check if an object with that URI is already instantiated.
        int instance_count = 1;
        string annotation_id = cdef_node->persistentIdentity.get() + "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
        while (cdef_node->doc->find_property_value(SBOL_DISPLAY_ID, "annotation" + to_string(instance_count)).size() > 0)
        {
            // Find the last instance assigned
            ++instance_count;
            annotation_id = cdef_node->persistentIdentity.get() +  "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
        }
        SequenceAnnotation& new_ann = cdef_node->sequenceAnnotations.create("annotation" + to_string(instance_count));
        new_ann.roles.set(SO "0000239");  // Set to Sequence Ontology "flanking_sequence"
        new_ann.name.set("flanking region " + to_string(instance_count));

        Range& new_range = new_ann.locations.create<Range>("range" + to_string(instance_count));
        new_range.start.set(r_new_start);
        new_range.end.set(r_new_end);
        
        // Append in order in the list of Ranges
        ranges.insert(ranges.begin(), &new_range);
    }
    
    // Check if Ranges are ordered
    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

    // Fill in gaps with flanking SequenceAnnotations / Ranges
//    std::cout << "Filling gaps with flanking sequences" << std::endl;

    std::vector < sbol::Range* > gapped_ranges = ranges;
    ranges.clear();
    for (auto i_r = gapped_ranges.begin(); i_r != std::prev(gapped_ranges.end()); ++i_r)
    {
//        std::cout << "Iterating through Ranges" << std::endl;
        Range& r_a = **i_r;
        Range& r_b = **(std::next(i_r));
        ranges.push_back(&r_a);
        
        if (!r_a.adjoins(r_b))
        {
//            std::cout << "Calculating gap" << std::endl;
            int r_new_start = r_a.end.get() + 1;
            int r_new_end = r_b.start.get() - 1;
            int l = r_new_end - r_new_start + 1;
            string flanking_seq = nucleotides.substr(r_new_start - start_reference - 1, l);
//            std::cout << "Start: " << r_new_start << std::endl;
//            std::cout << "End: " << r_new_end << std::endl;
//
//            std::cout << "Autoconstructing SequenceAnnotation" << std::endl;

            // Generate URI of new SequenceAnnotation.  Check if an object with that URI is already instantiated.
            int instance_count = 1;
            string annotation_id = cdef_node->persistentIdentity.get() + "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
            while (cdef_node->doc->find_property_value(SBOL_DISPLAY_ID, "annotation" + to_string(instance_count)).size() > 0)
            {
                // Find the last instance assigned
                ++instance_count;
                annotation_id = cdef_node->persistentIdentity.get() +  "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
            }
            SequenceAnnotation& new_ann = cdef_node->sequenceAnnotations.create("annotation" + to_string(instance_count));
            new_ann.roles.set(SO "0000239");  // Set to Sequence Ontology "flanking_sequence"
            new_ann.name.set("flanking region " + to_string(instance_count));

//            std::cout << "Autoconstructing Range" << std::endl;

            Range& new_range = new_ann.locations.create<Range>("range" + to_string(instance_count));
            new_range.start.set(r_new_start);
            new_range.end.set(r_new_end);
            
            // Append in order in the list of Ranges
//            std::cout << "Inserting new range " << std::endl;
            ranges.push_back(&new_range);

        }
    }
    ranges.push_back(gapped_ranges[gapped_ranges.size() - 1]); // Terminal range

    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

//    std::cout << "Checking if the Range interval exceeds primary sequence length" << std::endl;

    // Trim Range if Range's interval exceeds the primary sequence length
    Range& r_last = **std::prev(ranges.end());
    if (r_last.end.get() > (seq.length() + start_reference))
    {
//        std::cout << "Trimming end" << std::endl;

        r_last.end.set(seq.length() + start_reference);
    }
    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

    
//    std::cout << "Checking for end gap" << std::endl;

    // Another edge case: Check for a gap in SequenceAnnotations / Ranges at the very end
    if (r_last.end.get() < seq.length())
    {
        std::cout << "Filling end" << std::endl;

        int r_new_start = r_last.end.get() + 1;  // Shift index by one to convert to zero-indexing
        int r_new_end = r_last.end.get() + seq.length();
        int l = r_new_end - r_new_start + 1;
        string flanking_seq = nucleotides.substr(r_new_start - 1, l);
        
        // Insert flanking Component
        int instance_count = 1;
        string component_id = cdef_node->persistentIdentity.get() + "/component" + to_string(instance_count) + "/" + cdef_node->version.get();
        
        // Generate URI of new Component.  Check if an object with that URI is already instantiated.
        instance_count = 1;
        string annotation_id = cdef_node->persistentIdentity.get() + "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
        while (cdef_node->doc->find_property_value(SBOL_DISPLAY_ID, "annotation" + to_string(instance_count)).size() > 0)
        {
            // Find the last instance assigned
            ++instance_count;
            annotation_id = cdef_node->persistentIdentity.get() +  "/annotation" + to_string(instance_count) + "/" + cdef_node->version.get();
        }
        SequenceAnnotation& new_ann = cdef_node->sequenceAnnotations.create("annotation" + to_string(instance_count));
        new_ann.roles.set(SO "0000239");  // Set to Sequence Ontology "flanking_sequence"
        new_ann.name.set("flanking region " + to_string(instance_count));
        
        Range& new_range = new_ann.locations.create<Range>("range" + to_string(instance_count));
        new_range.start.set(r_new_start);
        new_range.end.set(r_new_end);
        
        // Append to end of list of Ranges
        ranges.insert(ranges.end(), &new_range);
    }
    
    // Check if Ranges are ordered
    for (auto & r : ranges)
        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;

//    std::cout << "Dissembling " << cdef_node->identity.get() << std::endl;

    // Now that Ranges are regularized, instantiate Components and  the Sequence
    std::vector < ComponentDefinition* > primary_structure;
    std::vector < Component* > primary_structure_instances;
    for (auto & i_r : ranges)
    {
        Range& r = *i_r;
        SequenceAnnotation& ann = *(SequenceAnnotation*)r.parent;
        
//        std::cout << r.start.get() << "\t" << r.end.get() << std::endl;

        // If no corresponding Component for this SequenceAnnotation is defined
        if (ann.component.size() == 0)
        {
            std::string display_id = ann.displayId.get();
            size_t index = display_id.find("annotation");
            if (index != std::string::npos)
            {
                display_id.replace(index, 10, "component");
            }
            
//            std::cout << "Instantiating Sequence " << display_id << std::endl;
            Sequence& subseq = cdef_node->doc->sequences.create(display_id + "seq");
            subseq.elements.set(nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1));
//            std::cout << "Setting sequence " << nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1) << std::endl;

//            std::cout << "Instantiating ComponentDefinition " << display_id << std::endl;
            ComponentDefinition& cd = cdef_node->doc->componentDefinitions.create(display_id);
            cd.name.set(ann.name.get());
            cd.sequences.set(subseq);
            cd.roles.copy(ann.roles);
            ann.roles.clear();
            
            Component& c = cdef_node->components.create(display_id);
            c.definition.set(cd);
            c.name.set(ann.name.get());
            
            ann.component.set(c.identity.get());
            
            primary_structure.push_back(&cd);
            primary_structure_instances.push_back(&c);
        }
        else
        {
            Component& c = cdef_node->components.get(ann.component.get());
//            std::cout << "Component " << c.identity.get() << " already instantiated. Retrieving from document" << std::endl;

            ComponentDefinition& sub_cdef = cdef_node->doc->get<ComponentDefinition>(c.definition.get());
            Sequence& subseq = cdef_node->doc->get<Sequence>(sub_cdef.sequences.get());
            subseq.elements.set(nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1));
//            std::cout << "Setting sequence " << nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1) << std::endl;

            primary_structure.push_back(&sub_cdef);
            primary_structure_instances.push_back(&c);
            
            // Recurse into subcomponent, shift primary sequence start reference
            int start_reference = i_r->start.get();
            disassemble(&sub_cdef, start_reference);

        }
    }

//    // Check if Ranges are ordered
//    for (auto & r : ranges)
//    {
//        std::cout << r->start.get() << "\t" << r->end.get() << std::endl;
//    }
//
//    for (auto & c : primary_structure)
//    {
//        std::cout << c->displayId.get() <<  std::endl;
//    }
    
    // Set sequenceConstraints in primary sequence
    for (auto i_com = 1; i_com != primary_structure.size(); i_com++)
    {
        ComponentDefinition& cd_upstream = *primary_structure[i_com - 1];
        ComponentDefinition& cd_downstream = *primary_structure[i_com];
        
        Component& constraint_subject = *primary_structure_instances[i_com - 1];
        Component& constraint_object = *primary_structure_instances[i_com];
        
        SequenceConstraint& sc = cdef_node->sequenceConstraints.create("constraint" + to_string(i_com));
        sc.subject.set(constraint_subject.identity.get());
        sc.object.set(constraint_object.identity.get());
        sc.restriction.set(SBOL_RESTRICTION_PRECEDES);
    }
};

ComponentDefinition& SequenceAnnotation::extract(int start_reference)
{
    SequenceAnnotation& ann = *this;
//    std::cout << "Getting range" << std::endl;
    Range& r = ann.locations.get<Range>();
//    std::cout << "Getting parent CDef" << std::endl;
    SBOLObject* parent_cdef;
    for (auto & cdef : doc->componentDefinitions)
        for (auto & ann : cdef.sequenceAnnotations)
            if (!ann.identity.get().compare(identity.get()))
                parent_cdef = &cdef;
    
    ComponentDefinition* cdef_node = (ComponentDefinition*)parent_cdef;
//    std::cout << "Got " << cdef_node->identity.get() << std::endl;

//    std::cout << "Getting Sequence " << cdef_node->sequences.get() << std::endl;

    Sequence& seq = doc->get<Sequence>(cdef_node->sequences.get());
    string nucleotides = seq.elements.get();
    
//    std::cout << cdef_node->identity.get() << std::endl;
//    std::cout << r.start.get() << "\t" << r.end.get() << std::endl;
    
    // If no corresponding Component for this SequenceAnnotation is defined
    if (ann.component.size() == 0)
    {
        std::string display_id = ann.displayId.get();
        size_t index = display_id.find("annotation");
        if (index != std::string::npos)
        {
            display_id.replace(index, 10, "component");
        }

        //            std::cout << "Instantiating Sequence " << display_id << std::endl;
        Sequence& subseq = cdef_node->doc->sequences.create(display_id + "_sequence");
        subseq.elements.set(nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1));
//        std::cout << "Setting sequence " << nucleotides.substr(r.start.get() - start_reference, r.end.get() - r.start.get() + 1) << std::endl;
        
        //            std::cout << "Instantiating ComponentDefinition " << display_id << std::endl;
    
        string cd_display_id = ann.name.get();
        replace_if(cd_display_id.begin(), cd_display_id.end(), is_not_alphanumeric_or_underscore, '_');
//        std::cout << "New name : " << cd_display_id << std::endl;
        ComponentDefinition& cd = cdef_node->doc->componentDefinitions.create(cd_display_id);
        cd.name.set(ann.name.get());
        cd.sequences.set(subseq);
        cd.roles.copy(ann.roles);
        ann.roles.clear();
        
        Component& c = cdef_node->components.create(display_id);
        c.definition.set(cd);
        c.name.set(ann.name.get());
        
        ann.component.set(c.identity.get());
        
        return cd;
    }
    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "A Component for SequenceAnnotation " + ann.identity.get() + " has already been extracted");
}

void ComponentDefinition::disassemble(int range_start)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "SBOL-compliant URIs must be enabled to use this method");

    if (doc == NULL)
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot disassemble. ComponentDefinition " + identity.get() + " does not belong to a Document.");
    
    if (!isComplete())
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot disassemble. The design is incomplete, meaning some ComponentDefinitions or their Sequences are missing from the Document.");
    
    ::disassemble(this,  range_start);
    return;
};

void ComponentDefinition::linearize(std::vector<ComponentDefinition*> primary_structure)
{
    if (!components.size() && !types.find(SO_LINEAR))
    {
        types.add(SO_LINEAR);
        return;
    }
    if (components.size() != primary_structure.size())
    {
        // throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid primary structure provided. This ComponentDefinition must contain a number of Components corresponding to the length of the primary structure");
    }
    if (sequenceConstraints.size())
    {
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot linearize a ComponentDefinition that already has SequenceConstraints.");
    }
    for (auto & cd : primary_structure)
    {
        if (cd->doc != doc)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid Document specified for " + cd->identity.get() + ". All ComponentDefinitions passed as arguments must belong to the same Document as the parent ComponentDefinition.");
    }
    std::unordered_map<std::string, std::queue<Component*>> component_map;
    for (auto & c : components)
    {
        component_map[c.definition.get()].push(&c);
    }
    std::vector<Component*> primary_structure_components;
    for (auto & cd : primary_structure)
    {
        if (!component_map.count(cd->identity.get()))
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid primary structure provided. " + cd->identity.get() + " does not correspond with any of this object's Components");
        if (!component_map[cd->identity.get()].size())
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid primary structure provided. A Component with definition " + cd->identity.get() + " is missing from the parent ComponentDefinition");
        Component* mapped_component = component_map[cd->identity.get()].front();
        primary_structure_components.push_back(mapped_component);
        component_map[cd->identity.get()].pop();
    }

    for (auto i_com = 1; i_com != primary_structure_components.size(); i_com++)
    {
        ComponentDefinition& cd_upstream = *primary_structure[i_com - 1];
        ComponentDefinition& cd_downstream = *primary_structure[i_com];
        
        Component& constraint_subject = *primary_structure_components[i_com - 1];
        Component& constraint_object = *primary_structure_components[i_com];
        
        SequenceConstraint& sc = sequenceConstraints.create("constraint" + to_string(i_com));
        sc.subject.set(constraint_subject.identity.get());
        sc.object.set(constraint_object.identity.get());
        sc.restriction.set(SBOL_RESTRICTION_PRECEDES);
    }
};

void ComponentDefinition::linearize(vector<string> primary_structure)
{
    if (Config::getOption("sbol_compliant_uris").compare("False") == 0)
        throw SBOLError(SBOL_ERROR_COMPLIANCE, "ComponentDefinition::linearize methods require SBOL-compliance enabled");
    if (doc == NULL)
    {
        throw SBOLError(SBOL_ERROR_MISSING_DOCUMENT, "Cannot perform assembly operation on ComponentDefinition because it does not belong to a Document. You may pass a Document as an optional second argument to this method. Otherwise add this ComponentDefinition to a Document");
    }
    ComponentDefinition& parent_component = *this;
    std::vector<ComponentDefinition*> list_of_components;
    for (auto & uri : primary_structure)
    {
        ComponentDefinition& cdef = doc->componentDefinitions.get(uri);
        list_of_components.push_back(&cdef);
    }
    linearize(list_of_components);
};

void ModuleDefinition::override(FunctionalComponent& highlevel, FunctionalComponent& lowlevel)
{
    highlevel.mask(lowlevel);
};

void FunctionalComponent::override(FunctionalComponent& masked_component)
{
    this->mask(masked_component);

};
