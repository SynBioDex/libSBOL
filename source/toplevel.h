#ifndef TOP_LEVEL_INCLUDED
#define TOP_LEVEL_INCLUDED

#include "identified.h"

#include <string>

namespace sbol 
{
	class TopLevel : public Identified
	{

	// The public constructor delegates to this protected constructor in order to initialize the object with an SBOL type URI 
    public:
//        TopLevel(std::string uri = DEFAULT_NS "/TopLevel/example") : TopLevel(SBOL_TOP_LEVEL, uri) {};
//        TopLevel(std::string uri_prefix, std::string display_id, std::string version) : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, version) {};
        void addToDocument(sbol::Document&);
        virtual ~TopLevel() {};
    protected:
        TopLevel(sbol_type type_uri, std::string uri, std::string version) :
            Identified(type_uri, uri, version)
            {
                if  (isSBOLCompliant())
                {
                    this->displayId.set(uri);
                    this->identity.set(getHomespace() + "/" + getClassName(type) + "/" + this->displayId.get() + "/" + this->version.get());
                    this->persistentIdentity.set(getHomespace() + "/" + getClassName(type) + "/" + this->displayId.get());
                }
            };
        TopLevel(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string version) :
			Identified(type_uri, uri_prefix, display_id, version)
            {
            };
    };
}




#endif