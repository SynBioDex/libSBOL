#include <iostream>
#include <string>
#include "sbol.h"
//#include "identified.h"

using namespace std;
using namespace sbol;

void Identified::set_identity(std::string uri_prefix, std::string id) {
	identity = uri_prefix + id;
	cout << "Identity : " << identity << endl;
}

std::string Identified::get_identity() {
	return identity;
}