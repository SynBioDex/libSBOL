#include <iostream>
#include <string>

#include "property.h"

using namespace std;
using namespace sbol;

string TextProperty::get()
{
	return text;
}

void TextProperty::set(string arg) 
{
	text = arg;
};
