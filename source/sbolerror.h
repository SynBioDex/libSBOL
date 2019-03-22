/**
 * @file    sbolerror.h
 * @brief   SBOLError class and error codes
 * @author  Bryan Bartley
 * @email   bartleyba@sbolstandard.org
 *
 * <!--------------------------------------------------------------------------
 * This file is part of libSBOL.  Please visit http://sbolstandard.org for more
 * information about SBOL, and the latest version of libSBOL.
 *
 *  Copyright 2016 University of Washington, WA, USA
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ------------------------------------------------------------------------->*/


#ifndef SBOL_ERROR_INCLUDED
#define SBOL_ERROR_INCLUDED

#include "config.h"
#include <string>
#include <iostream>

namespace sbol
{
	enum SBOLErrorCode { DUPLICATE_URI_ERROR,
                         NOT_FOUND_ERROR,
                         SBOL_ERROR_NOT_FOUND,
                         END_OF_LIST,
                         SBOL_ERROR_URI_NOT_UNIQUE,
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
                         SBOL_ERROR_TYPE_MISMATCH,
                         SBOL_ERROR_BAD_HTTP_REQUEST,
                         SBOL_ERROR_HTTP_UNAUTHORIZED
                        };

	//SBOLErrorCode SBOLError(SBOLErrorCode error_code, const std::string message);
    
    class SBOL_DECLSPEC SBOLError: public std::exception {
    private:
        std::string message_;
        SBOLErrorCode err_;
    public:
        explicit SBOLError(SBOLErrorCode error_code, std::string message) :
        message_(message),
        err_(error_code)
        {
        };
        virtual const char* what() const throw() {
            return message_.c_str();
        }
        std::string error_message()
        {
            return message_;
        }
        SBOLErrorCode error_code() const
        {
            return err_;
        }
    };
    
};

#endif