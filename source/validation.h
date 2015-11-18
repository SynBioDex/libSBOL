#include <vector>

namespace sbol
{
	typedef void(*ValidationRule)(void *);
	typedef std::vector<ValidationRule> ValidationRules;
	//typedef std::vector<void(*)(void *)> ValidationRules;
	
	void validation_rule_10202(void *sbol_obj);
};
