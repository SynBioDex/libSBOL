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
        /// The subject property is REQUIRED and MUST contain a URI that refers to a Component contained by the same parent ComponentDefinition that contains the SequenceConstraint.
        ReferencedObject subject;
        /// The object property is REQUIRED and MUST contain a URI that refers to a Component contained by the same parent ComponentDefinition that contains the SequenceConstraint. This Component MUST NOT be the same Component that the SequenceConstraint refers to via its subject property.
        ReferencedObject object;
        
        /// The restriction property is REQUIRED and has a data type of URI. This property MUST indicate the type of structural restriction on the relative, sequence-based positions or orientations of the subject and object Component objects. The URI value of this property SHOULD come from the RECOMMENDED URIs in the following table.
        /// | Restriction URI                           | Description                                                                      |
        /// | :---------------------------------------- | -------------------------------------------------------------------------------- |
        /// | http://sbols.org/v2#precedes              | The position of the subject Component MUST precede that of the object Component.<br> If each one is associated with a SequenceAnnotation, then the SequenceAnnotation<br>associated with the subject Component MUST specify a region that starts before<br>the region specified by the SequenceAnnotation associated with the object<br> Component. |
        /// | http://sbols.org/v2#sameOrientationAs     | The subject and object Component objects MUST have the same orientation. If each<br>one is associated with a SequenceAnnotation, then the orientation URIs of the<br>Location objects of the first SequenceAnnotation MUST be among those of the<br>second SequenceAnnotation, and vice versa. |
        /// | http://sbols.org/v2#oppositeOrientationAs | The subject and object Component objects MUST have opposite orientations. If<br>each one is associated with a SequenceAnnotation, then the orientation URIs of<br>the Location objects of one SequenceAnnotation MUST NOT be among those of the<br>other SequenceAnnotation. |
        URIProperty restriction;
        
        /// Construct a SequenceConstraint. If operating in SBOL-compliant mode, use ComponentDefinition::sequenceConstraints::create instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param subject Identity of the Component with this structural constraint
        /// @param object Identity of the other Component with this structural constraint
        /// @param restriction Flag indicating the type of structual constraint between the subject and object Components. By default, this is set to SBOL_RESTRICTION_PRECEDES
        SequenceConstraint(std::string uri = DEFAULT_NS "/SequenceConstraint/example", std::string subject = "", std::string object = "", std::string restriction = SBOL_RESTRICTION_PRECEDES, std::string version = "1.0.0") :
            SequenceConstraint(SBOL_SEQUENCE_CONSTRAINT, uri, subject, object, restriction, version) {};

		
        virtual ~SequenceConstraint() {};
	
	protected:
        SequenceConstraint(sbol_type type, std::string uri, std::string subject, std::string object, std::string restriction, std::string version) :
            Identified(type, uri, version),
            subject(SBOL_SUBJECT, SBOL_COMPONENT, this, subject),
            object(SBOL_OBJECT, SBOL_COMPONENT, this, object),
            restriction(SBOL_RESTRICTION, this, restriction)
            {
            }

	};
}

#endif