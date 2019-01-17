/**
 * @file    experiment.h
 * @brief   Classes for grouping experimental data files
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

#ifndef EXPERIMENT_INCLUDED
#define EXPERIMENT_INCLUDED

namespace sbol
{

    /// The ExperimentalData class represents a set of links to experimental data files (Attachment objects) that are typically but not always associated with a single sample, experimental condition, and/or lab instrument.
    class SBOL_DECLSPEC ExperimentalData : public TopLevel
    {
    public:
        /// Construct a new ExperimentalData object.
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        ExperimentalData(std::string uri = "example", std::string version = VERSION_STRING) : ExperimentalData(SBOL_EXPERIMENTAL_DATA, uri, version) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        ExperimentalData(rdf_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version)
        {
        };
        virtual ~ExperimentalData(){};
    };

    
    /// A generated Entity is linked through a wasGeneratedBy relationship to an Activity, which is used to describe how different Agents and other entities were used. An Activity is linked through a qualifiedAssociation to Associations, to describe the role of agents, and is linked through qualifiedUsage to Usages to describe the role of other entities used as part of the activity. Moreover, each Activity includes optional startedAtTime and endedAtTime properties. When using Activity to capture how an entity was derived, it is expected that any additional information needed will be attached as annotations. This may include software settings or textual notes. Activities can also be linked together using the wasInformedBy relationship to provide dependency without explicitly specifying start and end times.
    class SBOL_DECLSPEC Experiment : public TopLevel
    {
    public:
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param version An arbitrary version string. If SBOLCompliance is enabled, this should be a Maven version string of the form "major.minor.patch".
        Experiment(std::string uri = "example", std::string version = VERSION_STRING) : Experiment(SBOL_EXPERIMENT, uri, version) {};

        /// Constructor used for defining extension classes
        /// @param rdf_type The RDF type for an extension class derived from this one
        Experiment(rdf_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version),
            experimentalData(this, SBOL_URI "#experimentalData", SBOL_EXPERIMENTAL_DATA, '0', '*', ValidationRules({}))
            {           
            };
        
        /// The experimentalData property is OPTIONAL and MAY contain zero or more URIs that refer to ExperimentalData objects.
        ReferencedObject experimentalData;
        
        virtual ~Experiment(){};
    };
}

#endif /* EXPERIMENT_INCLUDED */
