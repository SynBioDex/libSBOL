#define RAPTOR_STATIC

#include "sbol.h"

#ifdef _WIN32
    #include "dirent.h"
#else
    #include <dirent.h>
#endif

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using namespace sbol;


bool roundtrip(string path, string filename)
{
    Document& doc = *new Document();
    Document& doc2 = *new Document();

    std::cout << "Testing " << filename << std::endl;
    try
    {
        doc.read(path + "/" + filename);        
    }
    catch(const std::exception &e)
    {
        cerr << e.what() << endl;
        std::cout << "FAIL" << std::endl;
        return false;
    }
    try
    {
        std::cout << "Writing " << filename << std::endl;
        doc.write(path + "/" + "new_" + filename);        
    }
    catch(const std::exception &e)
    {
        cerr << e.what() << endl;
        std::cout << "FAIL" << std::endl;
        return false; 
    }
    try
    {
        std::cout << "Reading " << filename << std::endl;
        doc2.read(path + "/" + "new_" + filename);
        remove(string(path + "/" + "new_" + filename).c_str());
    }
    catch(const std::exception &e)
    {
        cerr << e.what() << endl;
        std::cout << "FAIL" << std::endl;
        return false;
    }
    int is_equal_to = doc.compare(&doc2);
    if (is_equal_to)
    {
        std::cout << "PASS" << std::endl;
        return true;
    }
    else
    {
        std::cout << "FAIL" << std::endl;
        return false;
    }
}

int main(int argc, char* argv[])
{ 
    Config::setOption("validate", false);
    string path = "roundtrip";
    int passed = 0;
    int failed = 0;
    int expected = 0;

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
        int test_case = 0;
        vector<string> expected_fail_cases = { "SBOL1and2Test.xml",
            "BBa_T9002_orig.xml", 
            "pIKE_pTAK_toggle_switches_orig.xml",
            "partial_pIKE_left_cassette_orig.xml",
            "partial_pIKE_right_casette_orig.xml",
            "partial_pIKE_right_cassette_orig.xml",
            "partial_pTAK_left_cassette_orig.xml",
            "partial_pTAK_right_cassette_orig.xml",
            "new_partial_pIKE_left_cassette_orig.xml",
            "new_partial_pTAK_right_cassette_orig.xml" };

        while (file)
        {
            if (file->d_name[0] != '.')
            {
                std::cout << "================" << std::endl;
                std::cout << "TEST CASE " << test_case << " : " << file->d_name << std::endl;
                std::cout << "================" << std::endl;
                if (roundtrip(path, file->d_name))
                    passed++;
                else
                {
                    if (std::find(expected_fail_cases.begin(), expected_fail_cases.end(), file->d_name) == expected_fail_cases.end())
                        failed++;
                    else
                        expected++;
                }
                test_case++;
            }
            file = readdir(valid);
        }
    }

    cout << "Passed: " << passed << endl;
    cout << "Expected Failures: " << expected << endl;
    cout << "FAILED: " << failed << endl;

    if(failed > 0) {
        return 1;
    }

    return 0;
}
