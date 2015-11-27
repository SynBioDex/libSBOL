#include <vector>

namespace sbol
{
	typedef void(*ValidationRule)(void *, void *);  // This defines the signature for validation rules.  The first argument is an SBOLObject, and the second argument is arbitrary data passed through to the handler function for validation
	typedef std::vector<ValidationRule> ValidationRules;
	
	void validation_rule_10202(void *sbol_obj, void *arg);
};
