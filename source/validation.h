#ifndef VALIDATION_RULE_INCLUDED
#define VALIDATION_RULE_INCLUDED

#include <vector>

typedef void(*ValidationRule)(void *, void *);  // This defines the signature for validation rules.  The first argument is an SBOLObject, and the second argument is arbitrary data passed through to the handler function for validation
typedef std::vector<ValidationRule> ValidationRules;

namespace sbol
{
    std::string getCompliantURI(std::string uri_prefix, std::string display_id, std::string sbol_class_name, std::string version);
   
    std::string getClassName(std::string type);

    
    /* These validation rules are explicitly defined in the SBOL 2.0 specification document */
	void sbol_rule_10202(void *sbol_obj, void *arg);

	/* These validation rules are internal to libSBOL */
	void libsbol_rule_1(void *sbol_obj, void *arg);

    //  The following class is an experimental wrapper class for a validation callback function
    //  See http://stackoverflow.com/questions/879408/c-function-wrapper-that-behaves-just-like-the-function-itself
    //
    //    class _ValidationRule
    //    {
    //    private:
    //        void (*validation_rule)(void *, void*);
    //    public:
    //        _ValidationRule(void (*validation_rule_arg)(void*, void*)) :
    //            validation_rule(validation_rule_arg)
    //        {
    //        };
    //        ~_ValidationRule();
    //    };
};

#endif