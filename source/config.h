#ifndef CONFIG_INCLUDED
#define CONFIG_INCLUDED

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
        SBOLCompliant(0)
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

}

#endif /* CONFIG_INCLUDED */
