#ifndef SBOL_ERROR_INCLUDED
#define SBOL_ERROR_INCLUDED

#include <string>
#include <iostream>

namespace sbol
{
	enum SBOLErrorCode { DUPLICATE_URI_ERROR,
                         NOT_FOUND_ERROR,
                         END_OF_LIST,
                         SBOL_ERROR_PARSE,
                         SBOL_ERROR_MISSING_NAMESPACE,
                         SBOL_ERROR_NONCOMPLIANT_VERSION,
                         SBOL_ERROR_COMPLIANCE,
                         SBOL_ERROR_MISSING_DOCUMENT,
                         SBOL_ERROR_INVALID_ARGUMENT,
                         SBOL_ERROR_FILE_NOT_FOUND
                        };

	SBOLErrorCode SBOLError(SBOLErrorCode error_code, const std::string message);
};

#endif