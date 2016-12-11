#include <fstream>
#include "catch.hpp"
#include "IntersectionApplication.hpp"

TEST_CASE( "IntersectionApplication_EndToEnd", "[endToEnd]" ) 
{
    IntersectionApplication testApp;
    testApp.execute("__BASE_sample.json");
    testApp.printOutputToFile("__TEST_output.out");
    
    //Very small output files, so its acceptable to copy into string for simplcitity
    std::ifstream goldFile("__BASE_output.out");
    std::string goldStr((std::istreambuf_iterator<char>(goldFile)), std::istreambuf_iterator<char>());
    goldFile.close();
    
    std::ifstream testFile("__TEST_output.out");
    std::string testStr((std::istreambuf_iterator<char>(testFile)), std::istreambuf_iterator<char>());
    testFile.close();
    
    REQUIRE( goldStr == testStr );
}