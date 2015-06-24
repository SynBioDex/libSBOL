#include "componentdefinition.h"

using namespace std;
using namespace sbol;

ComponentDefinition::ComponentDefinition(std::string uri_prefix, std::string display_id)
{
	identity.set(uri_prefix + "/" + display_id + "/1.0.0");
	persistentIdentity.set(uri_prefix + "/" + display_id + "/1.0.0");
	displayID.set(display_id);
	name.set("");
	description.set("");
}