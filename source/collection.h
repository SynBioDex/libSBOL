/**
 * @file    collection.h
 * @brief   Collection class
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


#ifndef COLLECTION_INCLUDED
#define COLLECTION_INCLUDED

#include "toplevel.h"

namespace sbol
{
    /// The Collection class is a class that groups together a set of TopLevel objects that have something in common. Some examples of Collection objects:
    /// . Results of a query to find all ComponentDefinition objects in a repository that function as promoters
    /// . A set of ModuleDefinition objects representing a library of genetic logic gates.
    /// . A ModuleDefinition for a complexdesign, and all of the ModuleDefinition, ComponentDefinition, Sequence, and Model objects used to provide its full specification.
    class SBOL_DECLSPEC Collection : public TopLevel
    {
    public:
 
        /// Construct a Collection
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Collection(std::string uri = "example", std::string version = VERSION_STRING) : Collection(SBOL_COLLECTION, uri, version) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        Collection(rdf_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version),
            members(this, SBOL_MEMBERS, '0', '*', ValidationRules({}))
            {
            };
        
        /// The members property of a Collection is OPTIONAL and MAY contain a set of URI references to zero or more TopLevel objects.
        URIProperty members;
        
        virtual ~Collection() {};
    };
}
#endif /* COLLECTION_INCLUDED */
