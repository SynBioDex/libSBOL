#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

#include "sbolerror.h"
#include <string>

namespace sbol
{
    class Config
    {
        std::string home; ///< The authoritative namespace for the Document. Setting the home namespace is like     signing a piece of paper.
        int SBOLCompliant; ///< Flag indicating whether to autoconstruct URI's consistent with SBOL's versioning scheme
    public:
        Config() :
        home(""),
        SBOLCompliant(1)
            {
            };
        void setHomespace(std::string ns);
        std::string getHomespace();
        int hasHomespace();
        void toggleSBOLCompliance();
        int isSBOLCompliant();
    };

    void setHomespace(std::string ns);
    extern std::string getHomespace();
    int hasHomespace();
    void toggleSBOLCompliance();
    int isSBOLCompliant();
    std::string randomIdentifier();
    std::string autoconstructURI();
    std::string constructNonCompliantURI(std::string uri);
    std::string constructCompliantURI(std::string sbol_type, std::string display_id, std::string version);
    std::string constructCompliantURI(std::string parent_type, std::string child_type, std::string display_id, std::string version);
    std::string getCompliantURI(std::string uri_prefix, std::string sbol_class_name, std::string display_id, std::string version);
    std::string getClassName(std::string type);
    std::string getNameSpace(std::string type);
}

#endif /* CONFIG_INCLUDED */
