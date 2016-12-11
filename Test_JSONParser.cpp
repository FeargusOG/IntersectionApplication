#include <vector>
#include "catch.hpp"
#include "JSONParser.hpp"
#include "Rectangle.hpp"

TEST_CASE( "JsonParser_PopulateVector", "[jsonParse]" ) 
{
    JSONParser jParse;    
    std::vector<Rectangle> testRectangleVector;
    jParse.parseJSONFromFile("__BASE_sample.json", testRectangleVector, 1000);
    
    std::vector<Rectangle> goldRectangleVector;
    Rectangle sample1{1, 100, 100, 250, 80};
    Rectangle sample2{2, 120, 200, 250, 150};
    Rectangle sample3{3, 140, 160, 250, 100};
    Rectangle sample4{4, 160, 140, 350, 190};
    goldRectangleVector.push_back(sample1);
    goldRectangleVector.push_back(sample2);
    goldRectangleVector.push_back(sample3);
    goldRectangleVector.push_back(sample4);
    
    bool matching = true;
    int i = 0;
    for(Rectangle& eachRect : testRectangleVector)
    {
        if(eachRect.toInputString() != goldRectangleVector[i++].toInputString())
        {
            matching = false;
            break;
        }
    }
    
    REQUIRE( matching == true );
}