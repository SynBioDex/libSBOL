#include <vector>

namespace sbol
{
	typedef void(*ValidationRule)(void *, void *);  // This defines the signature for validation rules.  The first argument is an SBOLObject, and the second argument is arbitrary data passed through to the handler function for validation
	typedef std::vector<ValidationRule> ValidationRules;

	/* These validation rules are explicitly defined in the SBOL 2.0 specification document */
	void sbol_rule_10202(void *sbol_obj, void *arg);

	/* These validation rules are internal to libSBOL */
	void libsbol_rule_1(void *sbol_obj, void *arg);
};
