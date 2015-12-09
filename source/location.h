#ifndef LOCATION_INCLUDED
#define LOCATION_INCLUDED

#include "identified.h"

namespace sbol
{
	class Location : public Identified
	{
	public:
		URIProperty orientation;

	protected:
		Location(sbol_type type, std::string uri_prefix, std::string id) :
			Identified(type, uri_prefix, id, "", "", ""),
			orientation(SBOL_ORIENTATION, this)
			{
			}
	};

	class Range : public Location
	{
	public:
		IntProperty start;
		IntProperty end;

		Range(std::string uri_prefix = SBOL_URI "/Range", std::string id = "Example", int start = 1, int end = 1) :
			Range(SBOL_RANGE, uri_prefix, id, start, end)
			{
			}
		~Range() {};
	protected:
		Range(sbol_type type, std::string uri_prefix, std::string id, int start, int end) :
			Location(type, uri_prefix, id),
			start(SBOL_START, this, start),
			end(SBOL_END, this, end)
			{
			}	
	};

}

#endif