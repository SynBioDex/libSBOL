#ifndef MAPS_TO_INCLUDED
#define MAPS_TO_INCLUDED

#include "identified.h"

namespace sbol
{
    class ComponentInstance;  // Forward declaration necessary for ReferencedObject templates
    
    ///  The purpose of the MapsTo class is to make identity relationships between different ComponentInstances in functional and structural hierarchies more clear. For example, a MapsTo object may be used to connect outputs and inputs between different low-level ModuleDefinitions contained in a higher level Module Definition. A MapsTo object may also be used to override a generic Component in a low-level ModuleDefinition with an explicit Component in a high-level ModuleDefinition, for example mapping a generic gene to an explicit component with a name and sequence.
    class MapsTo : public Identified
	{
	public:
        /// Each MapsTo object MUST specify the relationship between its local and remote ComponentInstance objects using one of the REQUIRED refinement URIs provided in the table below.
        /// | Refinement URI                       | Description                                                              |
        /// | :----------------------------------- | :----------------------------------------------------------------------- |
        /// | http://sbols.org/v2#useRemote        | All references to the local ComponentInstance MUST dereference to the<br>remote ComponentInstance instead. |
        /// | http://sbols.org/v2#useLocal         | In the context of the ComponentDefinition or ModuleDefinition that contains<br>the owner of the MapsTo, all references to the remote ComponentInstance<br>MUST dereference to the local ComponentInstance instead. |
        /// | http://sbols.org/v2#verifyIdentical  | The definition properties of the local and remoteComponentInstance objects<br>MUST refer to the same ComponentDefinition. |
        /// | http://sbols.org/v2#mergeDescription | In the context of the ComponentDefinition or ModuleDefinition that<br>contains the owner of the MapsTo, all references to the local<br>ComponentInstance or the remote ComponentInstance MUST dereference<br>to both objects.
        URIProperty refinement;
        
        /// The identity of the lower level ComponentInstance
        ReferencedObject local;
        
        /// The identity of the higher level ComponentInstance
        ReferencedObject remote;

        /// Construct a MapsTo. If operating in SBOL-compliant mode, use ModuleDefinition::mapsTos::create instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param local The identity of the lower level ComponentInstance
        /// @param remote The identity of the higher level ComponentInstance
        /// @param restriction Flag indicating the relationship between high- and low-level ComponentInstances. By default, this is set to SBOL_REFINEMENT_VERIFY_IDENTICAL
        MapsTo(std::string uri = DEFAULT_NS "/MapsTo/example", std::string local = "", std::string remote = "", std::string refinement = SBOL_REFINEMENT_VERIFY_IDENTICAL) : MapsTo(SBOL_MAPS_TO, uri, local, remote, refinement) {};
        
        
        virtual ~MapsTo() {};
	protected:
        MapsTo(sbol_type type, std::string uri, std::string local, std::string remote, std::string refinement) :
            Identified(type, uri),
            refinement(SBOL_REFINEMENT, this, refinement),
            local(SBOL_LOCAL, this, local),
            remote(SBOL_REMOTE, this, remote)
            {
            }

	};
}

#endif