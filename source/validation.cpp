/**
 * @file    validation.cpp
 * @brief   Validation rules
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

#include "sbol.h"
#include <iostream>

#ifndef SBOL_BUILD_MANYLINUX
#include <regex>
#endif

using namespace sbol;
using namespace std;

bool sbol::is_alphanumeric_or_underscore(char c)
{
    int i = (int)c;
    if (i >= 48 && i <= 57)
        return true;
    if (i >= 65 && i <= 90)
        return true;
    if (i >= 97 && i <= 122)
        return true;
    if (i == 95)
        return true;
    return false;
};

bool sbol::is_not_alphanumeric_or_underscore(char c)
{
    return !is_alphanumeric_or_underscore(c);
};

/* An SBOL document MUST declare the use of the following XML namespace: http://sbols.org/v2#. */
void sbol::sbolRule10101(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(SBOL_URI "#") == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " SBOL_URI "#");
}

/* An SBOL document MUST declare the use of the following XML namespace: http://www.w3.org/1999/02/22-rdf-syntax-ns#.*/
void sbol::sbolRule10102(void *sbol_obj, void *arg)
{
    Document* doc = (Document *)sbol_obj;
    vector<string> namespaces = doc->getNamespaces();
    int FOUND_NS = 0;
    for (vector<string>::iterator i_ns = namespaces.begin(); i_ns != namespaces.end(); ++i_ns)
    {
        string ns = *i_ns;
        if(ns.compare(RDF_URI) == 0) FOUND_NS = 1;
    }
    if (!FOUND_NS) SBOLError(SBOL_ERROR_MISSING_NAMESPACE, "Missing namespace " RDF_URI);
}

/* The identity property of an Identified object MUST be globally unique. */
void sbol::sbol_rule_10202(void *sbol_obj, void *arg)
{
	Identified *identified_obj = (Identified *)sbol_obj;
	string new_id;

	if (arg != NULL)
	{
		new_id = *static_cast<std::string*>(arg);
	}
	if (identified_obj->doc)
	{
		if (identified_obj->doc->SBOLObjects.find(new_id) != identified_obj->doc->SBOLObjects.end())  // If the new identity is already in the document throw an error
		{
			throw SBOLError(SBOL_ERROR_URI_NOT_UNIQUE, "Cannot add " + new_id + " to Document. An object with this URI already exists. See validation rule sbol-10202.");
		}
	}
};

/* The displayId property of an Identified object is OPTIONAL and MAY contain a String that MUST be composed of only alphanumeric or underscore characters and MUST NOT begin with a digit. */
void sbol::sbol_rule_10204(void *sbol_obj, void *arg)
{
    Identified *identified_obj = (Identified *)sbol_obj;
    string display_id;
    
    if (arg != NULL)
    {
        display_id = *static_cast<std::string*>(arg);
        for (auto c : display_id)
            if (is_not_alphanumeric_or_underscore(c))
                throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "DisplayId " + display_id + " is invalid. DisplayIds must contain only alphanumeric or underscore characters. See validation rule sbol-10204.");
        int c = (int)display_id[0];
        if (c >= 48 && c <= 57)
            throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "DisplayId " + display_id + " is invalid. DisplayIds cannot begin with a numeral. See validation rule sbol-10204.");
    }
}

/*	The definition property MUST NOT refer to the same ComponentDefinition as the one that contains the
ComponentInstance.Furthermore, ComponentInstance objects MUST NOT form a cyclical chain of references
via their definition properties and the ComponentDefinition objects that contain them.For example, consider
the ComponentInstance objects A and B and the ComponentDefinition objects X and Y.The reference chain "X
contains A, A is defined by Y, Y contains B, and B is defined by X" is cyclical. */


// Print a test message
void sbol::libsbol_rule_1(void *sbol_obj, void *arg)
{
	cout << "Testing internal validation rules" << endl;
};

// Validate XSD date-time format
void sbol::libsbol_rule_2(void *sbol_obj, void *arg)
{
#ifndef SBOL_BUILD_MANYLINUX
		const char *c_date_time = (const char *)arg;
		string date_time = string(c_date_time);
        if (date_time.compare("") != 0)
        {
            bool DATETIME_MATCH_1 = false;
            bool DATETIME_MATCH_2 = false;
            bool DATETIME_MATCH_3 = false;
            std::regex date_time_1("([0-9]{4})-([0-9]{2})-([0-9]{2})([A-Z])?");
            std::regex date_time_2("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})([.][0-9]+)?[A-Z]?");
            std::regex date_time_3("([0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2}):([0-9]{2})([.][0-9]+)?[A-Z]?([\\+|-]([0-9]{2}):([0-9]{2}))?");
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_1))
                DATETIME_MATCH_1 = true;
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_2))
                DATETIME_MATCH_2 = true;
            if (std::regex_match(date_time.begin(), date_time.end(), date_time_3))
                DATETIME_MATCH_3 = true;
            if (!(DATETIME_MATCH_1 || DATETIME_MATCH_2 || DATETIME_MATCH_3))
                throw SBOLError(SBOL_ERROR_NONCOMPLIANT_VERSION, "Invalid datetime format. Datetimes are based on XML Schema dateTime datatype. For example 2016-03-16T20:12:00Z");
        }
#endif
};

// Validate Design.structure and Design.function are compatible
void sbol::libsbol_rule_3(void *sbol_obj, void *arg)
{

    ComponentDefinition& structure = *static_cast<ComponentDefinition*>(arg);
    Design& design = (Design&)(*structure.parent);

    // Add the structure ComponentDefinition to the Document
    if (design.doc && !structure.doc)
        structure.doc = design.doc;
    else if (design.doc != structure.doc)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot use " + structure.identity.get() + " for this Design. The objects must belong to the same Document");
        
    
    // Update Reference property to match the OwnedObject property (only the Reference will be serialized)
    design.properties["http://sys-bio.org#_structure"][0] = "<" + structure.identity.get() + ">";
    
    if (design.function.size() > 0)
    {
        // Update FunctionalComponent which correlates the structure and function properties
        ModuleDefinition& fx = design.function.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get() == structure.identity.get())
                STRUCTURE_FUNCTION_CORRELATED = true;
                break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
        {
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
            correlation.definition.set(structure);
        }
    }
};

void sbol::libsbol_rule_4(void *sbol_obj, void *arg)
{
    ModuleDefinition& fx = *static_cast<ModuleDefinition*>(arg);
    Design& design = (Design&)(*fx.parent);

    // Add the structure ComponentDefinition to the Document
    if (design.doc && !fx.doc)
        fx.doc = design.doc;
    else if (design.doc != fx.doc)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot use " + fx.identity.get() + " for this Design. The objects must belong to the same Document");
    
    design.properties["http://sys-bio.org#_function"][0] = "<" + fx.identity.get() + ">";
    if (design.structure.size() > 0)
    {
        ComponentDefinition& structure = design.structure.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get() == structure.identity.get())
                STRUCTURE_FUNCTION_CORRELATED = true;
            break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
        {
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
            correlation.definition.set(structure);
        }
    }
};

// Validate Build.structure and Build.behavior are compatible
void sbol::libsbol_rule_5(void *sbol_obj, void *arg)
{

    ComponentDefinition& structure = *static_cast<ComponentDefinition*>(arg);
    Build& build = (Build&)(*structure.parent);

    // Add the structure ComponentDefinition to the Document
    if (build.doc && !structure.doc)
        structure.doc = build.doc;
    else if (build.doc != structure.doc)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot use " + structure.identity.get() + " for this Design. The objects must belong to the same Document");
        
    
    // Update Reference property to match the OwnedObject property (only the Reference will be serialized)
    build.properties["http://sys-bio.org#_structure"][0] = "<" + structure.identity.get() + ">";
    
    if (build.behavior.size() > 0)
    {
        // Update FunctionalComponent which correlates the structure and function properties
        ModuleDefinition& fx = build.behavior.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get() == structure.identity.get())
                STRUCTURE_FUNCTION_CORRELATED = true;
                break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
        {
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
            correlation.definition.set(structure);
        }
    }
};

void sbol::libsbol_rule_6(void *sbol_obj, void *arg)
{
    ModuleDefinition& fx = *static_cast<ModuleDefinition*>(arg);
    Build& build = (Build&)(*fx.parent);

    // Add the structure ComponentDefinition to the Document
    if (build.doc && !fx.doc)
        fx.doc = build.doc;
    else if (build.doc != fx.doc)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot use " + fx.identity.get() + " for this Design. The objects must belong to the same Document");
    
    build.properties[SBOL_URI "#built"][0] = "<" + fx.identity.get() + ">";
    if (build.structure.size() > 0)
    {
        ComponentDefinition& structure = build.structure.get();
        bool STRUCTURE_FUNCTION_CORRELATED = false;
        for (auto & fc : fx.functionalComponents)
        {
            if (fc.definition.get() == structure.identity.get())
                STRUCTURE_FUNCTION_CORRELATED = true;
            break;
        }
        if (!STRUCTURE_FUNCTION_CORRELATED)
        {
            FunctionalComponent& correlation = fx.functionalComponents.create(fx.displayId.get());
            correlation.definition.set(structure);
        }
    }
};

// Validate that the Analysis object referenced in Design.characterization is consistent with #learn Usage
void sbol::libsbol_rule_7(void *sbol_obj, void *arg)
{
    // Design& design = *(Design*)sbol_obj;
    // string& analysis_id = *(string*)arg;
    // if (design.doc && design.wasGeneratedBy.size())
    // {
    //     vector< Usage* > learn_usages;
    //     for (auto & activity : design.doc->activities)
    //         if (activity.identity.get() == design.wasGeneratedBy.get())
    //             for (auto & usage : activity.usages)
    //                 if (usage.roles.find(SBOL_LEARN))
    //                     learn_usages.push_back(&usage);
    //     for (auto & usage : learn_usages)
    //         if (analysis_id == usage->entity.get())
    //             return;
    //     throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "The characterization property of " + design.identity.get() + " must reference the same Analysis as referenced by the Activity that produced it.");    }
};

// Validate that the Design object referenced in Build.design is consistent with #design Usage
void sbol::libsbol_rule_8(void *sbol_obj, void *arg)
{
    // Build& build = *(Build*)sbol_obj;
    // string& design_id = *(string*)arg;
    // if (build.doc  && build.wasGeneratedBy.size())
    // {
    //     vector< Usage* > design_usages;
    //     for (auto & activity : build.doc->activities)
    //         if (activity.identity.get() == build.wasGeneratedBy.get())
    //             for (auto & usage : activity.usages)
    //                 if (usage.roles.find(SBOL_DESIGN))
    //                     design_usages.push_back(&usage);
    //     for (auto & usage : design_usages)
    //         if (design_id == usage->entity.get())
    //             return;
    //     throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "The design property of " + build.identity.get() + " must reference the same Design as referenced by the Activity that produced it.");
    // }
};

// Validate that the Build objects referenced in Test.samples is consistent with #build Usage
void sbol::libsbol_rule_9(void *sbol_obj, void *arg)
{
    // Test& test = *(Test*)sbol_obj;
    // string& sample_id = *(string*)arg;
    // if (test.doc && test.wasGeneratedBy.size())
    // {
    //     vector< Usage* > build_usages;
    //     for (auto & activity : test.doc->activities)
    //         if (activity.identity.get() == test.wasGeneratedBy.get())
    //             for (auto & usage : activity.usages)
    //                 if (usage.roles.find(SBOL_BUILD))
    //                     build_usages.push_back(&usage);
    //     for (auto & usage : build_usages)
    //         if (sample_id == usage->entity.get())
    //             return;
    //     throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "The samples property of " + test.identity.get() + " must reference the same Build objects as referenced by the Activity that produced it.");
    // }
};

// Validate that the Test objects referenced in Analysis.rawData is consistent with #test Usage
void sbol::libsbol_rule_10(void *sbol_obj, void *arg)
{
    // Analysis& analysis = *(Analysis*)sbol_obj;
    // string& test_id = *(string*)arg;
    // if (analysis.doc && analysis.wasGeneratedBy.size())
    // {
    //     vector< Usage* > test_usages;
    //     for (auto & activity : analysis.doc->activities)
    //         if (activity.identity.get() == analysis.wasGeneratedBy.get())
    //             for (auto & usage : activity.usages)
    //                 if (usage.roles.find(SBOL_TEST))
    //                     test_usages.push_back(&usage);
    //     for (auto & usage : test_usages)
    //         if (test_id == usage->entity.get())
    //             return;
    //     throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "The rawData property of " + analysis.identity.get() + " must reference the same Test object as referenced by the Activity that produced it.");
    // }
};

void sbol::libsbol_rule_11(void *sbol_obj, void *arg)
{
    Design& design = *(Design*)arg;
    for (auto analysis : design.characterization)
    {
        libsbol_rule_7(sbol_obj, &analysis);
    }
};

void sbol::libsbol_rule_12(void *sbol_obj, void *arg)
{
    Build& build = *(Build*)arg;
    for (auto design : build.design)
    {
        libsbol_rule_8(sbol_obj, &design);
    }
};

void sbol::libsbol_rule_13(void *sbol_obj, void *arg)
{
    Test& test = *(Test*)arg;
    for (auto build : test.samples)
    {
        libsbol_rule_9(sbol_obj, &build);
    }
};

void sbol::libsbol_rule_14(void *sbol_obj, void *arg)
{
    Analysis& analysis = *(Analysis*)arg;
    for (auto test : analysis.rawData)
    {
        libsbol_rule_10(sbol_obj, &test);
    }
};

void sbol::libsbol_rule_15(void *sbol_obj, void *arg)
{
    SampleRoster& roster = *(SampleRoster*)sbol_obj;
    string sample_id = *(string*)arg;
    if (roster.doc && !roster.doc->builds.find(sample_id))
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Invalid SampleRoster. The referenced Build " + sample_id + " is not contained in the Document");
};

void sbol::libsbol_rule_16(void *sbol_obj, void *arg)
{
    SampleRoster& roster = *(SampleRoster*)arg;
    for (auto sample_id : roster.samples)
        libsbol_rule_15(sbol_obj, &roster);
};

void sbol::libsbol_rule_17(void *sbol_obj, void *arg)
{
    ModuleDefinition& mdef = *(ModuleDefinition*)sbol_obj;
    Interaction& interaction = *(Interaction*)arg;
    for (auto & fc : interaction.functionalComponents)
    {
        libsbol_rule_18(arg, &fc);
    }
};

void sbol::libsbol_rule_18(void *sbol_obj, void *arg)
{
    Interaction& interaction = *(Interaction*)sbol_obj;
    FunctionalComponent& fc = *(FunctionalComponent*)arg;
    if (interaction.parent)
    {
        ModuleDefinition& parent_mdef = *(ModuleDefinition*)interaction.parent;
        // Skip if a copy of this FunctionalComponent is already stored in the parent Interaction
        for (auto & fc_comparand : parent_mdef.functionalComponents)
            if (fc.identity.get() == fc_comparand.identity.get() || fc.displayId.get() == fc_comparand.displayId.get())
            {
                // Update reference to participant FunctionalComponent
                for (auto & p : interaction.participations)
                {
                    if (p.participant.get() == fc.identity.get())
                        p.participant.set(fc_comparand.identity.get());
                }
                return;
            }
        string old_id = fc.identity.get();
        parent_mdef.functionalComponents.add(fc);  // Updates the FC's URI
        // Update reference to participant FunctionalComponent
        for (auto & p : interaction.participations)
        {
            if (p.participant.get() == old_id)
                p.participant.set(fc);
        }
    }
};

void sbol::libsbol_rule_19(void *sbol_obj, void *arg)
{
    throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot modify property value. It is read-only.");
};

void sbol::libsbol_rule_20(void *sbol_obj, void *arg)
{
    ComponentDefinition& cd = *(ComponentDefinition*)sbol_obj;
    Sequence& seq = *(Sequence*)arg;
    vector<string> seq_ids = cd.sequences.getAll();
    if (std::find(seq_ids.begin(), seq_ids.end(), seq.identity.get()) == seq_ids.end())
    {
        cd.sequences.clear();
        cd.sequences.set(seq.identity.get());
    }
};

void sbol::libsbol_rule_21(void *sbol_obj, void *arg)
{
    ComponentDefinition& cd = *(ComponentDefinition*)sbol_obj;
    string& seq_id = *(string*)arg;
    if (cd.sequence.size() && seq_id != cd.sequence.get().identity.get())
    {
        cd.sequence.remove();
        if (cd.doc && cd.sequences.find(seq_id))
        {
            cd.sequence.set(cd.doc->get<Sequence>(seq_id));
        }
    }
};

void sbol::libsbol_rule_22(void *sbol_obj, void *arg)
{
    Activity& activity = *(Activity*)sbol_obj;
    Agent& agent = *(Agent*)arg;

    if (activity.associations.size() > 1)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot add Agent. This Activity already has an Association that specifies an Agent");
    
    if (activity.associations.size() == 1) {
        Association &asc = activity.associations.get();
        asc.agent.set(agent.identity.get());

    } else {
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = activity.displayId.get();
        else
            id = activity.identity.get();
        Association& asc = activity.associations.create(id + "_generation_association");
        asc.agent.set(agent.identity.get());
        if (activity.plan.size())
            asc.plan.set(activity.plan.get().identity.get());
    }
};

void sbol::libsbol_rule_24(void *sbol_obj, void *arg)
{
    Activity& activity = *(Activity*)sbol_obj;
    Plan& plan = *(Plan*)arg;

    if (activity.associations.size() > 1)
        throw SBOLError(SBOL_ERROR_INVALID_ARGUMENT, "Cannot add Plan. This Activity already has an Association that specifies a Plan");
    
    if (activity.associations.size() == 1) {
        Association &asc = activity.associations.get();
        asc.plan.set(plan.identity.get());

    } else {
        std::string id;
        if (Config::getOption("sbol_compliant_uris") == "True")
            id = activity.displayId.get();
        else
            id = activity.identity.get();
        Association& asc = activity.associations.create(id + "_generation_association");
        asc.plan.set(plan.identity.get());
        if (activity.agent.size())
            asc.agent.set(activity.agent.get().identity.get());
    }
};
