#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

#include "identified.h"

using namespace std;
using namespace sbol;

Identified::Identified(std::string uri_prefix, std::string id)
{
	stampTime(); 
	char _identity[80];
	int size = sprintf(_identity, "%s//%s//%d//%d", uri_prefix.c_str(), id.c_str(), majorVersion, minorVersion);
	identity = string(_identity);
	persistentIdentity = identity;
}

void Identified::setIdentity(std::string uri_prefix, std::string id) 
{
	identity = uri_prefix + "/" + id;
}

void Identified::stampTime()
{
	time_t timer;
	struct tm * time_info;
	char time_stamp[80];

	time(&timer);
	time_info = localtime(&timer);
	timeStamp = string(asctime(time_info));
}

std::string Identified::getIdentity() {
	return identity;
}

std::string Identified::getTimeStamp()
{
	return timeStamp;
};

int Identified::getMinorVersion() 
{
	return minorVersion;
};

int Identified::getMajorVersion() 
{
	return majorVersion;
};

