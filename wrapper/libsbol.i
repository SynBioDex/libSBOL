%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    //  Headers are listed in strict order of dependency
    #include "constants.h"
    #include "validation.h"
    #include "sbolerror.h"
    #include "property.h"
    #include "properties.h"
    #include "object.h"
    #include "identified.h"
    #include "toplevel.h"
    #include "generictoplevel.h"
    #include "location.h"
    #include "sequenceconstraint.h"
    #include "sequenceannotation.h"
    #include "mapsto.h"
    #include "component.h"
    #include "componentdefinition.h"
    #include "sequence.h"
    #include "participation.h"
    #include "interaction.h"
    #include "module.h"
    #include "model.h"
    #include "moduledefinition.h"
    #include "document.h"
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

%include "validation.h"

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


%exception next
{
	try
	{
		$action
	}
	catch(SBOLErrorCode exception)
	{
		PyErr_SetNone(PyExc_StopIteration);
		return NULL;
	}
}

%extend sbol::OwnedObject 
{
	SBOLClass& __getitem__(const int nIndex)
	{
		return $self->operator[](nIndex);
	}

	SBOLClass& __getitem__(const std::string uri)
	{
		return $self->operator[](uri);
	}

	OwnedObject<SBOLClass>* __iter__()
	{
		$self->python_iter = OwnedObject<SBOLClass>::iterator($self->begin());
		return $self;
	}

	SBOLClass* next()
	{
		if ($self->python_iter != $self->end())
		{
			SBOLObject* obj = *$self->python_iter;
			$self->python_iter++;
			if ($self->python_iter == $self->end())
			{
				PyErr_SetNone(PyExc_StopIteration);
			}
			return (SBOLClass*)obj;
		}
		throw (END_OF_LIST);
		return NULL;
	}
};



%include "object.h"

//%pythoncode
//%{
//    import sys
//    from cStringIO import StringIO
//    def capture_stdout(fn, *args, **kwargs):
//      backup = sys.stdout
//      sys.stdout = StringIO()
//      fn(*args, **kwargs)
//      output = sys.stdout.getvalue()
 //      sys.stdout.close()
//      sys.stdout = backup
//      return output
//%}


/* Bind C++ iterator --> Python list */
//%typemap(out) sbol::OwnedObject<sbol::SequenceAnnotation>* 
//{
//	sbol::OwnedObject<sbol::SequenceAnnotation>* container = $1;
//	sbol::SequenceAnnotation* owned_obj = (SequenceAnnotation*)*container->python_iter;
//	PyObject* iter = SWIG_NewPointerObj(SWIG_as_voidptr(owned_obj), $descriptor(sbol::SequenceAnnotation*), 0 |  0 );
//	iter = PyObject_GetIter(iter);
//    $result  = iter;
//}



/* Convert C++ vector of Locations --> Python list */
%typemap(out) std::vector<sbol::Location*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::Location*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
}

/* Convert C++ vector of mapsTos --> Python list */
%typemap(out) std::vector<sbol::mapsTo*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::mapsTo*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
}

/* Convert C++ vector of SequenceConstraints --> Python list */
%typemap(out) std::vector<sbol::SequenceConstraint*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::SequenceConstraint*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
}

/* Convert C++ vector of SequenceAnnotations --> Python list */
%typemap(out) std::vector<sbol::SequenceAnnotation*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::SequenceAnnotation*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
}

/* Convert C++ vector of Participations --> Python list */
%typemap(out) std::vector<sbol::Participation*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::Participation*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
    
}/* Convert C++ vector of Modules --> Python list */
%typemap(out) std::vector<sbol::Module*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::Module*), 0 |  0 );
        PyList_Append(list, elem);
        
    }
    $result  = list;
}

/* Convert C++ vector of Interactions --> Python list */
%typemap(out) std::vector<sbol::Interaction*> {
    int len = $1.size();
    PyObject* list = PyList_New(0);
    for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
    {
        PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::Interaction*), 0 |  0 );
        PyList_Append(list, elem);
    }
    $result  = list;
}


%include "identified.h"

%include "toplevel.h"

%include "generictoplevel.h"

// Declare instances of the member templates first, then declare instances of the class templates.

%include "location.h"
%template(locationProperty) sbol::Property<sbol::Location>;
//%template(addLocation) sbol::OwnedObject::add<Location>;
%template(_VectorOfLocations) std::vector<sbol::Location>;
%template(ownedLocation) sbol::OwnedObject<sbol::Location>;
%template(listOfOwnedLocations) sbol::List<sbol::OwnedObject<sbol::Location>>;
%include "sequenceannotation.h"

%include "mapsto.h"
%template(_VectorOfMapsTos) std::vector<sbol::MapsTo>;
%template(mapsToProperty) sbol::Property<sbol::MapsTo>;
%template(ownedMapsTo) sbol::OwnedObject<sbol::MapsTo>;
%template(listOfOwnedMapsTos) sbol::List<sbol::OwnedObject<sbol::MapsTo>>;
%include "component.h"

%include "sequenceconstraint.h"
%template(_VectorOfSequenceConstraints) std::vector<sbol::SequenceConstraint>;
%template(sequenceConstraintProperty) sbol::Property<sbol::SequenceConstraint>;
%template(ownedSequenceConstraint) sbol::OwnedObject<sbol::SequenceConstraint>;
%template(listOfOwnedSequenceConstraints) sbol::List<sbol::OwnedObject<sbol::SequenceConstraint>>;

%template(_VectorOfSequenceAnnotations) std::vector<sbol::SequenceAnnotation>;
%template(sequenceAnnotationProperty) sbol::Property<sbol::SequenceAnnotation>;
%template(ownedSequenceAnnotation) sbol::OwnedObject<sbol::SequenceAnnotation>;
%template(listOfOwnedSequenceAnnotations) sbol::List<sbol::OwnedObject<sbol::SequenceAnnotation>>;
%include "componentdefinition.h"

%include "sequence.h"

%template(listOfURIs) sbol::List<sbol::URIProperty>;
%include "participation.h"

%template(participationProperty) sbol::Property<sbol::Participation>;
%template(ownedParticipation) sbol::OwnedObject<sbol::Participation>;
%template(listOfOwnedParticipations) sbol::List<sbol::OwnedObject<sbol::Participation>>;
%include "interaction.h"

%include "module.h"
%include "model.h"

%template(moduleProperty) sbol::Property<sbol::Module>;
%template(ownedModule) sbol::OwnedObject<sbol::Module>;
%template(listOfOwnedModules) sbol::List<sbol::OwnedObject<sbol::Module>>;
%template(interactionProperty) sbol::Property<sbol::Interaction>;
%template(ownedInteraction) sbol::OwnedObject<sbol::Interaction>;
%template(listOfOwnedInteractions) sbol::List<sbol::OwnedObject<sbol::Interaction>>;
%template(functionalComponentProperty) sbol::Property<sbol::FunctionalComponent>;
%template(ownedFunctionalComponent) sbol::OwnedObject<sbol::FunctionalComponent>;
%template(listOfOwnedFunctionalComponents) sbol::List<sbol::OwnedObject<sbol::FunctionalComponent>>;

%include "moduledefinition.h"

%include "document.h"
%template(addComponentDefinition) sbol::Document::add<ComponentDefinition>;
%template(addSequence) sbol::Document::add<Sequence>;
%template(addModel) sbol::Document::add<Model>;
%template(addModuleDefinition) sbol::Document::add<ModuleDefinition>;
%template(getComponentDefinition) sbol::Document::get<ComponentDefinition>;
%template(getSequence) sbol::Document::get<Sequence>;
%template(getModel) sbol::Document::get<Model>;
%template(getModuleDefinition) sbol::Document::get<ModuleDefinition>;

// The following stub code can be used to make vectors act like Python lists 
//%extend std::vector {             // Attach these functions to vector
//    void __getitem__() {
//		std::cout << "Test" << std::endl;
//	}
//};





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
