#include "config.h"

using namespace sbol;
using namespace std;

extern Config& config = * new sbol::Config();

void sbol::setHomespace(std::string ns)
{
    config.setHomespace(ns);
};

std::string sbol::getHomespace()
{
    return config.getHomespace();
};

int sbol::hasHomespace()
{
    if (config.getHomespace().compare("") == 0)
        return 0;
    else
        return 1;
};

void sbol::toggleSBOLCompliance()
{
    config.toggleSBOLCompliance();
};

int sbol::isSBOLCompliant()
{
    return config.isSBOLCompliant();
};


void Config::setHomespace(std::string ns)
{
    this->home = ns;
};

string Config::getHomespace()
{
    return this->home;
};

int Config::hasHomespace()
{
    if (this->home.compare("") == 0)
        return 0;
    else
        return 1;
};

void Config::toggleSBOLCompliance()
{
    if (this->SBOLCompliant == 0)
        this->SBOLCompliant = 1;
    else
        this->SBOLCompliant = 0;
};

int Config::isSBOLCompliant()
{
    return this->SBOLCompliant;
};

