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
			identity(TextProperty(uri_prefix + "/" + id + "/0/0")),
			persistentIdentity(TextProperty(uri_prefix + "/" + id + "/0/0")),
			majorVersion(0),
			minorVersion(0),
			timeStamp(TextProperty())
			{
			}
		//sbol::TextProperty sbolString;

		//Identified(std::string uri_prefix, std::string id);

		TextProperty identity;
		TextProperty persistentIdentity;
		IntProperty majorVersion;
		IntProperty minorVersion;
		TextProperty timeStamp;

		std::string getTimeStamp();
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		int getMinorVersion();
		int getMajorVersion();

	};
}