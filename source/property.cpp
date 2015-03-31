#include "property.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;

string TextProperty::get()
{
	return value;
};

void TextProperty::set(string arg) 
{
	value = arg;
}

vector<string> TextProperty::split(const char c) {
	// Adapted from C++ cookbook
	const string& s = this->value;
	vector<string> v;

	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos) {
		v.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}
	return v;
}


int IntProperty::get()
{
	return value;
}

void IntProperty::set(int arg)
{
	value = arg;
}

VersionProperty::VersionProperty(std::string version_arg)
{
	TextProperty *base = this;
	base->set(version_arg);
	this->major.set(1);
	this->minor.set(0);
	this->incremental.set(0);
	cout << "Instantiating version " << version_arg << endl;
	cout << base->get() << endl;
	cout << this->major.get() << endl;
	cout << this->minor.get() << endl;
	cout << this->incremental.get() << endl;
}