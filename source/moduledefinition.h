/**
 * @file    moduledefinition.h
 * @brief   ModuleDefinition class
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

#ifndef MODULE_DEFINITION_INCLUDED
#define MODULE_DEFINITION_INCLUDED

#include "toplevel.h"
#include "module.h"
#include "component.h"
#include "interaction.h"

#include <string>

namespace sbol
{
    // Forward declaration of Model necessary for template instantiation of ModuleDefinition.models;
    class Model;
    
    /// The ModuleDefinition class represents a grouping of structural and functional entities in a biological design. The primary usage of this class is to assert the molecular interactions and abstract function of its child entities.
    class SBOL_DECLSPEC ModuleDefinition : public TopLevel
	{

	public:
        /// Construct a ModuleDefinition
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a valid [Maven version string](http://maven.apache.org/).
        ModuleDefinition(std::string uri = "example", std::string version = VERSION_STRING) : ModuleDefinition(SBOL_MODULE_DEFINITION, uri, version) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        ModuleDefinition(rdf_type sbol_type_uri, std::string uri, std::string version) :
            TopLevel(sbol_type_uri, uri, version),
            roles(this, SBOL_ROLES, '0', '*', ValidationRules({})),
            models(this, SBOL_MODELS, SBOL_MODEL, '0', '*', ValidationRules({})),
            functionalComponents(this, SBOL_FUNCTIONAL_COMPONENTS, '0', '*', ValidationRules({})),
            modules(this, SBOL_MODULES, '0', '*', ValidationRules({})),
            interactions(this, SBOL_INTERACTIONS, '0', '*', { libsbol_rule_17 })
            {
            };
        
        /// The roles property is an OPTIONAL set of URIs that clarifies the intended function of a ModuleDefinition. These URIs might identify descriptive biological roles, such as “metabolic pathway” and “signaling cascade,” but they can also identify identify “logical” roles, such as “inverter” or “AND gate”, or other abstract roles for describing the function of design. Interpretation of the meaning of such roles currently depends on the software tools that read and write them.
		URIProperty roles;
        
        /// The modules property is OPTIONAL and MAY specify a set of Module objects contained by the ModuleDefinition. While the ModuleDefinition class is analogous to a specification sheet for a system of interacting biological elements, the Module class represents the occurrence of a particular subsystem within the system. Hence, this class allows a system design to include multiple instances of a subsystem, all defined by reference to the same ModuleDefinition. For example, consider the ModuleDefinition for a network of two-input repressor devices in which the particular repressors have not been chosen yet. This ModuleDefinition could contain multiple Module objects that refer to the same ModuleDefinition of an abstract two-input repressor device. Note that the set of relations between Module and ModuleDefinition objects is strictly acyclic.
		OwnedObject<Module> modules;
        
        /// The interactions property is OPTIONAL and MAY specify a set of Interaction objects within the ModuleDefinition.  The Interaction class provides an abstract, machine-readable representation of entity behavior within a ModuleDefinition. Each Interaction contains Participation objects that indicate the roles of the FunctionalComponent objects involved in the Interaction.
        OwnedObject<Interaction> interactions;
        
        /// The functionalComponents property is OPTIONAL and MAY specify a set of FunctionalComponent objects contained by the ModuleDefinition. Just as a Module represents an instance of a subsystem in the overall system represented by a ModuleDefinition, a FunctionalComponent represents an instance of a structural entity (represented by a ComponentDefinition) in the system. This concept allows a ModuleDefinition to assert different interactions for separate copies of the same structural entity if needed. For example, a ModuleDefinition might contain multiple FunctionalComponent objects that refer to the same promoter ComponentDefinition, but assert different interactions for these promoter copies based on their separate positions in another ComponentDefinition that represents the structure of the entire system.
		OwnedObject<FunctionalComponent> functionalComponents;
        
        /// The models property is OPTIONAL and MAY specify a set of URI references to Model objects. Model objects are placeholders that link ModuleDefinition objects to computational models of any format. A ModuleDefinition object can link to more than one Model since each might encode system behavior in a different way or at a different level of detail.
        ReferencedObject models;
        
        /// Defines an output for a sub-Module. Useful for top-down assembly of Modules and sub-Modules. If a FunctionalComponent with the given definition does not exist yet, one will be autoconstructed. Otherwise the FunctionalComponent with the given definition will be inferred. Be warned that this inference may fail if there is more than one FunctionalComponent with the same definition.
        /// @param output A ComponentDefinition that defines the output
        /// @return A FunctionalComponent that is derived from the argument ComponentDefinition and configured as this ModuleDefinition's output (it's direction property is set to SBOL_DIRECTION_OUT)
        FunctionalComponent& setOutput(ComponentDefinition& output);

        /// Defines an input for a sub-Module. Useful for top-down assembly of Modules and sub-Modules. If a FunctionalComponent with the given definition does not exist yet, one will be autoconstructed. Otherwise the FunctionalComponent with the given definition will be inferred. Be warned that this inference may fail if there is more than one FunctionalComponent with the same definition.
        /// @param input A ComponentDefinition that defines the input
        /// @return A FunctionalComponent that is derived from the argument ComponentDefinition and configured as this ModuleDefinition's input (it's direction property is set to SBOL_DIRECTION_IN)
        FunctionalComponent& setInput(ComponentDefinition& input);

        /// Configures a FunctionalComponent as an output for a Module. Useful for bottom-up assembly of Modules and sub-Modules.
        /// @param output The FunctionalComponent that will be configured
        void setOutput(FunctionalComponent& output);
        
        /// Configures a FunctionalComponent as an input for a Module. Useful for bottom-up assembly of Modules and sub-Modules
        /// @param input The FunctionalComponent that will be configured
        void setInput(FunctionalComponent& input);

        /// Connects the output of a sub-Module with the input of another sub-Module. Auto-constructs MapsTo objects.
        /// @param output A FunctionalComponent configured as a Module output (see setOutput)
        /// @param input A FunctionalComponent configured as a Module input (see setInput)
        void connect(FunctionalComponent& output, FunctionalComponent& input);
        
        /// Overrides a low-level component in an abstract sub-Module with a high-level component in a parent ModuleDefinition, for example when overriding an abstract template Module with explicit components.
        /// @param highlevel A high-level FunctionalComponent
        /// @param lowlevel A low-level FunctionalComponent in a nested sub-Module
        void override(FunctionalComponent& highlevel, FunctionalComponent& lowlevel);
        
        /// Perform an operation on every ModuleDefinition in a structurally-linked hierarchy of ModuleDefinitions by applying a callback function. If no callback is specified, the default behavior is to return a pointer list of each ModuleDefinition in the hierarchy.
        /// @param callback_fun A pointer to a callback function with signature void callback_fn(ModuleDefinition *, void *).
        /// @param user_data Arbitrary user data which can be passed in and out of the callback as an argument or return value.
        /// @return Returns a flat list of pointers to all ModuleDefinitions in the hierarchy.
        std::vector<ModuleDefinition*> applyToModuleHierarchy(void (*callback_fn)(ModuleDefinition *, void *) = NULL, void * user_data = NULL);
        
        virtual ~ModuleDefinition() {};

        /// Assemble a high-level ModuleDefinition from lower-level submodules. Autoconstructs Module objects in the process.
        /// @param list_of_modules A list of pointers to the submodule ModuleDefinitions
        void assemble(std::vector < ModuleDefinition* > list_of_modules);
	};
}

#endif
