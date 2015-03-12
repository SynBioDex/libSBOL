#include "documented.h"

#include <string>

namespace sbol 
{
	class TextProperty;
	class SBOLDocument;

	class TopLevel : public Documented
	{

	public:
		TopLevel(std::string uri_prefix, std::string display_id) :
			Documented(uri_prefix, display_id)
			{
			}
		void addToDocument(sbol::SBOLDocument&);

	};
}