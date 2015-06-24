#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "property.h"

#include <string>

namespace sbol {
	class Identified : public SBOLObject {
	public:

		//Identified(std::string uri_prefix, std::string id);
		Identified(std::string uri_prefix = SBOL_URI "/Identified", std::string id = "example") : Identified(SBOL_IDENTIFIED, uri_prefix, id)
			{
			}
		Identified(sbol_type type, std::string uri_prefix, std::string id) :
			SBOLObject(type),
			identity(TextProperty(SBOL_IDENTITY, this, uri_prefix + "/" + id + "/1.0.0")),
			persistentIdentity(TextProperty(SBOL_PERSISTENT_IDENTITY, this, uri_prefix + "/" + id + "/1.0.0")),
			version(VersionProperty("1.0.0")),
			timeStamp(TextProperty())
			{
			}

		//Identified(std::string, std::string id, std::string);
		//sbol::TextProperty sbolString;

		//Identified(std::string uri_prefix, std::string id);

		TextProperty identity;
		TextProperty persistentIdentity;
		VersionProperty version;
		TextProperty timeStamp;

		//sbol_type getTypeURI();
		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		Identified clone();

	};
}

#endif