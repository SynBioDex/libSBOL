/**
 * @file    sequenceannotation.h
 * @brief   SequenceAnnotation class
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

#ifndef ANNOTATION_INCLUDED
#define ANNOTATION_INCLUDED

#include "toplevel.h"
#include "location.h"

#include <string>

namespace sbol 
{
    class ComponentDefinition;
    
    /// The SequenceAnnotation class describes one or more regions of interest on the Sequence objects referred to by its parent ComponentDefinition. In addition, SequenceAnnotation objects can describe the substructure of their parent ComponentDefinition through association with the Component objects contained by this ComponentDefinition.
    class SBOL_DECLSPEC SequenceAnnotation : public Identified
	{
	public:
        /// Construct a ComponentDefinition
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        SequenceAnnotation(std::string uri = "example", std::string version = VERSION_STRING) : SequenceAnnotation(SBOL_SEQUENCE_ANNOTATION, uri, version) {};

        /// The component property is OPTIONAL and has a data type of URI. This URI MUST refer to a Component that is contained by the same parent ComponentDefinition that contains the SequenceAnnotation. In this way, the properties of the SequenceAnnotation, such as its description and locations, are associated with part of the substructure of its parent ComponentDefinition.
        ReferencedObject component;
        
        /// The locations property is a REQUIRED set of one or more Location objects that indicate which elements of a Sequence are described by the SequenceAnnotation.
        /// Allowing multiple Location objects on a single SequenceAnnotation is intended to enable representation of discontinuous regions (for example, a Component encoded across a set of exons with interspersed introns). As such, the Location objects of a single SequenceAnnotation SHOULD NOT specify overlapping regions, since it is not clear what this would mean. There is no such concern with different SequenceAnnotation objects, however, which can freely overlap in Location (for example, specifying overlapping linkers for sequence assembly).
		OwnedObject<Location> locations;
        
        /// Alternatively to describing substructure, a SequenceAnnotation can be utilized to identify a feature, such as a GenBank feature, of a specified Sequence. In this use case, the SequenceAnnotation MUST NOT have a component property, but instead it would have a roles property.
        /// The roles property comprises an OPTIONAL set of zero or more URIs describing the specified sequence feature being annotated. If provided, these role URIs MUST identify terms from appropriate ontologies. Roles are not restricted to describing biological function; they may annotate Sequences’ function in any domain for which an ontology exists.
        /// It is RECOMMENDED that these role URIs identify terms that are compatible with the type properties of this SequenceAnnotation’s parent ComponentDefinition. For example, a role of a SequenceAnnotation which belongs to a ComponentDefinition of type DNA might refer to terms from the Sequence Ontology. See documentation for ComponentDefinition for a table of recommended ontology terms.
        URIProperty roles;
        
        /// Tests if the comparand SequenceAnnotation precedes this one according to base coordinates
        /// @param comparand Another SequenceAnnotation
        /// @return true or false
        bool precedes(SequenceAnnotation& comparand);

        /// Tests if the comparand SequenceAnnotation follows this one according to base coordinates
        /// @param comparand Another SequenceAnnotation
        /// @return true or false
        bool follows(SequenceAnnotation& comparand);

        /// Tests if the comparand SequenceAnnotation is contained within the same start and end base coordinates as this one. This is mutually exclusive with overlaps.
        /// @param comparand Another SequenceAnnotation
        /// @return true or false
        bool contains(SequenceAnnotation& comparand);

        /// Tests if the comparand SequenceAnnotation overlaps with this one in the primary sequence
        /// @param comparand Another SequenceAnnotation
        /// @return true or false
        bool overlaps(SequenceAnnotation& comparand);
        
        std::vector<SequenceAnnotation*> precedes(std::vector<SequenceAnnotation*> comparand_list);
        std::vector<SequenceAnnotation*> follows(std::vector<SequenceAnnotation*> comparand_list);
        std::vector<SequenceAnnotation*> contains(std::vector<SequenceAnnotation*> comparand_list);
        std::vector<SequenceAnnotation*> overlaps(std::vector<SequenceAnnotation*> comparand_list);
        
        /// Convert a SequenceAnnotation to a subcomponent
        /// @return A ComponentDefinition representing the subcomponent
        ComponentDefinition& extract(int start_reference = 1);

        /// The length of a SequenceAnnotation in base coordinates.
        int length();
        
        virtual ~SequenceAnnotation() {};
	
	protected:
		// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
        SequenceAnnotation(rdf_type type, std::string uri, std::string version) :
            Identified(type, uri, version),
            component(this, SBOL_COMPONENT_PROPERTY, SBOL_COMPONENT, '0', '1', ValidationRules({})),
            locations(this, SBOL_LOCATIONS, '0', '*', ValidationRules({})),
            roles(this, SBOL_ROLES, '0', '*', ValidationRules({}))
            {
            };

	};
    

}

#endif