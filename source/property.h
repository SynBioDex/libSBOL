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
#define SBOL_DOCUMENT SBOL_URI "#Document"
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
#define SBOL_SEQUENCE_CONSTRAINTS SBOL_URI "#sequenceConstraints"
#define SBOL_SUBJECT SBOL_URI "#subject"
#define SBOL_OBJECT SBOL_URI "#object"
#define SBOL_RESTRICTION SBOL_URI "#restriction"

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

	template <class LiteralType>
	Property<LiteralType>::~Property()
	{
	};

	class URIProperty : public Property<std::string>
	{
	public:
		URIProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "", ValidationRules rules = {}) :
			Property(type_uri, property_owner, "<" + initial_value + ">", rules)
		{
		}
	};

	class TextProperty : public Property<std::string>
	{
	public:
		TextProperty(sbol_type type_uri, void *property_owner, std::string initial_value = "", ValidationRules rules = {}) :
			Property(type_uri, property_owner, "\"" + initial_value + "\"", rules = {})
		{
		}
	};

	class IntProperty : public Property<int>
	{
	public:
		IntProperty(sbol_type type_uri, void *property_owner, int initial_value = 0, ValidationRules rules = {}) :
			Property(type_uri, property_owner, initial_value, rules = {})
		{
		}
	};


	/* Constructor for string Property */
	template <class LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(initial_value);
			sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

	/* Constructor for int Property */
	template <class LiteralType>
	Property<LiteralType>::Property(sbol_type type_uri, void *property_owner, int initial_value, ValidationRules rules) : Property(type_uri, property_owner, rules)
	{
		// Register Property in owner Object
		if (sbol_owner != NULL)
		{
			std::vector<std::string> property_store;
			property_store.push_back(std::to_string(initial_value));
			sbol_owner->properties.insert({ type_uri, property_store });
		}
	}

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
		if (sbol_owner)
		{
			if (sbol_owner->properties.find(type) == sbol_owner->properties.end()) 
			{
				// not found
				return "";
			}
			else 
			{
				// found
				std::string value = sbol_owner->properties[type].front();
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
			std::string current_value = sbol_owner->properties[type][0];
			if (current_value[0] == '<')  //  this property is a uri
			{
				sbol_owner->properties[type][0] = "<" + new_value + ">";
			}
			else if (current_value[0] == '"') // this property is a literal
			{
				sbol_owner->properties[type][0] = "\"" + new_value + "\"";
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
			sbol_owner->properties[type][0] = "\"" + std::to_string(new_value) + "\"";
		}
		validate((void *)&new_value);  //  Call validation rules associated with this Property
	};

	template <class LiteralType>
	void Property<LiteralType>::write()
	{
		std::string subject = (*sbol_owner).identity.get();
		sbol_type predicate = type;
		std::string object = sbol_owner->properties[type].front();

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
			std::string current_value = sbol_owner->properties[type][0];
			if (current_value[0] == '<')  //  this property is a uri
			{
				sbol_owner->properties[type].push_back("<" + new_value + ">");
			}
			else if (current_value[0] == '"') // this property is a literal
			{
				sbol_owner->properties[type].push_back("\"" + new_value + "\"");
			}
			validate((void *)&new_value);  //  Call validation rules associated with this Property
		}
	};

	/* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	template <class SBOLClass>
	class OwnedObject : public Property<SBOLClass>
	{

	public:
		OwnedObject(sbol_type type_uri = UNDEFINED, SBOLObject *property_owner = NULL);
		OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object);

		void add(SBOLClass& sbol_obj);
		SBOLClass& get(std::string object_id);
	};

	template <class SBOLClass >
	OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, SBOLObject *property_owner) : 
		Property(type_uri, property_owner)
		{
			// Register Property in owner Object
			if (sbol_owner != NULL)
			{
				std::vector<sbol::SBOLObject*> object_store;
				sbol_owner->owned_objects.insert({ type_uri, object_store });
			}
		};

	template <class SBOLClass>
	OwnedObject< SBOLClass >::OwnedObject(sbol_type type_uri, void *property_owner, SBOLObject& first_object)
	{
	};


	template < class SBOLClass>
	void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
	{
		sbol_owner->owned_objects[type].push_back((SBOLObject *)&sbol_obj);
	};

	template <class SBOLClass>
	SBOLClass& OwnedObject<SBOLClass>::get(std::string object_id)
	{
	};


	//template < class SBOLClass >
	//void OwnedObject<SBOLClass>::add(SBOLClass& sbol_obj)
	//{
	//	sbol_owner->owned_objects[type].push_back((SBOLObject *)&sbol_obj);
	//};

	//template < class SBOLClass >
	//std::vector<SBOLClass> OwnedObject<SBOLClass>::get()
	//{
	//	std::vector<SBOLClass> vector_copy;
	//	for (auto o = sbol_owner->owned_objects[type].begin(); o != sbol_owner->owned_objects[type].end(); o++)
	//	{
	//		vector_copy.push_back(**o);
	//	}
	//	return vector_copy;
	//};



	///* Corresponding to black diamonds in UML diagrams.  Creates a composite out of two or more classes */
	//template <class SBOLClass>
	//class OwnedObjects
	//{
	//protected:
	//	sbol_type type;
	//	SBOLObject *sbol_owner;  // pointer to the owning SBOLObject to which this Property belongs
	//	
	//public:
	//	OwnedObjects<SBOLClass>() :
	//		type(UNDEFINED),
	//		sbol_owner(NULL)
	//	{
	//	}
	//	OwnedObjects(sbol_type type_uri, void *property_owner);
	//	OwnedObjects(sbol_type type_uri, void *property_owner, SBOLObject& first_object);
	//	std::vector<SBOLClass> get();
	//	void add(SBOLClass& sbol_obj);
	//	void remove(std::string uri);
	//};

	//template <class SBOLClass >
	//OwnedObjects< SBOLClass >::OwnedObjects(sbol_type type_uri, void *property_owner)
	//{
	//	type = type_uri;
	//	sbol_owner = ((SBOLObject *)property_owner);

	//	// Register Property in owner Object
	//	if (sbol_owner != NULL)
	//	{
	//		std::vector<sbol::SBOLObject*> object_store;
	//		sbol_owner->owned_objects.insert({ type_uri, object_store });
	//	}
	//};

	//template <class SBOLClass>
	//OwnedObjects< SBOLClass >::OwnedObjects(sbol_type type_uri, void *property_owner, SBOLObject& first_object)
	//{
	//};

	//template < class SBOLClass >
	//void OwnedObjects<SBOLClass>::add(SBOLClass& sbol_obj)
	//{
	//	sbol_owner->owned_objects[type].push_back((SBOLObject *)&sbol_obj);
	//};

	//template < class SBOLClass >
	//std::vector<SBOLClass> OwnedObjects<SBOLClass>::get()
	//{
	//	std::vector<SBOLClass> vector_copy;
	//	for (auto o = sbol_owner->owned_objects[type].begin(); o != sbol_owner->owned_objects[type].end(); o++)
	//	{
	//		vector_copy.push_back(**o);
	//	}
	//	return vector_copy;
	//};

	//class ReferencedObjects : public Property<std::string>
	//{
	//public:
	//	ReferencedObjects(sbol_type type_uri, void *property_owner, std::string initial_value) : Property<std::string>::Property(type_uri, property_owner, initial_value)
	//	{
	//	}
	//};

	class ReferencedObject : public URIProperty
	{
		public:
			ReferencedObject(sbol_type type_uri, void *property_owner, std::string initial_value, ValidationRules rules = {}) : URIProperty(type_uri, property_owner, initial_value, rules)
			{
			}
	};

	template <class PropertyType>
	class List : public PropertyType 
	{

	public:
		List(sbol_type type_uri, SBOLObject *property_owner, std::string initial_value) :
			PropertyType(type_uri, property_owner, initial_value)
		{
		}
		List(sbol_type type_uri, SBOLObject *property_owner) :
			PropertyType(type_uri, property_owner)
		{
		}
		std::string get(int index);
		void remove(int index);
		std::vector<PropertyType> copy();
		void remove(std::string uri);
	};

	template <class PropertyType>
	std::string List<PropertyType>::get(int index)
	{
		if (sbol_owner)
		{
			if (sbol_owner->properties.find(type) == sbol_owner->properties.end())
			{
				// TODO: trigger exception
				// not found
				return "";
			}
			else
			{
				// found
				std::string current_value = sbol_owner->properties[type].at(index);
				current_value = current_value.substr(1, current_value.length() - 2);
				return current_value;
			}
		}
		else
		{
			return "";
		}
	};

	template < class PropertyType >
	std::vector<PropertyType> List<PropertyType>::copy()
	{
		std::vector<PropertyType> vector_copy;
		for (auto o = sbol_owner->owned_objects[type].begin(); o != sbol_owner->owned_objects[type].end(); o++)
		{
			vector_copy.push_back(**o);
		}
		return vector_copy;
	};



	template <class PropertyType>
	void List<PropertyType>::remove(int index)
	{
		if (sbol_owner)
		{
			sbol_owner->properties[type].erase( sbol_owner->properties[type].begin() + index - 1);
		}
	};

	

	/* All SBOLObjects have a pointer back to their Document.  This requires forward declaration of SBOL Document class here */
	class Document;

	//typedef std::map<sbol_type, PropertyBase> PropertyStore;

	//extern PropertyStore* global_property_buffer;
	

	class SBOLObject
	{
	friend class Document;
	

	protected:
		//protected:
		//	sbol_type type;

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
	};
}

// This is a wrapper function for constructors.  This allows us to construct an SBOL object using a function pointer (direct pointers to constructors are not supported by C++)
template <class SBOLClass>
sbol::SBOLObject& create()
{
	// Construct an SBOLObject with emplacement
	void* mem = malloc(sizeof(SBOLClass));
	SBOLClass* a = new (mem) SBOLClass;
	return (SBOLObject&)*a;
};






#endif 
