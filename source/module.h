/**
 * @file    module.h
 * @brief   Module class
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

#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include "identified.h"
#include "mapsto.h"
#include "measurement.h"

namespace sbol
{
    // Forward declaration of ModuleDefinition necesaary for Module.definition template
    class ModuleDefinition;
    
    /// The Module class represents a submodule of a ModuleDefinition within a hierarchical design.
    class SBOL_DECLSPEC Module : public Identified
	{
	public:
        /// The definition property is a REQUIRED URI that refers to the ModuleDefinition for the Module.
        ReferencedObject definition;
        
        /// The mapsTos property is an OPTIONAL set of MapsTo objects that refer to and link ComponentInstance objects together within the heterarchy of Module, ModuleDefinition, ComponentInstance, and ComponentDefinition objects.
        OwnedObject<MapsTo> mapsTos;
        
        /// The measurements property links a Module to parameters or measurements and their associated units. For example Measurements attached to a Module may indicate the experimental or environmental context in which a ModuleDefinition is instantiated.
        OwnedObject<Measurement> measurements;
        
        /// Construct a Module. If operating in SBOL-compliant mode, use ModuleDefinition::modules::create instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param definition The identity of the Component with this structural constraint
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Module(std::string uri = "example", std::string definition = "", std::string version = VERSION_STRING) : Module(SBOL_MODULE, uri, definition, version) {};

        /// Constructor used for defining extension classes
        /// @param type The RDF type for an extension class derived from this one
        Module(rdf_type type, std::string uri, std::string definition, std::string version) :
            Identified(type, uri, version),
            definition(this, SBOL_DEFINITION, SBOL_MODULE_DEFINITION, '1', '1', ValidationRules({}), definition),
            mapsTos(this, SBOL_MAPS_TOS, '0', '*', ValidationRules({})),
            measurements(this, SBOL_MEASUREMENTS, '0', '*', ValidationRules({}))
        {
        };

        virtual ~Module() {};
    };
}

#endif
