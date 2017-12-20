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


bool roundtrip(string path, string filename)
{
    Document& doc = *new Document();
    Document& doc2 = *new Document();

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
        return true;
    }
    else
    {
        std::cout << "XXX " << filename << " failed XXX" << std::endl;
        return false;
    }
}

int main(int argc, char* argv[])
{
    string path = "roundtrip";
    int passed = 0;
    int failed = 0;
    
    if (argc > 1)
    {
        if (roundtrip(path, string(argv[1])))
            passed++;
        else
            failed++;
    }
    else
    {
        DIR* valid = opendir(path.c_str());
        struct dirent * file = readdir(valid);
        while (file)
        {
            if (file->d_name[0] != '.')
            {
                if (roundtrip(path, file->d_name))
                    passed++;
                else
                    failed++;
            }
            file = readdir(valid);
        }
    }

    cout << "Passed: " << passed << endl;
    cout << "FAILED: " << failed << endl;
    
}
