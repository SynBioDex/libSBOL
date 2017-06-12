/**
 * @file    sbol.h
 * @brief   Import this header to access the libSBOL API
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
 * ---------------------------------------------------------------------- -->*/

#ifndef SBOL_INCLUDED
#define SBOL_INCLUDED

#include "provo.h"
#include "partshop.h"

//// This is the global SBOL register for classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a constructor
//extern std::unordered_map<std::string, sbol::SBOLObject&(*)()> SBOL_DATA_MODEL_REGISTER;
//
//template <class SBOLClass>
//void extend_data_model(std::string uri)
//{
//	SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, ( SBOLObject&(*)() )&create<SBOLClass>));
//};

#endif