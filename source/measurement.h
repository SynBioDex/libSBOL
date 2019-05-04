/**
 * @file    measurement.h
 * @brief   Measurement class
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

#ifndef MEASUREMENT_INCLUDED
#define MEASUREMENT_INCLUDED

#include "identified.h"

namespace sbol
{
    /// The purpose of the Measure class is to link a numerical value to a unit of measure.
    class SBOL_DECLSPEC Measurement : public Identified
    {
    public:
        /// Construct a Measurement object
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param type A BioPAX ontology term that indicates whether the ComponentDefinition is DNA, RNA, protein, or some other molecule type.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Measurement(std::string uri = "example", double value = 0, std::string unit = "", std::string version = VERSION_STRING) : Measurement(SBOL_MEASURE, uri, value, unit, version) {};
        
        /// Constructor used for defining extension classes
        /// @param type The RDF type for an extension class derived from this one
        Measurement(rdf_type sbol_type, std::string uri, double value, std::string unit, std::string version) :
        Identified(sbol_type, uri, version),
            value(this, SBOL_VALUE, '1', '1', ValidationRules({}), value),
            unit(this, SBOL_UNIT, '1', '1', ValidationRules({}), unit),
            types(this, SBOL_TYPES, '0', '*', ValidationRules({}))
            {
            };
        
        /// The value property is REQUIRED and MUST contain a single float value.
        FloatProperty value;
        
        /// This URI may refer to a specific unit in the [Ontology of Units of Measure](http://www.ontology-of-units-of-measure.org/page/om-2) (OM), such as "gram per liter", but it can also refer to a custom unit that is not covered by OM but is still useful for synthetic biology, such as "molecules of equivalent fluorescein", or "MEFL" for short. The unit property is REQUIRED and MUST contain a single URI.
        URIProperty unit;
        
        /// The types property is an additional URI that helps interpret the purpose the measurement. For example, rate of reaction is identified by the SBO term http://identifiers.org/biomodels.sbo/SBO:0000612.
        URIProperty types;
    };

//    class Measured : public virtual Identified
//    {
//    public:
//        Measured() :
//            Identified(),
//            measurements(this, SBOL_MEASUREMENTS, '0', '*', ValidationRules({}))
//        {
//        };
//    
//        OwnedObject<Measurement> measurements;
//    };

}

#endif /* MEASUREMENT_INCLUDED */
