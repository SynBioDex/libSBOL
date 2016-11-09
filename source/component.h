#ifndef COMPONENT_INCLUDED
#define COMPONENT_INCLUDED

#include "identified.h"
#include "mapsto.h"

#include <string>

namespace sbol
{
    // Forward declaration necessary for ComponentInstance.definition
    class ComponentDefinition;
    
    class ComponentInstance : public Identified
	{

	public:

        /// The access property is a REQUIRED URI that indicates whether the ComponentInstance can be referred to remotely by a MapsTo. The value of the access property MUST be one of the following URIs.
        /// | Access URI                  | Description                                                        |
        /// | :---------------------------| :----------------------------------------------------------------- |
        /// | http://sbols.org/v2#public  | The ComponentInstance MAY be referred to by remote MapsTo objects  |
        /// | http://sbols.org/v2#private | The ComponentInstance MAY be referred to by remote MapsTo objects  |
		URIProperty access;
		List<OwnedObject<MapsTo>> mapsTos;
        ReferencedObject definition;
        List<URIProperty> roles;
        URIProperty roleIntegration;

        virtual ~ComponentInstance() {};
	protected:
        ComponentInstance(sbol_type type, std::string uri, std::string definition, std::string access, std::string version) :
            Identified(type, uri, version),
            definition(SBOL_DEFINITION, SBOL_COMPONENT_DEFINITION, this, definition),
            access(SBOL_ACCESS, this, access),
            mapsTos(SBOL_MAPS_TOS, this),
            roles(SBOL_ROLES, this),
            roleIntegration(SBOL_ROLE_INTEGRATION, this, SBOL_ROLE_INTEGRATION_MERGE)
            {
            };
//        ComponentInstance(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) :
//            Identified(type, uri_prefix, display_id, version),
//            definition(SBOL_DEFINITION, SBOL_COMPONENT_DEFINITION, this, definition),
//            access(SBOL_ACCESS, this, access),
//            mapsTos(SBOL_MAPS_TOS, this)
//            {
//            };
        
	};

    
    /// The Component class is used to compose ComponentDefinition objects into a structural hierarchy. For example, the ComponentDefinition of a gene could contain four Component objects: a promoter, RBS, CDS, and terminator. In turn, the ComponentDefinition of the promoter Component could contain Component objects defined as various operator sites.
	class Component : public ComponentInstance
	{
	public:
        Component(std::string uri = DEFAULT_NS "/Component/example", std::string definition = "", std::string access = SBOL_ACCESS_PUBLIC, std::string version = "1.0.0") :
            Component(SBOL_COMPONENT, uri, definition, access, version) {};
        
//        Component(std::string uri_prefix, std::string display_id, std::string version, std::string definition,std::string access) : Component(SBOL_COMPONENT, uri_prefix, display_id, version, definition, access) {};

        virtual ~Component() {};

	protected:
        Component(sbol_type type, std::string uri, std::string definition, std::string access, std::string version) :
            ComponentInstance(type, uri, definition, access, version) {};
        
//        Component(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access) : ComponentInstance(type, uri_prefix, display_id, version, definition, access) {};
	};
 
    /// The FunctionalComponent class is used to specify the functional usage of a ComponentDefinition inside a ModuleDefinition. The ModuleDefinition describes how the that describes how the FunctionalComponent interacts with others and summarizes their aggregate function.
	class FunctionalComponent : public ComponentInstance
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

        /// Construct a FunctionalComponent
        /// @param A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param definition
        /// @param access
        /// @param direction The direction property specifies whether a FunctionalComponent serves as an input, output, both, or neither for its parent ModuleDefinition object
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        FunctionalComponent(std::string uri = DEFAULT_NS "/FunctionalComponent/example", std::string definition = "", std::string access = SBOL_ACCESS_PUBLIC, std::string direction = SBOL_DIRECTION_NONE, std::string version = "1.0.0") : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri, definition, access, direction, version) {};
        
//        FunctionalComponent(std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access, std::string direction) : FunctionalComponent(SBOL_FUNCTIONAL_COMPONENT, uri_prefix, display_id, version, definition, access, direction) {};
        
        /// This method connects module inputs and outputs.
        /// @param interface_component An input or output component from another ModuleDefinition that corresponds with this component.
        void connect(FunctionalComponent& interface_component);
        void mask(FunctionalComponent& masked_component);
        int isMasked();
        virtual ~FunctionalComponent() {};

	protected:
        FunctionalComponent(sbol_type type, std::string uri, std::string definition, std::string access, std::string direction, std::string version) :
            ComponentInstance(type, uri, definition, access, version),
            direction(SBOL_DIRECTION, this, direction) {};
        
//        FunctionalComponent(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string definition, std::string access, std::string direction) :
//            ComponentInstance(type, uri_prefix, display_id, version, definition, access),
//            direction(SBOL_DIRECTION, this, direction) {};

	};
}

#endif