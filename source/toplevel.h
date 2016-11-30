#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "identified.h"

#include <string>

namespace sbol 
{
    /// All SBOL classes derived from TopLevel appear as top level nodes in the RDF/XML document tree and SBOL files. An abstract class.
	class TopLevel : public Identified
	{

	// The public constructor delegates to this protected constructor in order to initialize the object with an SBOL type URI 
    public:
//        TopLevel(std::string uri = DEFAULT_NS "/TopLevel/example") : TopLevel(SBOL_TOP_LEVEL, uri) {};
//        TopLevel(std::string uri_prefix, std::string display_id, std::string version) : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, version) {};
        void addToDocument(sbol::Document&);
        virtual ~TopLevel() {};
        template < class SBOLClass > SBOLClass& copy(Document* target_doc = NULL, std::string ns = "", std::string version = "");

    protected:
        TopLevel(sbol_type type_uri, std::string uri, std::string version) :
            Identified(type_uri, uri, version)
            {
                if  (isSBOLCompliant())
                {
                    displayId.set(uri);
                    if (compliantTypesEnabled())
                    {
                        identity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get() + "/" + version);
                        persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + displayId.get());
                    }
                    else
                    {
                        identity.set(getHomespace() + "/" + displayId.get() + "/" + version);
                        persistentIdentity.set(getHomespace() + "/" + displayId.get());
                    }
                }
            };
        TopLevel(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string version) :
			Identified(type_uri, uri_prefix, display_id, version)
            {
            };
    };
    

}




#endif