/**
 * @file    dblt.h
 * @brief   Contains the interface for Design-Build-Test classes
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
 * ------------------------------------------------------------------------>*/

#ifndef DBLT_INCLUDED
#define DBLT_INCLUDED

#include "combinatorialderivation.h"


namespace sbol
{
    class Design : public TopLevel
    {
    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > function;
        Design(std::string uri) :
            TopLevel(UNDEFINED, uri),
            structure(SBOL_COMPONENT_DEFINITION, this, "", { libsbol_rule_3 }),
            function(SBOL_MODULE_DEFINITION, this, "", { libsbol_rule_4 })
        {
        };

        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        virtual ~Design() {};

    };
    
    class Build : public TopLevel
    {
    public:
        OwnedObject < ComponentDefinition > structure;
        OwnedObject < ModuleDefinition > behavior;
        Build(std::string uri) :
            TopLevel(UNDEFINED, uri),
            structure(SBOL_COMPONENT_DEFINITION, this, "", { libsbol_rule_3 }),
            behavior(SBOL_MODULE_DEFINITION, this, "", { libsbol_rule_4 })
        {
        };
        
        // The destructor is over-ridden here thus preventing objects in the structure and function containers from being freed
        virtual ~Build() {};
        
    };
};



#endif