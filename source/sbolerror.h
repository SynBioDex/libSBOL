#ifndef SBOL_ERROR_INCLUDED
#define SBOL_ERROR_INCLUDED

#include <string>
#include <iostream>

namespace sbol
{
	enum SBOLErrorCode { DUPLICATE_URI_ERROR,
                         NOT_FOUND_ERROR,
                         SBOL_ERROR_NOT_FOUND,
                         END_OF_LIST,
                         SBOL_ERROR_END_OF_LIST,
                         SBOL_ERROR_SERIALIZATION,
                         SBOL_ERROR_PARSE,
                         SBOL_ERROR_MISSING_NAMESPACE,
                         SBOL_ERROR_NONCOMPLIANT_VERSION,
                         SBOL_ERROR_COMPLIANCE,
                         SBOL_ERROR_MISSING_DOCUMENT,
                         SBOL_ERROR_INVALID_ARGUMENT,
                         SBOL_ERROR_FILE_NOT_FOUND,
                         SBOL_ERROR_ORPHAN_OBJECT,
                         SBOL_ERROR_TYPE_MISMATCH
                        };

	SBOLErrorCode SBOLError(SBOLErrorCode error_code, const std::string message);
};

#endif