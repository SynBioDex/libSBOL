#ifndef SEQUENCE_CONSTRAINT_INCLUDED
#define SEQUENCE_CONSTRAINT_INCLUDED

#include "identified.h"

namespace sbol
{
    // Forward declaration of Component necessary for SequenceConstraint.subject and .object properties
    class Component;
    
    class SequenceConstraint : public Identified
	{
	
	public:
		ReferencedObject<Component> subject;
		ReferencedObject<Component> object;
		URIProperty restriction;

        SequenceConstraint(std::string uri = DEFAULT_NS "/SequenceConstraint/example", std::string subject = "", std::string object = "", std::string restriction = SBOL_RESTRICTION_PRECEDES) :
            SequenceConstraint(SBOL_SEQUENCE_CONSTRAINT, uri, subject, object, restriction) {};
        
        SequenceConstraint(std::string uri_prefix, std::string display_id, std::string version, std::string subject, std::string object, std::string restriction) :
			SequenceConstraint(SBOL_SEQUENCE_CONSTRAINT, uri_prefix, display_id, version, subject, object, restriction) {};
		
        ~SequenceConstraint() {};
	
	protected:
        SequenceConstraint(sbol_type type, std::string uri, std::string subject, std::string object, std::string restriction) :
            Identified(type, uri),
            subject(SBOL_SUBJECT, this, subject),
            object(SBOL_OBJECT, this, object),
            restriction(SBOL_RESTRICTION, this, restriction)
            {
            }
        SequenceConstraint(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string subject, std::string object, std::string restriction) :
			Identified(type, uri_prefix, display_id, version),
			subject(SBOL_SUBJECT, this, subject),
			object(SBOL_OBJECT, this, object),
			restriction(SBOL_RESTRICTION, this, restriction)
			{
			}
	};
}

#endif