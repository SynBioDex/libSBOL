%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    #include "constants.h"
    #include "validation.h"
    #include "sbolerror.h"
    #include "property.h"
    #include "properties.h"
    #include "object.h"
    #include "identified.h"
    #include "toplevel.h"
    #include "generictoplevel.h"
    #include "sequenceannotation.h"
    #include "component.h"
    #include "componentdefinition.h"
    #include "sequence.h"
    #include "document.h"
    #include "sequenceannotationextension.h"
    #include "interaction.h"
    #include "participation.h"
    #include "location.h"
    #include "sequenceconstraint.h"
    #include "moduledefinition.h"
    #include "module.h"
    #include "mapsto.h"
    #include "model.h"
    #include "sbol.h"

    #include <vector>
    #include <map>
    #include <unordered_map>

    using namespace sbol;
    using namespace std;
    
%}



#ifdef SWIGWIN
    %include <windows.i>
#endif

// tell SWIG how to free strings
%typemap(newfree) char* "free($1);";


// Instantiate STL templates

%include "std_string.i"


%include "std_vector.i"

namespace std {
    %template(_IntVector) vector<int>;
    %template(_StringVector) vector<string>;
    %template(_SBOLObjectVector) vector<sbol::SBOLObject*>;
}

//%include "std_unordered_map.i"
//namespace std {
//    %template(_UnorderedMapVector) unordered_map<string, string >;
//    //%template(_UnorderedMapOfStringVector) unordered_map<string, string>;
//}


%include "std_map.i"
namespace std {
    %template(_MapVector) map<string, string >;
    %template(_MapOfStringVector) map<string, vector<string> >;
    %template(_MapOfSBOLObject) map<string, vector< sbol::SBOLObject* > >;

}

//%include "std_function.i"
//namespace std {
//    %template(_ValidationRule) function<void(void *, void *)>;
//    %template(_ValidationRules) vector<function<void(void *, void *)>>;}
//}

//typedef const void(*sbol::ValidationRule)(void *, void *);
// %template(_ValidationRules) std::vector<sbol::ValidationRule>;

// Instantiate libSBOL templates
%include "constants.h"

typedef std::string sbol::sbol_type;


//%ignore sbol::Property(std::string , void *, std::string , std::vector< std::string> );
//%ignore sbol::Property(std::string , void *, int initial_value, std::vector< (sbol::*)(void *)(void *) > );
//%ignore sbol::Property(std::string , void *, std::vector< (sbol::*)(void *)(void *) > );


%include "property.h"


namespace sbol
{
    
    %template(_StringProperty) Property<std::string>;  // These template instantiations are private, hence the underscore...
    %template(_IntProperty) Property<int>;             // They are required to have names in order to derive subclasses
}
%include "properties.h"

%ignore sbol::SBOLObject::getTypeURI;
%include "object.h"
%ignore sbol::SBOLObject::getTypeURI;



#%include "identified.h"
#%include "toplevel.h"
#%include "generictoplevel.h"

//%include "validation.h"
//namespace std
//{
////    typedef void(*ValidationRule)(void *, void *);  // This defines the signature for validation rules.  The first argument is an SBOLObject, and the second argument is arbitrary data passed through to the handler function for validation
////    
//    
////    typedef std::vector<ValidationRule> ValidationRules;
//    //%template(_ValidationRules) vector< void(*)>;  // This compiles, but doesn't appear to wrap anything useful
//
//}
//


//%include "object.h"
//%template(get) sbol::TextProperty::get<std::string>;
//%template(set) sbol::TextProperty::set<std::string>;

//%template(get) sbol::URIProperty::get<std::string>;
//%template(set) sbol::URIProperty::set<std::string>;





// tell SWIG to free the strings returned
// from these functions immediately
// (after copying their values into Python)
// %newobject getDNASequenceNucleotides;

// tell SWIG that these functions delete
// their first argument, and it doesnt need
// to be garbage collected
// (SBOL objects are managed manually anyway,
//  so this just makes doubly sure to avoid segfaults
//  from freeing twice)
//%delobject deleteDNASequence;

// functions returing pointers to new objects
//Document* createDocument();


// functions that delete objects
//void deleteDocument(Document* doc);

// funtions returning strings to be newfree()d
//#char* getDNASequenceNucleotides(const DNASequence* seq);

// functions returning pointers to existing objects
//#DNASequence* getDNASequence(Document* doc, const char* uri);

// functions returning ints
//int getNumSBOLObjects(Document* doc);

// functions returning void
//void setDNASequenceNucleotides(DNASequence* seq, const char* nucleotides);

