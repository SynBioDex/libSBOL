/**
 * @file    provo.h
 * @brief   PROV-O ontology for provenance relationships
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

#ifndef PROVO_INCLUDED
#define PROVO_INCLUDED



namespace sbol
{
    /// An Association is linked to an Agent through the agent relationship. The Association includes the hadRole property to qualify the role of the Agent in the Activity.
    class SBOL_DECLSPEC Association : public Identified
    {
    public:
        /// The agent property is REQUIRED and MUST contain a URI that refers to an Agent object.
        ReferencedObject agent;
        
        /// The hadRole property is REQUIRED and MUST contain a URI that refers to a particular term describing the usage of the agent.
        URIProperty hadRole;
        
        /// The hadPlan property is OPTIONAL and contains a URI that refers to a Plan.
        ReferencedObject hadPlan;
        
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Association(std::string uri = "example", std::string agent = "", std::string role = "", std::string version = "1.0.0") : Association(PROVO_ASSOCIATION, agent, role, uri, version) {};
        
        Association(sbol_type type, std::string uri, std::string agent, std::string role, std::string version) :
            Identified(type, uri, version),
            agent(PROVO_AGENT_PROPERTY, PROVO_AGENT, this, agent),
            hadRole(PROVO_HAD_ROLE, this, role),
            hadPlan(PROVO_HAD_PLAN, PROVO_PLAN, this)
        {
        };
    };

    /// How different entities are used in an Activity is specified with the Usage class, which is linked from an Activity through the qualifiedUsage relationship. A Usage is then linked to an Entity through the Entity’s URI and the role of this entity is qualified with the hadRole property. When the wasDerivedFrom property is used together with the full provenance described here, the entity pointed at by the wasDerivedFrom property MUST be included in a Usage.
    class SBOL_DECLSPEC Usage : public Identified
    {
    public:
        
        /// The entity property is REQUIRED and MUST contain a URI which MAY refer to an SBOL Identified object.
        ReferencedObject entity;
        
        /// The hadRole property is REQUIRED and MAY contain a URI that refers to a particular term describing the usage of an entity referenced by the entity property.
        URIProperty hadRole;
        
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Usage(std::string uri = "example", std::string entity = "", std::string role = "", std::string version = "1.0.0") : Usage(PROVO_USAGE, entity, role, uri, version) {};
        
        Usage(sbol_type type, std::string uri, std::string entity, std::string role, std::string version) :
            Identified(type, uri, version),
            entity(PROVO_ENTITY, SBOL_IDENTIFIED, this, entity),
            hadRole(PROVO_HAD_ROLE, this, role)
        {
        }
    };
    
    /// Examples of agents are person, organisation or software. These agents should be annotated with additional information, such as software version, needed to be able to run the same software again.
    class SBOL_DECLSPEC Agent : public TopLevel
    {
    public:
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Agent(std::string uri = "example", std::string version = "1.0.0") : Agent(PROVO_AGENT, uri, version) {};
        
        Agent(sbol_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version)
        {
        }
    };
        
    /// Examples of agents are person, organisation or software. These agents should be annotated with additional information, such as software version, needed to be able to run the same software again.
    class SBOL_DECLSPEC Plan : public TopLevel
    {
    public:
        /// Constructor
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Plan(std::string uri = "example", std::string version = "1.0.0") : Plan(PROVO_PLAN, uri, version) {};
            
        Plan(sbol_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version)
        {
        }
    };
    
    /// A generated Entity is linked through a wasGeneratedBy relationship to an Activity, which is used to describe how different Agents and other entities were used. An Activity is linked through a qualifiedAssociation to Associations, to describe the role of agents, and is linked through qualifiedUsage to Usages to describe the role of other entities used as part of the activity. Moreover, each Activity includes optional startedAtTime and endedAtTime properties. When using Activity to capture how an entity was derived, it is expected that any additional information needed will be attached as annotations. This may include software settings or textual notes. Activities can also be linked together using the wasInformedBy relationship to provide dependency without explicitly specifying start and end times.
    class SBOL_DECLSPEC Activity : public TopLevel
    {
    public:
 
        DateTimeProperty startedAtTime;
        
        /// The endedAtTime property is OPTIONAL and contains a dateTime (see section Section 12.7) value, indicating when the activity ended.
        DateTimeProperty endedAtTime;
        
        /// The wasInformedBy property is OPTIONAL and contains a URI of another activity.
        ReferencedObject wasInformedBy;
        
        /// The qualifiedAssociation property is OPTIONAL and MAY contain a set of URIs that refers to Association
        OwnedObject<Association> qualifiedAssociation;
        
        /// The qualifiedUsage property is OPTIONAL and MAY contain a set of URIs that refers to Usage objects.
        OwnedObject<Usage> qualifiedUsage;
        
        /// The type property is a REQUIRED ontology term that designates an activity or stage in the synthetic biology workflow, such as codon optimization or DNA assembly.
        URIProperty type;
        
        /// @param uri A full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Activity(std::string uri = "example", std::string action_type = "", std::string version = "1.0.0") : Activity(PROVO_ACTIVITY, uri, action_type, version) {};
        
        Activity(sbol_type type, std::string uri, std::string action_type, std::string version) :
            TopLevel(type, uri, version),
            type(SBOL_TYPES, this, action_type),
            startedAtTime(PROVO_STARTED_AT_TIME, this),
            endedAtTime(PROVO_ENDED_AT_TIME, this),
            wasInformedBy(PROVO_WAS_INFORMED_BY, PROVO_ACTIVITY, this)
            {
            };
        
        virtual ~Activity(){};

    };
}




#endif /* PROVO_INCLUDED */
