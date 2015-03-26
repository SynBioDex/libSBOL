#include "documented.h"

#include <string>

namespace sbol 
{
	class TextProperty;
	class SBOLDocument;

	class TopLevel : public Documented
	{
		static const sbol_type type = SBOL_TOP_LEVEL;

	public:
		TopLevel(std::string uri_prefix, std::string display_id) :
			Documented(uri_prefix, display_id)
			{
			}
		void addToDocument(sbol::SBOLDocument&);

	};
}