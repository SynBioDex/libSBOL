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
		URIProperty persistentIdentity;
		TextProperty displayId;
		VersionProperty version;
		URIProperty wasDerivedFrom;
		TextProperty name;
		TextProperty description;


//        Identified(std::string uri = DEFAULT_NS "/Identified/example", std::string version) : Identified(SBOL_IDENTIFIED, uri, version) {};
//        Identified(std::string prefix, std::string display_id, std::string version) : Identified(SBOL_IDENTIFIED, prefix, display_id, version) {};


	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI
        virtual ~Identified() {};
	protected:
        Identified(sbol_type type_uri, std::string uri, std::string version = "1.0.0") :
            SBOLObject(type_uri, uri),
            persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, uri),
            displayId(SBOL_DISPLAY_ID, this, uri),
            version(SBOL_VERSION, this, version),
            wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this, ""),
            name(SBOL_NAME, this, ""),
            description(SBOL_DESCRIPTION, this, "")
        {
            if(isSBOLCompliant())
            {
                identity.set(getHomespace() + "/" + uri + "/" + version);
                persistentIdentity.set(getHomespace() + "/" + uri);
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
			wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this, ""),
			name(SBOL_NAME, this, ""),
			description(SBOL_DESCRIPTION, this, "")
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
    
};

#endif