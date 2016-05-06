#define RAPTOR_STATIC

#include "sbol.h"

#include <dirent.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace sbol;

int main()
{
    int passed = 0;
    int failed = 0;
    
    Document& doc = *new Document();
    
    
    DIR* valid = opendir("./valid");
    struct dirent * file = readdir(valid);
    while (file)
    {
        if (file->d_name[0] != '.')
        {
            cout << "Testing " << file->d_name << endl;
            try
            {
                string path_to_test_file =  "./valid/" + string(file->d_name);
                doc.read(path_to_test_file);
                cout << "passed" << endl;
                passed++;
            }
            catch (...) {
                cout << "FAILED" << endl;
                failed++;
            }
        }
        file = readdir(valid);
    }
    
    DIR* invalid = opendir("./invalid");
    opendir("./invalid");
    file = readdir(invalid);
    while (file)
    {
        if (file->d_name[0] != '.')
        {
            cout << "Testing " << file->d_name << endl;
            try
            {
                string path_to_test_file =  "./invalid/" + string(file->d_name);
                doc.read(path_to_test_file);
                cout << "FAILED" << endl;
                failed++;
            }
            catch (...) {
                cout << "passed" << endl;
                passed++;
            }
        }

        file = readdir(invalid);
    }
    cout << "Passed: " << passed << endl;
    cout << "FAILED: " << failed << endl;
    
}
