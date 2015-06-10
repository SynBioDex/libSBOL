#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "property.h"

#include <string>

namespace sbol {
	class Identified : public SBOLObject {
	private:
		sbol_type type = SBOL_IDENTIFIED;
	public:

		//Identified(std::string uri_prefix, std::string id);
		Identified(std::string uri_prefix = "http://examples.com", std::string id = "Identified") :
			SBOLObject(),
			identity(TextProperty(SBOL_IDENTITY, this, uri_prefix + "/" + id + "/1.0.0")),
			persistentIdentity(TextProperty(SBOL_PERSISTENT_IDENTITY, this, uri_prefix + "/" + id + "/1.0.0")),
			version(VersionProperty("1.0.0")),
			timeStamp(TextProperty())
			{
			}
		Identified(std::string, std::string, std::string);
		//sbol::TextProperty sbolString;

		//Identified(std::string uri_prefix, std::string id);

		TextProperty identity;
		TextProperty persistentIdentity;
		VersionProperty version;
		TextProperty timeStamp;

		sbol_type getTypeURI();
		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		Identified clone();

	};
}

#endif