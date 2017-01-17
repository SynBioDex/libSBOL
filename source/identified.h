/**
 * @file    identified.h
 * @brief   Identified class
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

#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "object.h"
#include <string>

namespace sbol
{
    /// @defgroup sbol_core_data_model SBOL Core Data Model
    /// The core data model consists of classes described in the [Synthetic Biology Open Language specification document](http://sbolstandard.org).  Classes in the core data model represent key ideas in the description of biological structure and function.
    
    /// @ingroup sbol_core_data_model
    /// All SBOL-defined classes are directly or indirectly derived from the Identified abstract class. An Identified object is identified using a Uniform Resource Identifier (URI), a unique string that identifies and refers to a specific object in an SBOL document or in an online resource such as a DNA repository.
	class Identified : public SBOLObject
    {
	
	public:
        /// The persistentIdentity property is OPTIONAL and has a data type of URI. This URI serves to uniquely refer to a set of SBOL objects that are different versions of each other. An Identified object MUST be referred to using either its identity URI or its persistentIdentity URI.
		URIProperty persistentIdentity;
        
        /// The displayId property is an OPTIONAL identifier with a data type of String. This property is intended to be an intermediate between name and identity that is machine-readable, but more human-readable than the full URI of an identity. If the displayId property is used, then its String value SHOULD be locally unique (global uniqueness is not necessary) and MUST be composed of only alphanumeric or underscore characters and MUST NOT begin with a digit.
		TextProperty displayId;
        
        /// If the version property is used, then it is RECOMMENDED that version numbering follow the conventions of [semantic versioning](http://semver.org/), particularly as implemented by [Maven](http://maven.apache.org/). This convention represents versions as sequences of numbers and qualifiers that are separated by the characters “.” and “-” and are compared in lexicographical order (for example, 1 < 1.3.1 < 2.0-beta). For a full explanation, see the linked resources.
		VersionProperty version;
        
        /// The wasDerivedFrom property is OPTIONAL and has a data type of URI. An SBOL object with this property refers to another SBOL object or non-SBOL resource from which this object was derived. If the wasDerivedFrom property of an SBOL object A that refers to an SBOL object B has an identical persistentIdentity, and both A and B have a version, then the version of B MUST precede that of A. In addition, an SBOL object MUST NOT refer to itself via its own wasDerivedFrom property or form a cyclical chain of references via its wasDerivedFrom property and those of other SBOL objects. For example, the reference chain “ A was derived from B and B was derived from A” is cyclical.
		URIProperty wasDerivedFrom;
        
        /// The name property is OPTIONAL and has a data type of String. This property is intended to be displayed to a human when visualizing an Identified object. If an Identified object lacks a name, then software tools SHOULD instead display the object’s displayId or identity. It is RECOMMENDED that software tools give users the ability to switch perspectives between name properties that are human-readable and displayId properties that are less human-readable, but are more likely to be unique.
		TextProperty name;
        
        /// The description property is OPTIONAL and has a data type of String. This property is intended to contain a more thorough text description of an Identified object.
		TextProperty description;

        virtual ~Identified() {};
        template < class SBOLClass > SBOLClass& copy(std::string ns = "", std::string version = "");

    protected:
        /// Copy an object and automatically increment its version. If the optional version argument is specified, it will be used instead of incrementing the copied object's version. An object may also be copied into a new document and a new namespace, assuming compliant URIs.
        /// @tparam SBOLClass The type of SBOL object being copied
        /// @param new_doc The new copies will be attached to this Document.  NULL by default.
        /// @param ns This namespace will be substituted for the current namespace (as configured by setHomespace) in all SBOL-compliat URIs.
        /// @param version A new version
        /// @return The full URI of the created object.
        Identified& copy(Document* target_doc = NULL, std::string ns = "", std::string version = "");

        
        Identified(sbol_type type_uri, std::string uri, std::string version = "1.0.0") :
            SBOLObject(type_uri, uri),
            persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, uri),
            displayId(SBOL_DISPLAY_ID, this, uri),
            version(SBOL_VERSION, this, version),
            wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this),
            name(SBOL_NAME, this),
            description(SBOL_DESCRIPTION, this)
        {
            if(isSBOLCompliant())
            {
                if (compliantTypesEnabled())
                {
                    identity.set(getHomespace() + "/" + getClassName(type) + "/" + uri + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + uri);
                }
                else
                {
                    identity.set(getHomespace() + "/" + uri + "/" + version);
                    persistentIdentity.set(getHomespace() + "/" + uri);
                }
            }
            else if (hasHomespace())
            {
                identity.set(getHomespace() + "/" + uri);
                persistentIdentity.set(getHomespace() + "/" + uri);
            }
            identity.validate();
        }
        
        Identified(sbol_type type_uri, std::string prefix, std::string display_id, std::string version) :
			SBOLObject(type_uri, prefix, display_id, version),
			persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, prefix + "/" + display_id),
			displayId(SBOL_DISPLAY_ID, this, display_id),
			version(SBOL_VERSION, this, version),
			wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this),
			name(SBOL_NAME, this),
			description(SBOL_DESCRIPTION, this)
		{
            identity.validate();
		}
        
//        Identified(sbol_type type_uri, std::string uri) :
//            SBOLObject(type_uri, prefix, display_id),
//            persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, prefix + "/" + display_id),
//            displayId(SBOL_DISPLAY_ID, this, display_id),
//            version(SBOL_VERSION, this, version),
//            wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this, ""),
//            name(SBOL_NAME, this, name),
//            description(SBOL_DESCRIPTION, this, description)
//        {
//            identity.validate();
//        }
	};
  
    template <class SBOLClass>
    SBOLClass& Identified::copy(std::string ns, std::string version)
    {
        return (SBOLClass&)this->copy(NULL, ns, version);
    };
  
//    ///
//    template <class SBOLClass>
//    SBOLClass& Identified::copy(Document& doc)
//    {
//        return (SBOLClass&)&copy();
//    };
};

#endif