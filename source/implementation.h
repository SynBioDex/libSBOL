/**
 * @file    attachment.h
 * @brief   Attachment class
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

#ifndef IMPLEMENTATION_INCLUDED
#define IMPLEMENTATION_INCLUDED

#include "toplevel.h"

namespace sbol
{
    /// An Implementation represents a real, physical instance of a synthetic biological construct which may be associated with a laboratory sample. An Implementation may be linked back to its original design (either a ModuleDefinition or ComponentDefinition) using the wasDerivedFrom property inherited from the Identified superclass.
	class SBOL_DECLSPEC Implementation : public TopLevel
	{
	public:
        /// Construct an Implementation
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Implementation(std::string uri = "example", std::string version = VERSION_STRING) : Implementation(SBOL_IMPLEMENTATION, uri, version) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        Implementation(rdf_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version),
            built(this, SBOL_URI "#built", '0', '1', ValidationRules({}))
            {
            };

        // The built property is OPTIONAL and MAY contain a URI that MUST refer to a TopLevel object that is either a ComponentDefinition or ModuleDefinition. This ComponentDefinition or ModuleDefinition is intended to describe the actual physical structure and/or functional behavior of the Implementation. When the built property refers to a ComponentDefinition that is also linked to the Implementation via PROV-O properties such as wasDerivedFrom, it can be inferred that the actual structure and/or function of the Implementation matches its original design. When the built property refers to a different ComponentDefinition, it can be inferred that the Implementation has deviated from the original design. For example, the latter could be used to document when the DNA sequencing results for an assembled construct do not match the original target sequence.
        URIProperty built;

        virtual ~Implementation() {};
	};
}

#endif