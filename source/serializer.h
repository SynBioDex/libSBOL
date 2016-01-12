#include <libxml2/libxml/tree.h>
#include <libxml2/libxml/parser.h>

int main() {
	xmlDocPtr p = xmlNewDoc(BAD_CAST "1.0");
	std::cerr << "Bye\n";
	return 0;
}