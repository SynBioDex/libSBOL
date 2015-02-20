#include <iostream>
#include "sbol.h"
//#include "identified.h"

using namespace std;
using namespace sbol;

void Rectangle::set_values(int x, int y) {
	width = x;
	height = y;
}

int main() {
	Rectangle rect;
	rect.set_values(3, 4);
	cout << "area: " << rect.area();
	return 0;
}