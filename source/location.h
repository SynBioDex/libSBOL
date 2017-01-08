#ifndef LOCATION_INCLUDED
#define LOCATION_INCLUDED

#include "identified.h"

namespace sbol
{
    /// The Location class specifies the strand orientation of a Component and can be further extended by the Range, Cut, and GenericLocation classes.
	class Location : public Identified
	{
	public:
        /// The orientation indicates how a region of double-stranded DNA represented by the parent SequenceAnnotation and its associated Component are oriented. The orientation may be one of the following values. By default it is set to SBOL_ORIENTATION_INLINE.
        /// | Orientation URI                       | libSBOL Symbol                      |
        /// | :------------------------------------ | :---------------------------------- |
        /// | http://sbols.org/v2#inline            | SBOL_ORIENTATION_INLINE             |
        /// | http://sbols.org/v2#reverseComplement | SBOL_ORIENTATION_REVERSE_COMPLEMENT |
        URIProperty orientation;

	// A public constructor is required so objects can be auto created by the SBOLObject.OwnedObjects.create(...) method
        Location(sbol_type type = SBOL_LOCATION, std::string uri = DEFAULT_NS "/Location/example") :
			Identified(type, uri),
			orientation(SBOL_ORIENTATION, this, SBOL_ORIENTATION_INLINE)
			{
			}
        virtual ~Location() {};;
    };

    /// A Range object specifies a region via discrete, inclusive start and end positions that correspond to indices for characters in the elements String of a Sequence.  Note that the index of the first location is 1, as is typical practice in biology, rather than 0, as is typical practice in computer science.
	class Range : public Location
	{
	public:
        /// Specifies the inclusive starting position of a sequence region. It must be 1 or greater.
		IntProperty start;
        
        /// Specifies the inclusive end position of a sequence region. It must be equal to or greater than the start.
		IntProperty end;

        /// Construct a Range. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < Range > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param start An integer of 1 or greater
        /// @param end An integer equal to or greater than the start
        Range(std::string uri = DEFAULT_NS "/Range/example", int start = 1, int end = 2) : Range(SBOL_RANGE, uri, start, end) {};

        
		virtual ~Range() {};
        
	protected:
        Range(sbol_type type, std::string uri, int start, int end) :
            Location(type, uri),
            start(SBOL_START, this, start),
            end(SBOL_END, this, end)
            {
            };
	};

    /// The Cut class specifies a location between two coordinates of a Sequence's elements.     class Cut : public Location
    class Cut : public Location
    {
    public:
        /// This property specifies the location between this nucleotide coordinate (or other sequence element) and the nucleotide coordinate immediately following it. When equal to zero, the specified region is immediately before the first nucleotide or character in the elements
        IntProperty at;
        
        /// Construct a Cut. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < Cut > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        /// @param at An integer of 0 or greater
        Cut(std::string uri = DEFAULT_NS "/Cut/example", int at = 0) : Cut(SBOL_CUT, uri, at) {};
        
        virtual ~Cut() {};
        
    protected:
        Cut(sbol_type type, std::string uri, int at) :
            Location(type, uri),
            at(SBOL_AT, this, at)
        {
        };

    };

    /// the GenericLocation class is included as a starting point for specifying regions on Sequence objects with encoding properties other than IUPAC and potentially nonlinear structure. This class can also be used to set the orientation of a SequenceAnnotation and any associated Component when their parent ComponentDefinition is a partial design that lacks a Sequence.
    class GenericLocation : public Location
    {
    public:
        /// Construct a GenericLocation. If operating in SBOL-compliant mode, use SequenceAnnotation::locations.create < GenericLocation > instead.
        /// @param uri If operating in open-world mode, this should be a full URI including a scheme, namespace, and identifier.  If SBOLCompliance configuration is enabled, then this argument is simply the displayId for the new object and a full URI will automatically be constructed.
        GenericLocation(std::string uri = DEFAULT_NS "/GenericLocation/example") : GenericLocation(SBOL_GENERIC_LOCATION, uri) {};
        
        virtual ~GenericLocation() {};
        
    protected:
        GenericLocation(sbol_type type, std::string uri) :
            Location(type, uri)
        {
        };
        
    };

}



#endif