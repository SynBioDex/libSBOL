#include "property.h"

#include <string>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace sbol;

//PropertyStore* sbol::global_property_buffer = new PropertyStore;

//PropertyBase::PropertyBase(sbol_type type_uri, void *property_owner, void *self)
//{
//	this->type = type_uri;
//	this->sbol_owner = (SBOLObject *)property_owner;
//	SBOLObject* owner = (SBOLObject *)&property_owner;
//	PropertyBase& property_instance = *this;
//
//	// Register Property in owner Object
//	if (sbol_owner != NULL)
//	{
//		//sbol_owner->properties.insert({ type_uri, *this });
//		//global_property_buffer->insert({ type_uri, *this });
//		sbol_owner->properties.insert({ type_uri, "" });
//	}
//}
//
//void PropertyBase::write()
//{
//	std::string subject = (*sbol_owner).identity.get();
//	sbol_type predicate = type;
//
//	cout << "Subject:  " << subject << endl;
//	cout << "Predicate: " << predicate << endl;
//	cout << "No Object" << endl;
//}
//

sbol_type SBOLObject::getTypeURI() 
{
	return type;
}

//sbol_type PropertyBase::getTypeURI()
//{
//	return type;
//};
//
//SBOLObject& PropertyBase::getOwner()
//{
//
//	return *sbol_owner;
//}

void SBOLObject::add(PropertyBase& property_instance)
{
	//properties[property_instance.type] = &property_instance;
	cout << "Registering " << &property_instance << endl;
	//sbol::global_property_buffer->insert({ property_instance.type, property_instance });

	//properties.push_back(property_instance);
	//properties.push_back((PropertyBase *)&property_instance);
	//properties.push_back(property_instance);
	//cout << &property_instance << endl;
	//cout << &(*properties.back()) << endl;
}

//Property& SBOLObject::get()
//{
//	//return *properties[0];
//	return properties.begin();
//}

void SBOLObject::serialize()
{
	for (auto it = properties.begin(); it != properties.end(); ++it)
	{
		std::cout << type << it->first << it->second.front() << endl;
	}
	//for (std::vector<PropertyBase*>::iterator property = properties.begin(); property != properties.end(); ++property)	
	//{
	//	obj = (*property);
	//	std::cout << obj->type << endl;
	//}
}


//sbol_type Property::getTypeURI()
//{
//	return type;
//}

//sbol_type TextProperty::getTypeURI()
//{
//	return type;
//}
//
//SBOLObject& Property::getOwner()
//{
//	return *sbol_owner;
//}
//
//SBOLObject& TextProperty::getOwner()
//{
//	return *sbol_owner;
//}
//
//vector<string> TextProperty::split(const char c) {
//	// Adapted from C++ cookbook
//	const string& s = this->value;
//	vector<string> v;
//
//	string::size_type i = 0;
//	string::size_type j = s.find(c);
//
//	while (j != string::npos) {
//		v.push_back(s.substr(i, j - i));
//		i = ++j;
//		j = s.find(c, j);
//
//		if (j == string::npos)
//			v.push_back(s.substr(i, s.length()));
//	}
//	return v;
//}
//
//
//int IntProperty::get()
//{
//	return value;
//}
//
//void IntProperty::set(int arg)
//{
//	value = arg;
//}
//
//VersionProperty::VersionProperty(std::string version_arg)
//{
//	TextProperty *base = this;
//	base->set(version_arg);
//	vector<string> v = base->split('-');
//	cout << v.size() << endl;
//	this->major.set(1);
//	this->minor.set(0);
//	this->incremental.set(0);
//	cout << base->get() << endl;
//	cout << this->major.get() << endl;
//	cout << this->minor.get() << endl;
//	cout << this->incremental.get() << endl;
//}
//

//VersionProperty::VersionProperty(std::string version_arg)
//{
//	std::string value = version_arg;
//	//vector<string> v = value.split('-');  // split method is not defined
//	//cout << v.size() << endl;
//	major.set(1);
//	minor.set(0);
//	incremental.set(0);
//	qualifier.set("");
//}
//
//void VersionProperty::set(std::string maven_version)
//{
//}

//	TextProperty *base = this;
//	string old_value = base->get();
//	base->set(maven_version);
//	
//	// parse qualifier string from maven version string
//	vector<string> version_tokens = base->split('-');
//	int n_tokens = version_tokens.size();
//	if (n_tokens > 2)
//	{
//		base->set(old_value);
//		int e = SBOLError(1, "Invalid version string.");
//		return;
//	}
//	if (n_tokens == 2)
//	{
//		qualifier.set(version_tokens[1]);
//	}
//
//	// parse major, minor, and incremental version properties
//	TextProperty left_side = TextProperty(UNDEFINED, NULL, version_tokens[0]);
//	version_tokens = left_side.split('.');
//	n_tokens = version_tokens.size();
//	if (n_tokens > 3)
//	{
//		cout << "SBOL error: Invalid version string." << endl;
//		return;
//	}
//	if (n_tokens > 2)
//	{
//		incremental.set(stoi(version_tokens[2]));
//		cout << incremental.get() << endl;
//	}
//	if (n_tokens > 1)
//	{
//		minor.set(stoi(version_tokens[1]));
//		cout << minor.get() << endl;
//	}
//	major.set(stoi(version_tokens[0]));
//	cout << major.get() << endl;
//	// @todo:  free left_side TextProperty?
//}