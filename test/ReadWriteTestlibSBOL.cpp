// Final Testing of LibSBOL.cpp : main project file.

#include "sbol.h"
using namespace sbol;

int main(int argc, char* argv[])
{
	setHomespace("http://sbols.org");
	//create an SBOL Document to read into
	Document &doc = *new Document();
	std::string version = "1.0.0";
	//printf("Reading %s\n", argv[1]);
	doc.read(std::string(argv[1]));
	//printf("Writing %s\n", argv[2]);
	doc.write(std::string(argv[2]));		
	//printf("%s\n", argv[1]);
	//printf("%s\n", argv[2]);
}


