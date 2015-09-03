#ifndef IDENTIFIED_INCLUDED
#define IDENTIFIED_INCLUDED

#include "property.h"

#include <string>

namespace sbol {
	class Identified : public SBOLObject {

	// This protected constructor is a delegate constructor in order to initialize the object with an SBOL type URI 
	protected:
		Identified(sbol_type type, std::string uri_prefix, std::string id) :
			SBOLObject(type, uri_prefix, id),
			//SBOLObject(type),
			//identity(Property<std::string>(uri_prefix + "/" + id, SBOL_IDENTITY, this)),
			persistentIdentity(Property<std::string>(uri_prefix + "/" + id, SBOL_PERSISTENT_IDENTITY, this))
			//version(VersionProperty("1.0.0"))			
		{
		}
	public:

		//Identified(std::string uri_prefix, std::string id);
		Identified(std::string uri_prefix = SBOL_URI "#" SBOL_IDENTIFIED, std::string id = "example") : Identified(SBOL_URI "#" SBOL_IDENTIFIED, uri_prefix, id)
			{
			}



		//Identified(std::string, std::string id, std::string);
		//Identified(std::string uri_prefix, std::string id);

		//Property<std::string> identity;
		Property<std::string> persistentIdentity;
		//Property<std::string> version;

		//sbol_type getTypeURI();
		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		Identified clone();

	};
}

#endif