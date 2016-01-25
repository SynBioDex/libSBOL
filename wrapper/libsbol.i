%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    #include "validation.h"
    #include "sbolerror.h"
    #include "property.h"
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

    using namespace sbol;

%}
%include "std_string.i"
%include "std_vector.i"



#ifdef SWIGWIN
    %include <windows.i>
#endif

// tell SWIG how to free strings
%typemap(newfree) char* "free($1);";

namespace sbol
{
    typedef std::string sbol_type;
    
    /* All SBOLProperties have a pointer back to the object which the property belongs to.
     This requires forward declaration of the SBOLObject class */
    class SBOLObject;
    
    template <class LiteralType>
    class Property
    {
        
    protected:
        sbol_type type;
        SBOLObject *sbol_owner;  // back pointer to the SBOLObject to which this Property belongs
        ValidationRules validationRules;
        
    public:
        Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules = {} );
        Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules rules = {} );
        
        Property(sbol_type type_uri = UNDEFINED, void *property_owner = NULL, ValidationRules rules = {} ) :
        type(type_uri),
        sbol_owner((SBOLObject *)property_owner),
        validationRules(rules)
        {
        }
        ~Property();
        virtual sbol_type getTypeURI();
        virtual SBOLObject& getOwner();
        virtual std::string get();
        void add(std::string new_value);
        
        virtual void set(std::string new_value);
        virtual void set(int new_value);
        virtual void write();
        void validate(void * arg = NULL);
    };
    
    /* Instantiate a few different versions of the template */
    %template(IntProperty) Property<int>;
    %template(TextProperty) Property<std::string>;
    
    
    class SBOLObject
    {
        friend class Document;
    public:
        Document *doc = NULL;
    
        //std::unordered_map<sbol::sbol_type, sbol::PropertyBase> properties;
        std::unordered_map<sbol::sbol_type, std::vector< std::string > > properties;
        std::unordered_map<sbol::sbol_type, std::vector< std::string > > list_properties;
        std::map<sbol::sbol_type, std::vector< sbol::SBOLObject* > > owned_objects;
    
        SBOLObject(sbol_type type = UNDEFINED, std::string uri_prefix = SBOL_URI, std::string id = "example") :
            type(type),
            identity(URIProperty(SBOL_IDENTITY, this, uri_prefix + "/" + id, { sbol_rule_10202 }))
            {
            }
        ~SBOLObject();
        sbol_type type;
        URIProperty identity;
    
        virtual sbol_type getTypeURI();
        void serialize(raptor_serializer* sbol_serializer, raptor_world *sbol_world = NULL);
        std::string nest(std::string& rdfxml_buffer);
    };
}








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

