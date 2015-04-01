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

void VersionProperty::set(std::string version_arg)
{
	TextProperty *base = this;
	std::string old_value = base->get();
	base->set(version_arg);
	vector<string> v = base->split('-');
	if (v.size() > 2)
	{
		cout << "SBOL error: Invalid version string." << endl;
		base->set(old_value);
		return;
	}
	if (v.size() == 2)
	{
		qualifier.set(v[1]);
	}
	TextProperty left_side = TextProperty(v[0]);
	v = left_side.split('.');
	if (v.size() > 3)
	{
		cout << "SBOL error: Invalid version string." << endl;
	}
	int i_token = 0;
	while (i_token < v.size())
	{
		cout << std::stoi(v[i_token]) << endl;
		i_token++;
	}
}