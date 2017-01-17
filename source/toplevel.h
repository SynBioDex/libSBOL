/**
 * @file    toplevel.h
 * @brief   TopLevel class
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

#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "identified.h"

#include <string>

namespace sbol 
{
    /// All SBOL classes derived from TopLevel appear as top level nodes in the RDF/XML document tree and SBOL files. An abstract class.
	class TopLevel : public Identified
	{

	// The public constructor delegates to this protected constructor in order to initialize the object with an SBOL type URI 
    public:
        TopLevel(sbol_type type_uri = "", std::string uri = "", std::string version = "1.0.0") :
            Identified(type_uri, uri, version)
        {
            if  (isSBOLCompliant())
            {
                displayId.set(uri);
                if (compliantTypesEnabled())
                {
                    identity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get() + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
                }
                else
                {
                    identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + displayId.get());
                }
            }
        };

        void addToDocument(sbol::Document&);
        virtual ~TopLevel() {};
        
        /// Copy an object and automatically increment its version. If the optional version argument is specified, it will be used instead of incrementing the copied object's version. An object may also be copied into a new document and a new namespace, assuming compliant URIs.
        /// @tparam SBOLClass The type of SBOL object being copied
        /// @param new_doc The new copies will be attached to this Document.  NULL by default.
        /// @param ns This namespace will be substituted for the current namespace (as configured by setHomespace) in all SBOL-compliat URIs.
        /// @param version A new version
        /// @return The full URI of the created object.
        template < class SBOLClass > SBOLClass& copy(Document* target_doc = NULL, std::string ns = "", std::string version = "");

    };
    

}




#endif