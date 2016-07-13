#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "object.h"
#include <string>

namespace sbol
{
    /// All SBOL-defined classes are directly or indirectly derived from the Identified abstract class. An Identified object is identified using a Uniform Resource Identifier (URI) which is essentially a unique string referring to an objects in an SBOL document or somewhere on the World Wide Web (a URL is a kind of URI).
	class Identified : public SBOLObject
    {
	
	public:
		URIProperty persistentIdentity;
		TextProperty displayId;
		TextProperty version;
		URIProperty wasDerivedFrom;
		TextProperty name;
		TextProperty description;


        Identified(std::string uri = DEFAULT_NS "/Identified/example") : Identified(SBOL_IDENTIFIED, uri) {};
        Identified(std::string prefix, std::string display_id, std::string version) : Identified(SBOL_IDENTIFIED, prefix, display_id, version) {};
//        Identified(std::string prefix = SBOL_URI "/Identified",
//				   std::string display_id = "example",
//				   std::string name = "",
//				   std::string description = "",
//				   std::string version = "1.0.0") : Identified(SBOL_IDENTIFIED, prefix, display_id, name, description, version)
//		{
//        }


	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
	protected:
        Identified(sbol_type type_uri, std::string uri) :
            SBOLObject(type_uri, uri),
            persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, getHomespace() + uri),
            displayId(SBOL_DISPLAY_ID, this, ""),
            version(SBOL_VERSION, this, ""),
            wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this, ""),
            name(SBOL_NAME, this, ""),
            description(SBOL_DESCRIPTION, this, "")
        {
            if  (isSBOLCompliant())
            {
                this->displayId.set(uri);
                this->identity.set(getHomespace() + "/" + getClassName(type) + "/" + this->displayId.get() + "/" + this->version.get());
                this->persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + this->displayId.get());
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