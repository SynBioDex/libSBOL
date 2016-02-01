#ifndef PROPERTY_INCLUDED
#define PROPERTY_INCLUDED

#include "sbolerror.h"
#include "validation.h"

#include <raptor2.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>

// The URIs defined here determine the appearance of serialized RDF/XML nodes.  Change these URIs to change the appearance of an SBOL class or property name
#define SBOL_URI "http://sbols.org/v2"
#define RDF_URI "http://www.w3.org/1999/02/22-rdf-syntax-ns#" 
#define PURL_URI "http://purl.org/dc/terms/"
#define PROV_URI "http://www.w3.org/ns/prov"

// rdf nodes used in SBOL
#define NODENAME_ABOUT    "rdf:about"    ///< URI of a node representing an SBOLObject.
#define NODENAME_RESOURCE "rdf:resource" ///< URI of a node referencing an SBOLObject somewhere else.


/* URIs for SBOL objects */
#define SBOL_IDENTIFIED SBOL_URI "#Identified"
#define SBOL_DOCUMENTED SBOL_URI "#Documented"
#define SBOL_TOP_LEVEL SBOL_URI "#TopLevel"
#define SBOL_GENERIC_TOP_LEVEL SBOL_URI "#GenericTopLevel"
#define SBOL_SEQUENCE_ANNOTATION SBOL_URI "#SequenceAnnotation"
#define SBOL_COMPONENT SBOL_URI "#Component"
#define SBOL_FUNCTIONAL_COMPONENT SBOL_URI "#FunctionalComponent"
#define SBOL_COMPONENT_DEFINITION SBOL_URI "#ComponentDefinition"
#define SBOL_SEQUENCE SBOL_URI "#Sequence"
#define SBOL_MODULE_DEFINITION SBOL_URI "#ModuleDefinition"
#define SBOL_MODULE SBOL_URI "#Module"
#define SBOL_MODEL SBOL_URI "#Model"
#define SBOL_MAPS_TO SBOL_URI "#MapsTo"
#define SBOL_INTERACTION SBOL_URI "#Interaction"
#define SBOL_PARTICIPATION SBOL_URI "#Participation"
#define SBOL_SEQUENCE_CONSTRAINT SBOL_URI "#SequenceConstraint"
#define SBOL_LOCATION SBOL_URI "#Location"
#define SBOL_DOCUMENT SBOL_URI "#Document"
#define SBOL_RANGE SBOL_URI "#Range"
#define UNDEFINED SBOL_URI "#Undefined"

/* URIs for SBOL Properties */
#define SBOL_IDENTITY SBOL_URI "#identity"
#define SBOL_PERSISTENT_IDENTITY SBOL_URI "#persistentIdentity"
#define SBOL_VERSION SBOL_URI "#version"
#define SBOL_DISPLAY_ID  SBOL_URI "#displayId"
#define SBOL_NAME PURL_URI "#title"
#define SBOL_DESCRIPTION PURL_URI "#description"
#define SBOL_TYPES SBOL_URI "#type"
#define SBOL_START SBOL_URI "#start"
#define SBOL_END SBOL_URI "#end"
#define SBOL_SEQUENCE_ANNOTATIONS SBOL_URI "#sequenceAnnotation"
#define SBOL_COMPONENTS SBOL_URI "#component"
#define SBOL_ROLES SBOL_URI "#role"
#define SBOL_ELEMENTS SBOL_URI "#elements"
#define SBOL_ENCODING SBOL_URI "#encoding"
#define SBOL_SEQUENCE_PROPERTY SBOL_URI "#sequence"
#define SBOL_WAS_DERIVED_FROM PROV_URI "#wasDerivedFrom"
#define SBOL_DEFINITION SBOL_URI "#definition"
#define SBOL_ACCESS SBOL_URI "#access"
#define SBOL_DIRECTION SBOL_URI "#direction"
#define SBOL_MODELS SBOL_URI "#model"
#define SBOL_MODULES SBOL_URI "#module"
#define SBOL_FUNCTIONAL_COMPONENTS SBOL_URI "#functionalComponent"
#define SBOL_INTERACTIONS SBOL_URI "#interaction"
#define SBOL_MAPS_TOS SBOL_URI "#mapsTo"
#define SBOL_PARTICIPATIONS SBOL_URI "#participation"
#define SBOL_PARTICIPANT SBOL_URI "#participant"
#define SBOL_LOCAL SBOL_URI "#local"
#define SBOL_REMOTE SBOL_URI "#remote"
#define SBOL_REFINEMENT SBOL_URI "#refinement"
#define SBOL_SOURCE SBOL_URI "#source"
#define SBOL_LANGUAGE SBOL_URI "#language"
#define SBOL_FRAMEWORK SBOL_URI "#framework"
#define SBOL_SEQUENCE_CONSTRAINTS SBOL_URI "#sequenceConstraint"
#define SBOL_SUBJECT SBOL_URI "#subject"
#define SBOL_OBJECT SBOL_URI "#object"
#define SBOL_RESTRICTION SBOL_URI "#restriction"
#define SBOL_ORIENTATION SBOL_URI "#orientation"
#define SBOL_LOCATIONS SBOL_URI "#location"

/* SBOL internal ontologies */
#define SBOL_ACCESS_PRIVATE SBOL_URI "#private"
#define SBOL_ACCESS_PUBLIC SBOL_URI "#public"
#define SBOL_DIRECTION_IN SBOL_URI "#in"
#define SBOL_DIRECTION_OUT SBOL_URI "#out"
#define SBOL_DIRECTION_IN_OUT SBOL_URI "#inout"
#define SBOL_DIRECTION_NONE SBOL_URI "#none"
#define SBOL_PRECEDES SBOL_URI "#precedes"
#define SBOL_SAME_ORIENTATION_AS "#sameOrientationAs"
#define SBOL_OPPOSITE_ORIENTATION_AS "#oppositeOrientationAs"
#define SBOL_ENCODING_IUPAC "www.chem.qmul.ac.uk/iubmb/misc/naseq.html"
#define SBOL_ENCODING_IUPAC_PROTEIN "www.chem.qmul.ac.uk/iupac/AminoAcid/"
#define SBOL_ENCODING_SMILES "www.opensmiles.org/opensmiles.html"
#define SBOL_INLINE SBOL_URI "#inline"
#define SBOL_REVERSE_COMPLEMENT SBOL_URI "#reverseComplement"

/* Systems Biology Ontology */
/* Interaction.roles */
#define SBO "http://identifiers.org/biomodels.sbo/SBO:"
#define SBO_INHIBITION SBO "0000169"
#define SBO_GENETIC_PRODUCTION SBO "0000170"
#define SBO_STIMULATION SBO "0000589"
#define SBO_NONCOVALENT_BINDING SBO "0000177"
/* Participant.roles */
#define SBO_INHIBITOR SBO "0000020"
#define SBO_STIMULATOR SBO "0000459"
#define SBO_REACTANT SBO "0000010"
#define SBO_PRODUCT SBO "0000011"
#define SBO_LIGAND SBO "0000280"
#define SBOL_NONCOVALENT_COMPLEX SBO "0000253"

/* URIs for common Sequence Ontology terms */
#define SO_UNDEFINED "SO_0000001"

/* Modeling frameworks */
#define SBML "http://identifiers.org/edam/format_2585"
#define CELLML "http://identifiers.org/edam/format_3240"
#define BIOPAX "http://identifiers.org/edam/format_3156"


namespace sbol
{
	/* Contains URI strings used for constructing RDF triples */
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

//	/* Constructor for string Property */
//	template <class LiteralType>
//	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
//	{
//		// Register Property in owner Object
//		if (this->sbol_owner != NULL)
//		{
//			std::vector<std::string> property_store;
//			property_store.push_back(initial_value);
//			this->sbol_owner->properties.insert({ type_uri, property_store });
//		}
//	}
//
//	/* Constructor for int Property */
//	template <class LiteralType>
//	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
//	{
//		// Register Property in owner Object
//		if (this->sbol_owner != NULL)
//		{
//			std::vector<std::string> property_store;
//			property_store.push_back("\"" + std::to_string(initial_value) + "\"");
//			this->sbol_owner->properties.insert({ type_uri, property_store });
//		}
//	}


	//typedef std::map<sbol_type, PropertyBase> PropertyStore;

	//extern PropertyStore* global_property_buffer;

    template <class LiteralType>
    Property<LiteralType>::~Property()
    {
    };
    
    
    template <class LiteralType>
    sbol_type Property<LiteralType>::getTypeURI()
    {
        return type;
    }
    
    template <class LiteralType>
    SBOLObject& Property<LiteralType>::getOwner()
    {
        return *sbol_owner;
    }
    
    template <class LiteralType>
    std::string Property<LiteralType>::get()
    {
        if (this->sbol_owner)
        {
            if (this->sbol_owner->properties.find(type) == this->sbol_owner->properties.end())
            {
                // not found
                return "";
            }
            else
            {
                // found
                std::string value = this->sbol_owner->properties[type].front();
                value = value.substr(1, value.length() - 2);  // Strips angle brackets from URIs and quotes from literals
                return value;
            }
        }	else
        {
            return "";
        }
    };
    
    template <class LiteralType>
    void Property<LiteralType>::set(std::string new_value)
    {
        if (sbol_owner)
        {
            //sbol_owner->properties[type].push_back( new_value );
            std::string current_value = this->sbol_owner->properties[type][0];
            if (current_value[0] == '<')  //  this property is a uri
            {
                this->sbol_owner->properties[type][0] = "<" + new_value + ">";
            }
            else if (current_value[0] == '"') // this property is a literal
            {
                this->sbol_owner->properties[type][0] = "\"" + new_value + "\"";
            }
            
        }
        validate((void *)&new_value);
    };
    
    template <class LiteralType>
    void Property<LiteralType>::set(int new_value)
    {
        if (new_value)
        {
            // TODO:  need to convert new_value to string
            this->sbol_owner->properties[type][0] = "\"" + std::to_string(new_value) + "\"";
        }
        validate((void *)&new_value);  //  Call validation rules associated with this Property
    };
    
    template <class LiteralType>
    void Property<LiteralType>::write()
    {
        std::string subject = (*this->sbol_owner).identity.get();
        sbol_type predicate = type;
        std::string object = this->sbol_owner->properties[type].front();
        
        std::cout << "Subject:  " << subject << std::endl;
        std::cout << "Predicate: " << predicate << std::endl;
        std::cout << "Object: "  << std::endl;
    };
    
    template <class LiteralType>
    void Property<LiteralType>::validate(void * arg)
    {
        for (ValidationRules::iterator i_rule = validationRules.begin(); i_rule != validationRules.end(); ++i_rule)
        {
            ValidationRule& validate_fx = *i_rule;
            validate_fx(sbol_owner, arg);
        }
    };
    
    template <class LiteralType>
    void Property<LiteralType>::add(std::string new_value)
    {
        if (sbol_owner)
        {
            std::string current_value = this->sbol_owner->properties[type][0];
            if (current_value[0] == '<')  //  this property is a uri
            {
                this->sbol_owner->properties[type].push_back("<" + new_value + ">");
            }
            else if (current_value[0] == '"') // this property is a literal
            {
                this->sbol_owner->properties[type].push_back("\"" + new_value + "\"");
            }
            validate((void *)&new_value);  //  Call validation rules associated with this Property
        }
    };
    
    
}








#endif
