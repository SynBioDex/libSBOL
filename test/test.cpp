#define RAPTOR_STATIC

#include "sbol.h"

#ifdef _WIN32
    #include "dirent.h"
#else
    #include <dirent.h>
#endif

#include <iostream>
#include <vector>

using namespace std;
using namespace sbol;

int main()
{
    int passed = 0;
    int failed = 0;
    
    Document& doc = *new Document();
    Document& doc2 = *new Document();

    string path = "roundtrip";
    DIR* valid = opendir(path.c_str());
    struct dirent * file = readdir(valid);
    while (file)
    {
        if (file->d_name[0] != '.')
        {
            string filename = string(file->d_name);
            std::cout << "Testing " << filename << std::endl;
            doc.read(path + "/" + filename);
            std::cout << "Writing " << filename << std::endl;
            doc.write(path + "/" + "new_" + filename);
            std::cout << "Reading " << filename << std::endl;
            doc2.read(path + "/" + "new_" + filename);
            int is_equal_to = doc.compare(&doc2);
            if (is_equal_to)
            {
                std::cout << "=== " << filename << " passed ===" << std::endl;
                ++passed;
            }
            else
            {
                std::cout << "XXX " << filename << " failed XXX" << std::endl;
                ++failed;
            }
        }
        file = readdir(valid);
    }
    cout << "Passed: " << passed << endl;
    cout << "FAILED: " << failed << endl;
    
}
