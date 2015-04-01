#ifndef SBOL_ERROR_INCLUDED
#define SBOL_ERROR_INCLUDED

#include <string>
#include <iostream>

namespace sbol
{
	int SBOLError(int error_code, const std::string message);
};

#endif