/**
 * @file    component.h
 * @brief   ComponentInstance, Component, and FunctionalComponent classes
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

#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "identified.h"
#include "mapsto.h"
#include "location.h"
#include "measurement.h"

#include <string>

namespace sbol
{
    // Forward declaration necessary for ComponentInstance.definition
    class ComponentDefinition;
    
    class SBOL_DECLSPEC ComponentInstance : public Identified
	{

	public:

        
        /// The definition property is a REQUIRED URI that refers to the ComponentDefinition of the ComponentInstance. As described in the previous section, this ComponentDefinition effectively provides information about the types and roles of the ComponentInstance.
        /// The definition property MUST NOT refer to the same ComponentDefinition as the one that contains the ComponentInstance. Furthermore, ComponentInstance objects MUST NOT form a cyclical chain of references via their definition properties and the ComponentDefinition objects that contain them. For example, consider the ComponentInstance objects A and B and the ComponentDefinition objects X and Y . The reference chain “X contains A, A isdefinedby Y, Y contains B, and B isdefinedby X” iscyclical.
        ReferencedObject definition;
        
        /// The access property is a REQUIRED URI that indicates whether the ComponentInstance can be referred to remotely by a MapsTo. The value of the access property MUST be one of the following URIs.
        /// | Access URI                  | Description                                                        |
        /// | :---------------------------| :----------------------------------------------------------------- |
        /// | http://sbols.org/v2#public  | The ComponentInstance MAY be referred to by remote MapsTo objects  |
        /// | http://sbols.org/v2#private | The ComponentInstance MAY be referred to by remote MapsTo objects  |
		URIProperty access;
        
        /// The mapsTos property is OPTIONAL and MAY contain a set of MapsTo objects that refer to and link together ComponentInstance objects (both Component objects and FunctionalComponent objects) within a larger design.
		OwnedObject<MapsTo> mapsTos;

        /// The measurements property links a ComponentInstance to parameters or measurements and their associated units. For example a Measurement attached to a FunctionalComponent might indicate the quantity of a component ingredient in a growth medium recipe.
        OwnedObject<Measurement> measurements;
        
        virtual ~ComponentInstance() {};
	protected:
        ComponentInstance(rdf_type type, std::string uri, std::string definition, std::string access, std::string version) :
            Identified(type, uri, version),
            definition(this, SBOL_DEFINITION, SBOL_COMPONENT_DEFINITION, '1', '1', ValidationRules({}), definition),
            access(this, SBOL_ACCESS, '0', '1', ValidationRules({}), access),
            mapsTos(this, SBOL_MAPS_TOS, '0', '*', ValidationRules({})),
            measurements(this, SBOL_MEASUREMENTS, '0', '*', ValidationRules({}))
            {
            };
        
	};

    
    /// The Component class is used to compose ComponentDefinition objects into a structural hierarchy. For example, the ComponentDefinition of a gene could contain four Component objects: a promoter, RBS, CDS, and terminator. In turn, the ComponentDefinition of the promoter Component could contain Component objects defined as various operator sites.
	class SBOL_DECLSPEC Component : public ComponentInstance
	{
	public:
        /// The expected purpose and function of a genetic part are described by the roles property of ComponentDefinition. However, the same building block might be used for a different purpose in an actual design. In other words, purpose and function are sometimes determined by context.
        /// The roles property comprises an OPTIONAL set of zero or more role URIs describing the purpose or potential function of this Component’s included sub-ComponentDefinition in the context of its parent ComponentDefinition. If provided, these role URIs MUST identify terms from appropriate ontologies. Roles are not restricted to describing biological function; they may annotate a Component’s function in any domain for which an ontology exists.
        /// It is RECOMMENDED that these role URIs identify terms that are compatible with the type properties of both this Component’s parent ComponentDefinition and its included sub-ComponentDefinition. For example, a role of a Component which belongs to a ComponentDefinition of type DNA and includes a sub-ComponentDefinition of type DNA might refer to terms from the Sequence Ontology. See documentation for ComponentDefinition for a table of recommended ontology terms for roles.
        URIProperty roles;
        
        /// A roleIntegration specifies the relationship between a Component instance’s own set of roles and the set of roles on the included sub-ComponentDefinition.
        /// The roleIntegration property has a data type of URI. A Component instance with zero roles MAY OPTIONALLY specify a roleIntegration. A Component instance with one or more roles MUST specify a roleIntegration from the table below If zero Component roles are given and no Component roleIntegration is given, then http://sbols.org/v2#mergeRoles is assumed. It is RECOMMENDED to specify a set of Component roles only if the integrated result set of roles would differ from the set of roles belonging to this Component’s included sub-ComponentDefinition.
        /// | roleIntegration URI                | Description                                                                                        |
        /// | :----------------------------------| :------------------------------------------------------------------------------------------------- |
        /// | http://sbols.org/v2#overrideRoles  | In the context of this Component, ignore any roles given for the included sub-ComponentDefinition. |
        /// |                                    | Instead use only the set of zero or more roles given for this Component.                           |
        /// | http://sbols.org/v2#mergeRoles     | Use the union of the two sets: both the set of zero or more roles given for this Component as well |
        /// |                                    | as the set of zero or more roles given for the included sub-ComponentDefinition.                   |
        URIProperty roleIntegration;

        /// The sourceLocations property allows only a portion of the Component's sequence to be used when compiling a composite Sequence from a component hierarchy. This serves two related purposes: (1) To support the insertion of parts within a larger plasmid or genome "backbone". Typically, this will replace a small segment of the backbone which, currently, cannot be expressed in SBOL. (2) To support the "trimming" of part boundaries as it may happen during DNA assembly.
        OwnedObject<Location> sourceLocations;
        
        
        /// Construct a Component. If operating in SBOL-compliant mode, use ComponentDefinition::components::create instead.
        /// @param A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param definition A URI referring to the ComponentDefinition that defines this instance
        /// @param access Flag indicating whether the Component can be referred to remotely by a MapsTo
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Component(std::string uri = "example", std::string definition = "", std::string access = SBOL_ACCESS_PUBLIC, std::string version = VERSION_STRING) :
            Component(SBOL_COMPONENT, uri, definition, access, version) {};
        
//        Component(std::string uri_prefix, std::string display_id, std::string version, std::string definition,std::string access) : Component(SBOL_COMPONENT, uri_prefix, display_id, version, definition, access) {};

        virtual ~Component() {};

	protected:
        Component(rdf_type type, std::string uri, std::string definition, std::string access, std::string version) :
            ComponentInstance(type, uri, definition, access, version),
            roles(this, SBOL_ROLES, '0', '*', ValidationRules({})),
            roleIntegration(this, SBOL_ROLE_INTEGRATION, '0', '1', ValidationRules({}), SBOL_ROLE_INTEGRATION_MERGE),
            sourceLocations(this, SBOL_LOCATIONS, '0', '*', ValidationRules({}))
            {};
        
//        Component(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) : ComponentInstance(type, uri_prefix, display_id, version, definition, access) {};
	};
 
    /// The FunctionalComponent class is used to specify the functional usage of a ComponentDefinition inside a ModuleDefinition. The ModuleDefinition describes how the that describes how the FunctionalComponent interacts with others and summarizes their aggregate function.
	class SBOL_DECLSPEC FunctionalComponent : public ComponentInstance
	{
	public:
        /// Each FunctionalComponent MUST specify via the direction property whether it serves as an input, output, both, or neither for its parent ModuleDefinition object. The value for this property MUST be one of the URIs given in the table below.
        /// | Direction URI             | Description                                                           | LibSBOL Symbol        |
        /// | :------------------------ | :-------------------------------------------------------------------- | :-------------------- |
        /// | http://sbols.org/v2#in    | Indicates that the FunctionalComponent is an input.                   | SBOL_DIRECTION_IN     |
        /// | http://sbols.org/v2#out   | Indicates that the FunctionalComponent is an output.                  | SBOL_DIRECTION_OUT    |
        /// | http://sbols.org/v2#inout | Indicates that the FunctionalComponent is both an input and output    | SBOL_DIRECTION_IN_OUT |
        /// | http://sbols.org/v2#none  | Indicates that the FunctionalComponent is neither an input or output. | SBOL_DIRECTION_NONE   |
        URIProperty direction;

        /// Construct a FunctionalComponent. If operating in SBOL-compliant mode, use ModuleDefinition::functionalComponents::create instead.
        /// @param A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param definition A URI referring to the ComponentDefinition that defines this instance
        /// @param access Flag indicating whether the FunctionalComponent can be referred to remotely by a MapsTo
        /// @param direction The direction property specifies whether a FunctionalComponent serves as an input, output, both, or neither for its parent ModuleDefinition object
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        FunctionalComponent(std::string uri = "example", std::string definition = "", std::string access = SBOL_ACCESS_PUBLIC, std::string direction = SBOL_DIRECTION_NONE, std::string version = VERSION_STRING) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri, definition, access, direction, version) {};
        
//        FunctionalComponent(std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access, std::string direction) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri_prefix, display_id, version, definition, access, direction) {};
        
        /// This method connects module inputs and outputs. This convenience method auto-constructs a MapsTo object. See @ref modular_design for an example
        /// @param interface_component An input or output component from another ModuleDefinition that corresponds with this component.
        void connect(FunctionalComponent& interface_component);
        
        /// This method is used to state that FunctionalComponents in separate ModuleDefinitions are functionally equivalent. Using this method will override the  FunctionalComponent in the argument with the FunctionalComponent calling the method.  This is useful for overriding a generic, template component with an explicitly defined component. This convenience method auto-constructs a MapsTo object. See @ref modular_design for an example
        /// @param masked_component The FunctionalComponent that is being masked (over-ridden)
        void mask(FunctionalComponent& masked_component);

        /// This method is used to state that FunctionalComponents in separate ModuleDefinitions are functionally equivalent. Using this method will override the  FunctionalComponent in the argument with the FunctionalComponent calling the method.  This is useful for overriding a generic, template component with an explicitly defined component. This convenience method auto-constructs a MapsTo object. See @ref modular_design for an example
        /// @param masked_component The FunctionalComponent that is being masked (over-ridden)
        void override(FunctionalComponent& masked_component);

        /// Used to tell if a FunctionalComponent is linked to an equivalent FunctionalComponent in another ModuleDefinition
        /// @return 1 if the FunctionalComponent has been over-rided by another FunctionalComponent, 0 if it hasn't.
        int isMasked();
        virtual ~FunctionalComponent() {};

	protected:
        FunctionalComponent(rdf_type type, std::string uri, std::string definition, std::string access, std::string direction, std::string version) :
            ComponentInstance(type, uri, definition, access, version),
            direction(this, SBOL_DIRECTION, '1', '1', ValidationRules({}), direction)
            {
            };

	};
}

#endif
