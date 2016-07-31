#ifndef SEQUENCE_CONSTRAINT_INCLUDED
#define SEQUENCE_CONSTRAINT_INCLUDED

#include "identified.h"

namespace sbol
{
    // Forward declaration of Component necessary for SequenceConstraint.subject and .object properties
    class Component;
    
    /// The SequenceConstraint class can be used to assert restrictions on the relative, sequence-based positions of pairs of Component objects contained by the same parent ComponentDefinition. The primary purpose of this class is to enable the specification of partially designed ComponentDefinition objects, for which the precise positions or orientations of their contained Component objects are not yet fully determined.
    class SequenceConstraint : public Identified
	{
	
	public:
        ReferencedObject subject;
        ReferencedObject object;
        URIProperty restriction;
        
        SequenceConstraint(std::string uri = DEFAULT_NS "/SequenceConstraint/example", std::string subject = "", std::string object = "", std::string restriction = SBOL_RESTRICTION_PRECEDES, std::string version = "1.0.0") :
            SequenceConstraint(SBOL_SEQUENCE_CONSTRAINT, uri, subject, object, restriction, version) {};
        
//        SequenceConstraint(std::string uri_prefix, std::string display_id, std::string version, std::string subject, std::string object, std::string restriction) :
//			SequenceConstraint(SBOL_SEQUENCE_CONSTRAINT, uri_prefix, display_id, version, subject, object, restriction) {};
		
        virtual ~SequenceConstraint() {};
	
	protected:
        SequenceConstraint(sbol_type type, std::string uri, std::string subject, std::string object, std::string restriction, std::string version) :
            Identified(type, uri, version),
            subject(SBOL_SUBJECT, SBOL_COMPONENT, this, subject),
            object(SBOL_OBJECT, SBOL_COMPONENT, this, object),
            restriction(SBOL_RESTRICTION, this, restriction)
            {
            }
//        SequenceConstraint(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, std::string subject, std::string object, std::string restriction) :
//			Identified(type, uri_prefix, display_id, version),
//			subject(SBOL_SUBJECT, SBOL_COMPONENT, this, subject),
//			object(SBOL_OBJECT, SBOL_COMPONENT, this, object),
//			restriction(SBOL_RESTRICTION, this, restriction)
//			{
//			}
	};
}

#endif