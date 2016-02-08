#ifndef MODULE_INCLUDED
#define MODULE_INCLUDED

#include "identified.h"
#include "mapsto.h"

namespace sbol
{
	class Module : public Identified
	{

	public:
		ReferencedObject definition;
		//List<OwnedObject<MapsTo>> mapsTos;

		Module(std::string uri_prefix = SBOL_URI "/Module", std::string id = "example") :
			Module(SBOL_MODULE, uri_prefix, id)
			{
			}
		~Module();
	protected:
		Module(sbol_type type, std::string uri_prefix, std::string id) :
			Identified(type, uri_prefix, id, "", "", ""),
			definition(SBOL_DEFINITION, this, UNDEFINED)
			//mapsTos(SBOL_MAPS_TO, this)
			{
			}
	};
}

#endif