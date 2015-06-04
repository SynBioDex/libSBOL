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

void TextProperty::getType()
{
	cout << this->type << endl;
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
	vector<string> v = base->split('-');
	cout << v.size() << endl;
	this->major.set(1);
	this->minor.set(0);
	this->incremental.set(0);
	cout << base->get() << endl;
	cout << this->major.get() << endl;
	cout << this->minor.get() << endl;
	cout << this->incremental.get() << endl;
}

void VersionProperty::set(std::string maven_version)
{
	TextProperty *base = this;
	string old_value = base->get();
	base->set(maven_version);
	
	// parse qualifier string from maven version string
	vector<string> version_tokens = base->split('-');
	int n_tokens = version_tokens.size();
	if (n_tokens > 2)
	{
		base->set(old_value);
		int e = SBOLError(1, "Invalid version string.");
		return;
	}
	if (n_tokens == 2)
	{
		qualifier.set(version_tokens[1]);
	}

	// parse major, minor, and incremental version properties
	TextProperty left_side = TextProperty(UNDEFINED, version_tokens[0]);
	version_tokens = left_side.split('.');
	n_tokens = version_tokens.size();
	if (n_tokens > 3)
	{
		cout << "SBOL error: Invalid version string." << endl;
		return;
	}
	if (n_tokens > 2)
	{
		incremental.set(stoi(version_tokens[2]));
		cout << incremental.get() << endl;
	}
	if (n_tokens > 1)
	{
		minor.set(stoi(version_tokens[1]));
		cout << minor.get() << endl;
	}
	major.set(stoi(version_tokens[0]));
	cout << major.get() << endl;
	// @todo:  free left_side TextProperty?
}