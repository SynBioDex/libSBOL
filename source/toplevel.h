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
    class Plan;
    class Agent;
    
    /// All SBOL classes derived from TopLevel appear as top level nodes in the RDF/XML document tree and SBOL files. An abstract class.
	class SBOL_DECLSPEC TopLevel : public Identified
	{

	// The public constructor delegates to this protected constructor in order to initialize the object with an SBOL type URI 
    public:
        ReferencedObject attachments;
        
        TopLevel(rdf_type type_uri = SBOL_TOP_LEVEL, std::string uri = "example", std::string version = VERSION_STRING) :
            Identified(type_uri, uri, version),
            attachments(this, SBOL_ATTACHMENTS, SBOL_ATTACHMENT, '0', '*', ValidationRules({}))
        {
            if  (Config::getOption("sbol_compliant_uris").compare("True") == 0)
            {
                displayId.set(uri);
                if (Config::getOption("sbol_typed_uris").compare("True") == 0)
                {
                    persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
                    if (version != "")
                        identity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get() + "/" + version);
                    else
                        identity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
                }
                else
                {
                    persistentIdentity.set(getHomespace() + "/" + displayId.get());
                    if (version != "")
                        identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
                    else
                        identity.set(getHomespace() + "/" + displayId.get());
                }
            }
        };

        void addToDocument(sbol::Document&);
        virtual ~TopLevel() {};
        
        /// Recursively copies an object. Use this to copy an object to a new document, a new namespace, or to increment its version recursively. An object be recursively copied into a new document and a new namespace, assuming compliant URIs. If the optional version argument is specified, it will be used instead of incrementing the copied object's version (this can be used when using a custom versioning scheme other than libSBOL's default).
        /// @tparam SBOLClass The type of SBOL object being copied
        /// @param new_doc The new copies will be attached to this Document.  NULL by default.
        /// @param ns This namespace will be substituted for the current namespace (as configured by setHomespace) in all SBOL-compliant URIs.
        /// @param version A new version
        /// @return The copied object.
        template < class SBOLClass > SBOLClass& copy(Document* target_doc = NULL, std::string ns = "", std::string version = "");

        /// Copies an object. No child objects are copied.
        /// @param uri A URI for the new object, or a displayId if operating in SBOLCompliant mode
        /// @tparam Usually the same type of SBOL object as this
        template < class SBOLClass > SBOLClass& simpleCopy(std::string uri);
        
        /// @param uri A URI for the new object, or a displayId if operating in SBOLCompliant mode
        /// @tparam The type of SBOL object to generate
        template<class SBOLClass>
        SBOLClass& generate(std::string uri);

        /// @param uri A URI for the new object, or a displayId if operating in SBOLCompliant mode
        /// @tparam The type of SBOL object to generate
        template<class SBOLClass>
        SBOLClass& generate(std::string uri, Agent& agent, Plan& plan, std::vector<Identified*> usages = {});

        void initialize(std::string uri);

    };
    

}




#endif
