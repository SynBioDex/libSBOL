#include "property.h"

#include <string>

namespace sbol {
	class Identified {
		//std::string identity;  // @todo make URI type instead of string?
  //      std::string persistentIdentity;  // @todo make URI type instead of string?
		//int majorVersion;
		//int minorVersion;
		//std::string timeStamp;

	public:

		//Identified(std::string uri_prefix, std::string id);
		Identified(std::string uri_prefix = "http://examples.com", std::string id = "identified_object") :
			identity(TextProperty(uri_prefix + "/" + id + "/1.0.0")),
			persistentIdentity(TextProperty(uri_prefix + "/" + id + "/1.0.0")),
			version("1.0.0"),
			timeStamp(TextProperty())
			{
			}
		Identified(std::string, std::string, std::string);
		//sbol::TextProperty sbolString;

		//Identified(std::string uri_prefix, std::string id);

		TextProperty identity;
		TextProperty persistentIdentity;
		TextProperty version;
		TextProperty timeStamp;

		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		Identified clone();

	};
}