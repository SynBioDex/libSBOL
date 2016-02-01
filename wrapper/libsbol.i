%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

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

namespace sbol
{
    typedef std::string sbol_type;
}

%include "std_vector.i"

namespace std {
    %template(_IntVector) vector<int>;
    %template(_StringVector) vector<string>;
}

%include "std_unordered_map.i"
namespace std {
    %template(_UnorderedMapVector) unordered_map<string, string >;
    //%template(_UnorderedMapOfStringVector) unordered_map<string, string>;
}


%include "std_map.i"
namespace std {
    %template(_MapVector) map<string, string >;
    %template(_MapOfStringVector) map<string, vector<string> >;
}

//    %template(_UnorderedMapVector) unordered_map<sbol::sbol_type, vector<string> >;
//    %template(_MapVector) map<sbol::sbol_type, vector<string> >;

// Instantiate libSBOL templates
%include "validation.h"
%include "property.h"

namespace sbol
{

    %template(_StringProperty) Property<std::string>;  // These template instantiations are private, hence the underscore...
    %template(_IntProperty) Property<int>;             // They are required to have names in order to derive subclasses

}

%include "properties.h"
%include "object.h"
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

