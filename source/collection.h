//
//  collection.h
//  SBOL_TEST
//
//  Created by Bryan on 1/6/17.
//
//

#ifndef COLLECTION_INCLUDED
#define COLLECTION_INCLUDED

#include "toplevel.h"

namespace sbol
{
    /// The Collection class is a class that groups together a set of TopLevel objects that have something in common. Some examples of Collection objects:
    /// . Results of a query to find all ComponentDefinition objects in a repository that function as promoters
    /// . A set of ModuleDefinition objects representing a library of genetic logic gates.
    /// . A ModuleDefinition for a complexdesign, and all of the ModuleDefinition, ComponentDefinition, Sequence, and Model objects used to provide its full specification.
    class Collection : public TopLevel
    {
    public:
        /// The members property of a Collection is OPTIONAL and MAY contain a set of URI references to zero or more TopLevel objects.
        List < URIProperty > members;
 
        /// Construct a Collection
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        Collection(std::string uri = DEFAULT_NS "/Collection/example", std::string version = "1.0.0") : Collection(SBOL_COLLECTION, uri, version) {};
        
        virtual ~Collection() {};
    protected:
        Collection(sbol_type type, std::string uri, std::string version) :
            TopLevel(type, uri, version),
            members(SBOL_MEMBERS, this)
        {
        };
    };
}
#endif /* COLLECTION_INCLUDED */
