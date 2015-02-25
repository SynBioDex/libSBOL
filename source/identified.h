#include <string>
#include <ctime>

namespace sbol {
	class Identified {
		std::string identity;  // @todo make URI type instead of string?
        std::string persistentIdentity;  // @todo make URI type instead of string?
		int majorVersion;
		int minorVersion;
		std::string timeStamp;
	public:

		//Identified(std::string uri_prefix, std::string id);
		Identified() :
			identity(""),
			persistentIdentity(""),
			majorVersion(0),
			minorVersion(0),
			timeStamp("") 
			{
			}
		Identified(std::string uri_prefix, std::string id);
		void setIdentity(std::string, std::string);
		void stampTime();
		std::string getIdentity();
		int getMinorVersion();
		int getMajorVersion();
		std::string getTimeStamp();

	};
}