#include <string>

#include "property.h"

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

int IntProperty::get()
{
	return value;
}

void IntProperty::set(int arg)
{
	value = arg;
}