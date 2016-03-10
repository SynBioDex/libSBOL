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
        TopLevel(std::string uri = DEFAULT_NS "/TopLevel/example") : TopLevel(SBOL_TOP_LEVEL, uri) {};
        TopLevel(std::string uri_prefix, std::string display_id, std::string version) : TopLevel(SBOL_TOP_LEVEL, uri_prefix, display_id, version) {};
        void addToDocument(sbol::Document&);
        
    protected:
        TopLevel(sbol_type type_uri, std::string uri) :
            Identified(type_uri, uri)
            {
            };
        TopLevel(sbol_type type_uri, std::string uri_prefix, std::string display_id, std::string version) :
			Identified(type_uri, uri_prefix, display_id, version)
            {
            };
    };
    
    // Sets or overwrites the first reference URI with the argument object's identity
    // Automatically adds TopLevel objects to the document
    template < class SBOLClass>
    void ReferencedObject<SBOLClass>::set(SBOLClass& sbol_obj)
    {
        this->sbol_owner->properties[this->type][0] = sbol_obj.identity.get();
        if (this->sbol_owner->doc)
        {
            SBOLClass* ptr = &sbol_obj;
            if (TopLevel* top_level = dynamic_cast<sbol::TopLevel*>(ptr))
            {
                top_level->addToDocument(*this->sbol_owner->doc);
            }
        }
    };
    
    // Need to make addToDocument a method for all Identified objects (not just TopLevel)
    // Automatically adds TopLevel objects to the document
    template < class SBOLClass>
    void ReferencedObject<SBOLClass>::add(SBOLClass& sbol_obj)
    {
        this->sbol_owner->properties[this->type].push_back(sbol_obj.identity.get());
        if (this->sbol_owner->doc)
        {
            SBOLClass* ptr = &sbol_obj;
            if (TopLevel* top_level = dynamic_cast<sbol::TopLevel*>(ptr))
            {
                top_level->addToDocument(*this->sbol_owner->doc);
            }
        }
    };
    
}




#endif