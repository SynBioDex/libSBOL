%module libsbol
%{
    #define SWIG_FILE_WITH_INIT

    //  Headers are listed in strict order of dependency
    #include "constants.h"
    #include "sbolerror.h"
    #include "config.h"
    #include "validation.h"
    #include "property.h"
    #include "properties.h"
    #include "object.h"
    #include "identified.h"
    #include "toplevel.h"
    #include "sequenceannotation.h"
    #include "component.h"
    #include "componentdefinition.h"
    #include "sequence.h"
    #include "document.h"
    #include "interaction.h"
    #include "participation.h"
    #include "location.h"
    #include "sequenceconstraint.h"
    #include "moduledefinition.h"
    #include "module.h"

    #include "mapsto.h"
    #include "model.h"
    #include "collection.h"
    #include "assembly.h"
    #include "sbol.h"

    #include <vector>
    #include <map>
    #include <unordered_map>

    using namespace sbol;
    using namespace std;
    
%}

%include "python_docs.i"


#ifdef SWIGWIN
    %include <windows.i>
#endif

// Configure general error handling
%exception {
    try
    {
        $function
    }
    catch(SBOLError e)
    {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    }
    catch(...)
    {
    }
}

// Catch the signal from the Python interpreter indicating that iteration has reached end of list. For Python 2
%exception next
{
    try
    {
        $action
    }
    catch(SBOLError e)
    {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }
}

// Catch the signal from the Python interpreter indicating that iteration has reached end of list. For Python 3
%exception __next__
{
    try
    {
        $action
    }
    catch(SBOLError e)
    {
        PyErr_SetNone(PyExc_StopIteration);
        
        //        PyErr_SetObject(PyExc_StopIteration, Py_None);
        //PyErr_Clear()
        return NULL;
    }
}

// Hide these methods in the Python API
%ignore sbol::SBOLObject::close;
%ignore sbol::SBOLObject::properties;
%ignore sbol::SBOLObject::list_properties;
%ignore sbol::SBOLObject::owned_objects;
%ignore sbol::SBOLObject::begin;
%ignore sbol::SBOLObject::end;
%ignore sbol::SBOLObject::size;
%ignore sbol::OwnedObject::begin;
%ignore sbol::OwnedObject::end;
%ignore sbol::OwnedObject::size;
%ignore sbol::ReferencedObject::begin;
%ignore sbol::ReferencedObject::end;
%ignore sbol::ReferencedObject::size;
%ignore sbol::Document::parse_objects;
%ignore sbol::Document::parse_properties;
%ignore sbol::Document::namespaceHandler;
%ignore sbol::Document::flatten();
%ignore sbol::Document::parse_objects;
%ignore sbol::Document::close;

// Instantiate STL templates
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"

%template(_IntVector) std::vector<int>;
%template(_StringVector) std::vector<std::string>;
%template(_SBOLObjectVector) std::vector<sbol::SBOLObject*>;
%template(_MapVector) std::map<std::string, std::string >;
%template(_MapOfStringVector) std::map<std::string, std::vector<std::string> >;
%template(_MapOfSBOLObject) std::map<std::string, std::vector< sbol::SBOLObject* > >;

// Instantiate libSBOL templates
%include "config.h"
%include "constants.h"
%include "validation.h"
%include "property.h"

%template(_StringProperty) sbol::Property<std::string>;  // These template instantiations are private, hence the underscore...
%template(_IntProperty) sbol::Property<int>;

%include "properties.h"
%include "object.h"
%include "identified.h"
%include "toplevel.h"
%include "location.h"
%include "sequenceannotation.h"
%include "mapsto.h"
%include "component.h"
%include "sequenceconstraint.h"
%include "componentdefinition.h"
%include "sequence.h"
%include "participation.h"
%include "interaction.h"
%include "module.h"
%include "model.h"
%include "collection.h"
%include "moduledefinition.h"

%pythonappend sbol::PartShop::search
%{
    print ('Search complete')
    print(val)
    exec('val = ' + val)
    return val
    %}

%include "partshop.h"
%include "document.h"

%pythonappend sbol::PartShop::search
%{
    exec('val = ' + val)
    return val
%}

typedef std::string sbol::sbol_type;

%define TEMPLATE_MACRO_0(SBOLClass)
    %template(add ## SBOLClass) sbol::OwnedObject::add<SBOLClass>;
    %template(create ## SBOLClass) sbol::OwnedObject::create<SBOLClass>;
    %template(get ## SBOLClass) sbol::OwnedObject::get<SBOLClass>;

    %pythonappend add ## SBOLClass
    %{
        args[0].thisown = False
    %}
    
    %pythonappend create ## SBOLClass
    %{
        args[0].thisown = False
    %}
%enddef

%define TEMPLATE_MACRO_1(SBOLClass)

    /* Instantiate templates */
    %template(SBOLClass ## Vector) std::vector<sbol::SBOLClass>;
    %template(SBOLClass ## Property) sbol::Property<sbol::SBOLClass >;
    %template(Owned ## SBOLClass) sbol::OwnedObject<sbol::SBOLClass >;
    %template(ListOfOwned ## SBOLClass) sbol::List<sbol::OwnedObject<sbol::SBOLClass >>;

    /* Convert C++ vector of pointers --> Python list */
    %typemap(out) std::vector<sbol::SBOLClass*> {
        int len = $1.size();
        PyObject* list = PyList_New(0);
        for(auto i_elem = $1.begin(); i_elem != $1.end(); i_elem++)
        {
            PyObject *elem = SWIG_NewPointerObj(SWIG_as_voidptr(*i_elem), $descriptor(sbol::SBOLClass*), 0 |  0 );
            PyList_Append(list, elem);
        }
        $result  = list;
    }
    
    %pythonappend sbol::OwnedObject<sbol::SBOLClass >::add(SBOLClass& sbol_obj)
    %{
        args[0].thisown = False
    %}
    
    %pythonappend sbol::List<sbol::OwnedObject<sbol::SBOLClass >>::add(SBOLClass& sbol_obj)
    %{
        args[0].thisown = False
    %}
    
    %pythonappend sbol::List<sbol::OwnedObject<sbol::SBOLClass >>::create(std::string uri)
    %{
        args[0].thisown = False
    %}
        
%enddef

%define TEMPLATE_MACRO_2(SBOLClass)
        
    %template(add ## SBOLClass) sbol::Document::add<SBOLClass>;
        
    %pythonappend add ## SBOLClass
    %{
        args[0].thisown = False
    %}
        
%enddef
        
// Templates used by subclasses of Location: Range, Cut, and Generic Location
//%template(addRange) sbol::OwnedObject::add<Range>;
//%template(getRange) sbol::OwnedObject::get<Range>;
//%template(createRange) sbol::OwnedObject::create<Range>;
//%template(addCut) sbol::OwnedObject::add<Cut>;
//%template(getCut) sbol::OwnedObject::get<Cut>;
//%template(createCut) sbol::OwnedObject::create<Cut>;
//%template(addGenericLocation) sbol::OwnedObject::add<GenericLocation>;
//%template(getGenericLocation) sbol::OwnedObject::get<GenericLocation>;
//%template(createGenericLocation) sbol::OwnedObject::create<GenericLocation>;
TEMPLATE_MACRO_0(Range);
// Templates used in SequenceAnnotation class
TEMPLATE_MACRO_1(Location);
        
// Templates used in Component class
TEMPLATE_MACRO_1(MapsTo);
     
// Templates used in ComponentDefinition class
TEMPLATE_MACRO_1(SequenceConstraint);
TEMPLATE_MACRO_1(SequenceAnnotation);
TEMPLATE_MACRO_1(Component);

// Templates used in Participation class
%template(listOfURIs) sbol::List<sbol::URIProperty>;

// Templates used in Interaction class
TEMPLATE_MACRO_1(Participation);
        
// ModuleDefinition templates
TEMPLATE_MACRO_1(Module);
TEMPLATE_MACRO_1(Interaction);
TEMPLATE_MACRO_1(FunctionalComponent);

// Templates classes used by Document class
TEMPLATE_MACRO_1(ComponentDefinition);
TEMPLATE_MACRO_1(ModuleDefinition);
TEMPLATE_MACRO_1(Sequence);
TEMPLATE_MACRO_1(Model);

// Template functions used by Document
//%template(addComponentDefinition) sbol::Document::add<ComponentDefinition>;
TEMPLATE_MACRO_2(ComponentDefinition)
%template(addSequence) sbol::Document::add<Sequence>;
%template(addModel) sbol::Document::add<Model>;
%template(addModuleDefinition) sbol::Document::add<ModuleDefinition>;
%template(getComponentDefinition) sbol::Document::get<ComponentDefinition>;
%template(getSequence) sbol::Document::get<Sequence>;
%template(getModel) sbol::Document::get<Model>;
%template(getModuleDefinition) sbol::Document::get<ModuleDefinition>;


// Template functions used by PartShop
%template(pullComponentDefinition) sbol::PartShop::pull<ComponentDefinition>;

%extend sbol::Property
{
    std::string __getitem__(const int nIndex)
    {
        return $self->operator[](nIndex);
    }
    
    Property<LiteralType>* __iter__()
    {
        $self->python_iter = Property<LiteralType>::iterator($self->begin());
        return $self;
    }

    // Built-in iterator function for Python 2
    std::string next()
    {
        if ($self->python_iter != $self->end())
        {
            std::string ref = *$self->python_iter;
            $self->python_iter++;
            if ($self->python_iter == $self->end())
            {
                PyErr_SetNone(PyExc_StopIteration);
            }
            return ref;
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }
    
    // Built-in iterator function for Python 3
    std::string __next__()
    {
        if ($self->python_iter != $self->end())
        {
            std::string ref = *$self->python_iter;
            $self->python_iter++;
            if ($self->python_iter == $self->end())
            {
                PyErr_SetNone(PyExc_StopIteration);
            }
            return ref;
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }
    
    int __len__()
    {
        return $self->size();
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
		throw SBOLError(END_OF_LIST, "");
		return NULL;
	}

    SBOLClass* __next__()
    {
        if ($self->python_iter != $self->end())
        {

            SBOLObject* obj = *$self->python_iter;
            $self->python_iter++;

            return (SBOLClass*)obj;
        }

        throw SBOLError(END_OF_LIST, "");;
        return NULL;
    }
    
    int __len__()
    {
        return $self->size();
    }
};

%extend sbol::SBOLObject
{
    std::string __repr__()
    {
        return $self->type;
    }

    std::string __str__()
    {
        return $self->identity.get();
    }
}

%extend sbol::ReferencedObject
{
    std::string __getitem__(const int nIndex)
    {
        return $self->operator[](nIndex);
    }
    
    ReferencedObject* __iter__()
    {
        $self->python_iter = ReferencedObject::iterator($self->begin());
        return $self;
    }
    
    std::string next()
    {
        if ($self->python_iter != $self->end())
        {
            std::string ref = *$self->python_iter;
            $self->python_iter++;
            if ($self->python_iter == $self->end())
            {
                PyErr_SetNone(PyExc_StopIteration);
            }
            return ref;
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }
    
    std::string __next__()
    {
        if ($self->python_iter != $self->end())
        {
            std::string ref = *$self->python_iter;
            $self->python_iter++;
            if ($self->python_iter == $self->end())
            {
                PyErr_SetNone(PyExc_StopIteration);
            }
            return ref;
        }
        throw SBOLError(END_OF_LIST, "");
        return NULL;
    }
    
    int __len__()
    {
        return $self->size();
    }
};
    
%extend sbol::ComponentDefinition
{
    void assemble(PyObject *list)
    {
        std::vector<sbol::ComponentDefinition*> list_of_cdefs = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::ComponentDefinition* cd;
                if ((SWIG_ConvertPtr(obj,(void **) &cd, $descriptor(sbol::ComponentDefinition*),1)) == -1) throw;
                list_of_cdefs.push_back(cd);
            }
            $self->assemble(list_of_cdefs);
        };
    }
}

%extend sbol::Document
{
    void addComponentDefinition(PyObject *list)
    {
        std::vector<sbol::ComponentDefinition*> list_of_cds = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::ComponentDefinition* cd;
                if ((SWIG_ConvertPtr(obj,(void **) &cd, $descriptor(sbol::ComponentDefinition*),1)) == -1) throw;
                list_of_cds.push_back(cd);
            }
			$self->add(list_of_cds);
        };        
    }

    void addSequence(PyObject *list)
    {
        std::vector<sbol::Sequence*> list_of_seqs = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::Sequence* seq;
                if ((SWIG_ConvertPtr(obj,(void **) &seq, $descriptor(sbol::Sequence*),1)) == -1) throw;
                list_of_seqs.push_back(seq);
            }
			$self->add(list_of_seqs);
        };
    }
    
    void addModuleDefinition(PyObject *list)
    {
        std::vector<sbol::ModuleDefinition*> list_of_mds = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::ModuleDefinition* md;
                if ((SWIG_ConvertPtr(obj,(void **) &md, $descriptor(sbol::ModuleDefinition*),1)) == -1) throw;
                list_of_mds.push_back(md);
            }
			$self->add(list_of_mds);
        };                
    }
}

    
%extend sbol::ModuleDefinition
{
    void assemble(PyObject *list)
    {
        std::vector<sbol::ModuleDefinition*> list_of_mdefs = {};
        if (PyList_Check(list))
        {
            for (int i = 0; i < PyList_Size(list); ++i)
            {
                PyObject *obj = PyList_GetItem(list, i);
                sbol::ModuleDefinition* md;
                if ((SWIG_ConvertPtr(obj,(void **) &md, $descriptor(sbol::ModuleDefinition*),1)) == -1) throw;
                list_of_mdefs.push_back(md);
            }
            $self->assemble(list_of_mdefs);
        };
    }
}

%pythoncode
%{
    def register_extension_class(ns, ns_prefix, class_name, constructor ):
        uri = ns + class_name
        Config.__extensionclass__[uri] = constructor

    def testSBOL():
        """
        Function to run test suite for pySBOL
        """
        import unit_tests
        unit_tests.runTests()
    
    ### Add PYTHON_DATA_MODEL_REGISTER as a static variable in Config. This dictionary contains key : value pairs consisting of a Python extension class URI and the corresponding constructor callbacks for Python extension classes
    Config.__extensionclass__ = {}
%}
    
//%inline
//%{
//    // SBOLObject&(*constructor)()
//    PyObject* register_extension_class(std::string ns, std::string ns_prefix, std::string class_name, PyObject* constructor )
//    {
//        std::string uri = ns + class_name;
////        SBOL_DATA_MODEL_REGISTER.insert(make_pair(uri, (SBOLObject&(*)())constructor));
//        //namespaces[ns_prefix] = ns;  // Register extension namespace
//        std::cout << "Registering " << uri << endl;
//        std::cout << "Constructing " << uri << endl;
//        PyObject* obj = PyObject_CallFunction(constructor, NULL);
//        std::cout << "Constructed " << uri << endl;
//        return obj;
//    };
//    
//%}
        
        //%extend sbol::Document
        //{
        //    std::string __getitem__(const int nIndex)
        //    {
        //        return $self->operator[](nIndex);
        //    }
        //
        //    ReferencedObject* __iter__()
        //    {
        //        $self->python_iter = Document::iterator($self->begin());
        //        return $self;
        //    }
        //
        //    std::string next()
        //    {
        //        if ($self->python_iter != $self->end())
        //        {
        //            std::string ref = *$self->python_iter;
        //            $self->python_iter++;
        //            if ($self->python_iter == $self->end())
        //            {
        //                PyErr_SetNone(PyExc_StopIteration);
        //            }
        //            return ref;
        //        }
        //        throw (END_OF_LIST);
        //        return NULL;
        //    }
        //    
        //    int __len__()
        //    {
        //        return $self->size();
        //    }
        //};
        
        

//// The following code was experimented with for mapping C++ class structure to Python class structure
//%pythonappend ComponentDefinition %{
//    name = property(name.set, name.get)
//    %}
//
//%extend sbol::Identified{
//    %pythoncode %{
//        __swig_getmethods__["identity"] = _libsbol.TextProperty.get
//        __swig_setmethods__["identity"] = _libsbol.TextProperty.set
//        if _newclass: identity = property(_libsbol.TextProperty.get, _libsbol.URIProperty.set)
//            %}
//};

//%include "std_unordered_map.i"
//namespace std {
//    %template(_UnorderedMapVector) unordered_map<string, string >;
//    //%template(_UnorderedMapOfStringVector) unordered_map<string, string>;
//}
        
//%include "std_function.i"
//namespace std {
//    %template(_ValidationRule) function<void(void *, void *)>;
//    %template(_ValidationRules) vector<function<void(void *, void *)>>;}
//}
        
//typedef const void(*sbol::ValidationRule)(void *, void *);
// %template(_ValidationRules) std::vector<sbol::ValidationRule>;
        
//%pythonappend sbol::Config::parse_extension_objects()
//%{
//    print ("Parsing extension objects")
//%}
//
//%pythonappend sbol::Config::extension_memory_handler(bool swig_thisown)
//%{
//    print ("Entering memory handler")
//    print (args)
//    self.thisown = args[0]
//%}
        
//%pythonappend sbol::Config::extension_memory_handler(bool swig_thisown)
//%{
//    print ("Entering memory handler")
//    print (args)
//    self.thisown = args[0]
//%}




