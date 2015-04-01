#include "sbolerror.h"

using namespace sbol;

namespace sbol
{
	int SBOLError(int error_code, const std::string message)
	{
		// @todo: make error_code an enumerated type
		std::cout << "SBOL error " << error_code << ":" << message << std::endl;
		return error_code;
	};
}
