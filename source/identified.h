#include <string>

namespace sbol {
	class Identified {
		std::string identity;
        std::string persistent_identity;
	public:
		void set_identity(std::string, std::string);
		std::string get_identity();
	};
}