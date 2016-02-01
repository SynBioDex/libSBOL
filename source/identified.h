#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "object.h"
#include <string>

namespace sbol
{
	class Identified : public SBOLObject
    {
	
	public:
		TextProperty persistentIdentity;
		TextProperty displayId;
		TextProperty version;
		URIProperty wasDerivedFrom;
		TextProperty name;
		TextProperty description;

		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		Identified clone();

		Identified(std::string prefix = SBOL_URI "/Identified",
				   std::string display_id = "example",
				   std::string name = "",
				   std::string description = "",
				   std::string version = "1.0.0") : Identified(SBOL_IDENTIFIED, prefix, display_id, name, description, version)
		{
		}


	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
	protected:
		Identified(sbol_type type_uri, std::string prefix, std::string display_id, std::string name, std::string description, std::string version) :
			SBOLObject(type_uri, prefix, display_id),
			persistentIdentity(SBOL_PERSISTENT_IDENTITY, this, prefix + "/" + display_id),
			displayId(SBOL_DISPLAY_ID, this, display_id),
			version(SBOL_VERSION, this, version),
			wasDerivedFrom(SBOL_WAS_DERIVED_FROM, this, ""),
			name(SBOL_NAME, this, name),
			description(SBOL_DESCRIPTION, this, description)
		{
			identity.validate();
		}
	};
};

#endif