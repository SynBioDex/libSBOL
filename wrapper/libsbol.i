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
    #include "provo.h"
    #include "partshop.h"
    #include "combinatorialderivation.h"
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
// %ignore sbol::SBOLObject::end;
%ignore sbol::SBOLObject::size;
%ignore sbol::OwnedObject::begin;
// %ignore sbol::OwnedObject::end;
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

    
%pythonappend add
%{
    self.thisown = False
%}
    
%pythonappend create
%{
    self.thisown = False
%}

%pythonappend addToDocument
%{
    arg2.thisown = False
%}

/* @TODO remove methods should change thisown flag back to True */
    
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

// Converts json-formatted text into Python data structures, eg, lists, dictionaries
%pythonappend sbol::PartShop::search
%{
    if val[0] == '[' :
        exec('val = ' + val)
        return val
    else :
        return val
%}
//
//// Converts json-formatted text into Python data structures, eg, lists, dictionaries
%pythonappend sbol::PartShop::submit
%{
    if val[0] == '[' :
        exec('val = ' + val)
        return val
    else :
        return val
%}

%include "partshop.h"

%pythonappend addComponentDefinition
%{
    # addComponentDefinition is overloaded, it can take a list or single object as an argument
    if type(args[0]) is list:
        for obj in args[0]:
            obj.thisown = False
    else:
        args[0].thisown = False
%}

%pythonappend addModuleDefinition
%{
    # addModuleDefinition is overloaded, it can take a list or single object as an argument
    if type(args[0]) is list:
        for obj in args[0]:
            obj.thisown = False
    else:
        args[0].thisown = False
%}

%pythonappend addSequence
%{
    # addModuleDefinition is overloaded, it can take a list or single object as an argument
    if type(args[0]) is list:
        for obj in args[0]:
            obj.thisown = False
    else:
        args[0].thisown = False
%}

%pythonappend addModel
%{
    # addModel is overloaded, it can take a list or single object as an argument
    if type(args[0]) is list:
        for obj in args[0]:
            obj.thisown = False
    else:
        args[0].thisown = False
%}
    
%include "document.h"

typedef std::string sbol::sbol_type;

/* This macro is used to instantiate container properties (OwnedObjects) that can contain more than one type of object, eg, SequenceAnnotation::locations */
%define TEMPLATE_MACRO_0(SBOLClass)
    %template(add ## SBOLClass) sbol::OwnedObject::add<SBOLClass>;
    %template(create ## SBOLClass) sbol::OwnedObject::create<SBOLClass>;
    %template(get ## SBOLClass) sbol::OwnedObject::get<SBOLClass>;
    
%enddef

/* This macro is used to instantiate container properties (OwnedObjects) that can contain a single type of object, eg, ComponentDefinition::sequenceAnnotations */
%define TEMPLATE_MACRO_1(SBOLClass)
    
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
    
    /* Instantiate templates */
    %template(SBOLClass ## Vector) std::vector<sbol::SBOLClass>;
    %template(SBOLClass ## Property) sbol::Property<sbol::SBOLClass >;
    %template(Owned ## SBOLClass) sbol::OwnedObject<sbol::SBOLClass >;
    %template(ListOfOwned ## SBOLClass) sbol::List<sbol::OwnedObject<sbol::SBOLClass >>;
    
%enddef

/* This macro is used to instantiate special adders and getters for the Document class */
%define TEMPLATE_MACRO_2(SBOLClass)
    
//    %template(add ## SBOLClass) sbol::Document::add<SBOLClass>;
    %template(get ## SBOLClass) sbol::Document::get<SBOLClass>;
    
%enddef
        
// Templates used by subclasses of Location: Range, Cut, and Generic Location
TEMPLATE_MACRO_0(Range);
TEMPLATE_MACRO_0(Cut);
TEMPLATE_MACRO_0(GenericLocation);

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

TEMPLATE_MACRO_2(ComponentDefinition)
TEMPLATE_MACRO_2(ModuleDefinition)
TEMPLATE_MACRO_2(Sequence)
TEMPLATE_MACRO_2(Model)
    

// Template functions used by PartShop
//%template(pullComponentDefinitionFromCollection) sbol::PartShop::pull < ComponentDefinition > (sbol::Collection& collection);
//%template(pullComponentDefinition) sbol::PartShop::pull < ComponentDefinition >;
//%template(pullCollection) sbol::PartShop::pull < Collection >;
//%template(pullSequence) sbol::PartShop::pull < Sequence >;
//%template(pullDocument) sbol::PartShop::pull < Document >;
%template(countComponentDefinition) sbol::PartShop::count < ComponentDefinition >;
%template(countCollection) sbol::PartShop::count < Collection >;

%define PROPERTY_MACRO(SBOLClass)
%extend sbol::SBOLClass
{
    std::string __getitem__(const int nIndex)
    {
        return $self->operator[](nIndex);
    }
    
    SBOLClass* __iter__()
    {
        $self->python_iter = SBOLClass::iterator($self->begin());
        return $self;
    }
    
    // Built-in iterator function for Python 2
    std::string next()
    {
        if ($self->size() == 0)
            throw SBOLError(END_OF_LIST, "");
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
        if ($self->size() == 0)
            throw SBOLError(END_OF_LIST, "");
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
%enddef

%extend sbol::Config
{
    // This is the global SBOL register for Python extension classes.  It maps an SBOL RDF type (eg, "http://sbolstandard.org/v2#Sequence" to a Python constructor
    //        static PyObject* PYTHON_DATA_MODEL_REGISTER = PyDict_New();
//    static std::map<std::string, PyObject*> PYTHON_DATA_MODEL_REGISTER;
}
    
%extend sbol::SBOLObject
{
    void register_extension(std::string ns, std::string ns_prefix, std::string class_name, PyObject* constructor)
    {
//        std::string uri = ns + class_name;
//        Config::PYTHON_DATA_MODEL_REGISTER[uri] = constructor;
//        namespaces[ns_prefix] = ns;
    };
}

PROPERTY_MACRO(URIProperty)
PROPERTY_MACRO(TextProperty)
PROPERTY_MACRO(IntProperty)

    
    
    
//%extend sbol::ReferencedObject
//{
//    std::string __getitem__(const int nIndex)
//    {
//        return $self->operator[](nIndex);
//    }
//    
//    ReferencedObject* __iter__()
//    {
//        $self->python_iter = ReferencedObject::iterator($self->begin());
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
//        throw SBOLError(END_OF_LIST, "");
//        return NULL;
//    }
//    
//    std::string __next__()
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
//        throw SBOLError(END_OF_LIST, "");
//        return NULL;
//    }
//    
//    int __len__()
//    {
//        return $self->size();
//    }
//};

%include "assembly.h"
%include "provo.h"
%include "combinatorialderivation.h"

    
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
    
    void assemble(PyObject *list, PyObject *doc)
    {
        sbol::Document* cpp_doc;
        if ((SWIG_ConvertPtr(doc,(void **) &cpp_doc, $descriptor(sbol::Document*),1)) == -1) throw;

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
            $self->assemble(list_of_cdefs, *cpp_doc);
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
    
    def testSBOL():
        """
        Function to run test suite for pySBOL
        """
        import sys, os
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))  # Set path to current directory
        import unit_tests
        unit_tests.runTests()
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




