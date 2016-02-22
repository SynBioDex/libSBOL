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
    #include "location.h"
    #include "sequenceannotation.h"
    #include "component.h"
    #include "componentdefinition.h"
    #include "sequence.h"
    #include "document.h"
    #include "sequenceannotationextension.h"
    #include "interaction.h"
    #include "participation.h"
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

    class Inner {
    public:
        Inner();
    };
    
    
    template<class T>
    class Middle : public T
    {
    public:
        Middle() :
        T()
        {}
    };
    
    template<class T>
    class Outer : public T
    {
    public:
        Outer() :
        T()
        {}
    };
%}



#ifdef SWIGWIN
    %include <windows.i>
#endif

// tell SWIG how to free strings
%typemap(newfree) char* "free($1);";

class Inner {
public:
    Inner();
};


template<class T>
class Middle : public T
{
public:
    Middle() :
    T()
    {}
};

template<class T>
class Outer : public T
{
public:
    Outer() :
    T()
    {}
};

%template (MiddleWrappingInner) Middle<Inner>;
%template (OuterWrappingMiddle) Outer<Middle<Inner>>;
