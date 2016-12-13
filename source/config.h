#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "sbolerror.h"
#include <string>

namespace sbol
{
    /// A class which contains global configuration variables for the libSBOL environment. Intended to be used like a static class, configuration variables are accessed through the `config' object.
    class Config
    {
    private:
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like     signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
        int SBOLCompliantTypes; ///< Flag indicating whether an object's type is included in SBOL-compliant URIs
        int catch_exceptions = 0;
        std::string format = "rdfxml";
    public:
        Config() :
        home(""),
        SBOLCompliant(1),
        SBOLCompliantTypes(1)
            {
            };
        void setHomespace(std::string ns);
        std::string getHomespace();
        int hasHomespace();
        void toggleSBOLCompliance();
        int isSBOLCompliant();
        void toggleSBOLCompliantTypes();
        int compliantTypesEnabled();
        void toggleExceptions();
        int exceptionsEnabled();
        void setFileFormat(std::string file_format);
        std::string getFileFormat();
    };

    void setHomespace(std::string ns); ///< Set the default namespace for autocreation of URIs when a new SBOL object is created
    extern std::string getHomespace(); ///< Get the current default namespace for autocreation of URIs when a new SBOL object is created
    int hasHomespace();                ///< Checks if a valid default namespace has been defined
    void toggleSBOLCompliance();       ///< Enables SBOLCompliance, which simplifies creation of URIs in constructor calls
    int isSBOLCompliant();             ///< Checks if SBOLCompliance is enabled
    void toggleSBOLCompliantTypes();   ///< Turns option to include types in SBOL-compliant URIs on or off
    int compliantTypesEnabled();       ///< Checks if an object's type is included in SBOL-compliant URIs
    void setFileFormat(std::string file_format);
    std::string getFileFormat();
    void toggleExceptions();
    int exceptionsEnabled();
    
    std::string randomIdentifier();
    std::string autoconstructURI();
    std::string constructNonCompliantURI(std::string uri);
    std::string constructCompliantURI(std::string sbol_type, std::string display_id, std::string version);
    std::string constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version);
    std::string getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version);
    std::string parseClassName(std::string uri);
    std::string parsePropertyName(std::string uri);
    std::string parseNamespace(std::string uri);
}

#endif /* CONFIG_INCLUDED */
