/**
 * @file    mapsto.h
 * @brief   MapsTo class
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

#ifndef MAPS_TO_INCLUDED
#define MAPS_TO_INCLUDED

#include "identified.h"

namespace sbol
{
    class ComponentInstance;  // Forward declaration necessary for ReferencedObject templates
    
    ///  The purpose of the MapsTo class is to make identity relationships between different ComponentInstances in functional and structural hierarchies more clear. For example, a MapsTo object may be used to connect outputs and inputs between different low-level ModuleDefinitions contained in a higher level Module Definition. A MapsTo object may also be used to override a generic Component in a low-level ModuleDefinition with an explicit Component in a high-level ModuleDefinition, for example mapping a generic gene to an explicit component with a name and sequence.
    class SBOL_DECLSPEC MapsTo : public Identified
	{
	public:
        /// Each MapsTo object MUST specify the relationship between its local and remote ComponentInstance objects using one of the REQUIRED refinement URIs provided in the table below.
        /// | Refinement URI                       | libSBOL Symbol                    | Description                                                              |
        /// | :----------------------------------- | :-------------------------------- | :----------------------------------------------------------------------- |
        /// | http://sbols.org/v2#useRemote        | SBOL_REFINEMENT_USE_REMOTE        | All references to the local ComponentInstance MUST dereference to the<br>remote ComponentInstance instead. |
        /// | http://sbols.org/v2#useLocal         | SBOL_REFINEMENT_USE_LOCAL         | In the context of the ComponentDefinition or ModuleDefinition that contains<br>the owner of the MapsTo, all references to the remote ComponentInstance<br>MUST dereference to the local ComponentInstance instead. |
        /// | http://sbols.org/v2#verifyIdentical  | SBOL_REFINEMENT_VERIFY_IDENTICAL  | The definition properties of the local and remoteComponentInstance objects<br>MUST refer to the same ComponentDefinition. |
        /// | http://sbols.org/v2#merge | SBOL_REFINEMENT_MERGE_DESCRIPTION | In the context of the ComponentDefinition or ModuleDefinition that<br>contains the owner of the MapsTo, all references to the local<br>ComponentInstance or the remote ComponentInstance MUST dereference<br>to both objects.
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
            local(SBOL_LOCAL, SBOL_COMPONENT, this, local),
            remote(SBOL_REMOTE,  SBOL_COMPONENT, this, remote)
            {
            }

	};
}

#endif