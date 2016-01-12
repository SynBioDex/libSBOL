#ifndef LOCATION_INCLUDED
#define LOCATION_INCLUDED

#include "identified.h"

namespace sbol
{
	class Location : public Identified
	{
	public:
		URIProperty orientation;

	// A public constructor is required so objects can be auto created by the SBOLObject.OwnedObjects.create(...) method
		Location(sbol_type type = SBOL_LOCATION, std::string uri_prefix = SBOL_URI "/Location", std::string id = "Example", std::string orientation = SBOL_INLINE) :
			Identified(type, uri_prefix, id, "", "", ""),
			orientation(SBOL_ORIENTATION, this, orientation)
			{
			}
	};

	class Range : public Location
	{
	public:
		IntProperty start;
		IntProperty end;

		Range(std::string uri_prefix = SBOL_URI "/Range", std::string id = "Example", std::string orientation = SBOL_INLINE, int start = 1, int end = 1) :
			Range(SBOL_RANGE, uri_prefix, id, orientation, start, end)
			{
			}
		~Range() {};
	protected:
		Range(sbol_type type, std::string uri_prefix, std::string id, std::string orientation, int start, int end) :
			Location(type, uri_prefix, id, orientation),
			start(SBOL_START, this, start),
			end(SBOL_END, this, end)
			{
			}	
	};

};




#endif