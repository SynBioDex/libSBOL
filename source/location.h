#ifndef LOCATION_INCLUDED
#define LOCATION_INCLUDED

#include "identified.h"

namespace sbol
{
    /// The Location class specifies the strand orientation of a Component and can be further extended by the Range, Cut, and GenericLocation classes.
	class Location : public Identified
	{
	public:
		URIProperty orientation;

	// A public constructor is required so objects can be auto created by the SBOLObject.OwnedObjects.create(...) method
        Location(sbol_type type = SBOL_LOCATION, std::string uri = DEFAULT_NS "/Location/example") :
			Identified(type, uri),
			orientation(SBOL_ORIENTATION, this, SBOL_INLINE)
			{
			}
        Location(sbol_type, std::string uri_prefix, std::string display_id, std::string version) :
            Identified(type, uri_prefix, display_id, version),
            orientation(SBOL_ORIENTATION, this, SBOL_INLINE)
            {
            }
    };

    /// A Range object specifies a region via discrete, inclusive start and end positions that correspond to indices for characters in the elements String of a Sequence.  Note that the index of the first location is 1, as is typical practice in biology, rather than 0, as is typical practice in computer science.
	class Range : public Location
	{
	public:
		IntProperty start;
		IntProperty end;

        Range(std::string uri = DEFAULT_NS "/Range/example", int start = 1, int end = 2) : Range(SBOL_RANGE, uri, start, end) {};

        Range(std::string uri_prefix, std::string display_id, std::string version, int start, int end) : Range(SBOL_RANGE, uri_prefix, display_id, version, start, end) {};
        
		~Range() {};
        
	protected:
        Range(sbol_type type, std::string uri, int start, int end) :
            Location(type, uri),
            start(SBOL_START, this, start),
            end(SBOL_END, this, end)
            {
            };
        Range(sbol_type type, std::string uri_prefix, std::string display_id, std::string version, int start, int end) :
			Location(type, uri_prefix, display_id, version),
			start(SBOL_START, this, start),
			end(SBOL_END, this, end)
			{
            };
	};

};




#endif