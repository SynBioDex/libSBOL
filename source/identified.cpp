#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <unordered_map>

#include "identified.h"

using namespace std;
using namespace sbol;

//Identified::Identified(std::string uri_prefix, std::string id)
//{
//	stampTime(); 
//	char _identity[80];
//	int size = sprintf(_identity, "%s//%s//%d//%d", uri_prefix.c_str(), id.c_str(), majorVersion, minorVersion);
//	identity.set(string(_identity));
//	persistentIdentity.set(identity.get());
//}

Identified::Identified(std::string uri_prefix, std::string id, std::string _version) 
{
	identity = TextProperty(uri_prefix + "/" + id + "/" + _version);
	persistentIdentity = TextProperty(identity);
	version = VersionProperty(_version);
	timeStamp = TextProperty();
};

void Identified::setIdentity(std::string uri_prefix, std::string id) 
{
	identity.set(uri_prefix + "/" + id);
}

void Identified::stampTime()
{
	time_t timer;
	struct tm * time_info;
	char time_stamp[80];

	time(&timer);
	time_info = localtime(&timer);
	timeStamp.set(string(asctime(time_info)));
}

Identified Identified::clone() 
{
	Identified clone = Identified();
	clone.identity.set(this->identity.get());
	clone.persistentIdentity.set(this->persistentIdentity.get());
	clone.version.set(this->version.get());
	return clone;
}

std::string Identified::getIdentity() {
	return identity.get();
}

std::string Identified::getTimeStamp()
{
	return timeStamp.get();
};

