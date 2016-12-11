#include <stdexcept>
#include <iostream>
#include "catch.hpp"
#include "Rectangle.hpp"

TEST_CASE( "RectangleConstructor_ValidArgs", "[rectConstructors]" ) 
{
    //All args valid
    try
    {
        Rectangle testRect{1, 100, 200, 300, 400};
        REQUIRE(true == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

TEST_CASE( "RectangleConstructor_InvalidId", "[rectConstructors]" ) 
{
    //Invalid ID
    try
    {
        Rectangle testRect{-1, 100, 200, 300, 400};
        REQUIRE(false == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(true == true);
    }
}

TEST_CASE( "RectangleConstructor_InvalidWidth", "[rectConstructors]" ) 
{
    //Invalid Width
    try
    {
        Rectangle testRect{1, 100, 200, -300, 400};
        REQUIRE(false == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(true == true);
    }
}

TEST_CASE( "RectangleConstructor_InvalidHeight", "[rectConstructors]" ) 
{
    //Invalid Height
    try
    {
        Rectangle testRect{1, 100, 200, 300, -400};
        REQUIRE(false == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(true == true);
    }
}

TEST_CASE( "IntersectionConstructor_ValidArgs", "[rectConstructors]" ) 
{
    //Rectangles that intersect
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        Rectangle rectB{3, 140, 160, 250, 100};
        Rectangle intersection(rectA, rectB);
        REQUIRE(true == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

TEST_CASE( "IntersectionConstructor_InvalidArgs", "[rectConstructors]" ) 
{    
    //Rectangles that do not intersect
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        Rectangle rectB{2, 120, 200, 250, 150};
        Rectangle intersection(rectA, rectB);
        REQUIRE(false == true);
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(true == true);
    }
}

TEST_CASE( "IntersectionGetters_CartesianCoords", "[rectGetters]" ) 
{
    //Correct intersection formed
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        REQUIRE(rectA.X1() == 100);
        REQUIRE(rectA.X2() == 350);
        REQUIRE(rectA.Y1() == 100);
        REQUIRE(rectA.Y2() == 180);
        REQUIRE(rectA.getIdString() == "1");
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

TEST_CASE( "IntersectionGetters_toString", "[rectGetters]" )
{
    //Correct toString is returned
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        REQUIRE(rectA.toInputString() == "1: Rectangle at (100,100), w=250, h=80.");
        REQUIRE(rectA.toOutputString() == "Between rectangle 1 at (100,100), w=250, h=80.");
        REQUIRE(rectA.toJSONString() == "{\"x\": 100, \"y\": 100, \"w\": 250, \"h\": 80}");
        REQUIRE(rectA.toCartesianString() == "{\"X1\": 100, \"Y1\": 100, \"X2\": 350, \"Y2\": 180}");
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

TEST_CASE( "IntersectionConstructor_CorrectIntersectionFormed", "[rectConstructors]" ) 
{
    //Correct intersection formed
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        Rectangle rectB{3, 140, 160, 250, 100};
        Rectangle intersection(rectA, rectB);
        REQUIRE(intersection.X1() == 140);
        REQUIRE(intersection.X2() == 350);
        REQUIRE(intersection.Y1() == 160);
        REQUIRE(intersection.Y2() == 180);
        REQUIRE(intersection.getIdString() == "1 and 3");
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

TEST_CASE( "IntersectionConstructor_IntersectionWithIntersection", "[rectConstructors]" ) 
{
    //Correct intersection formed
    try
    {
        Rectangle rectA{1, 100, 100, 250, 80};
        Rectangle rectB{3, 140, 160, 250, 100};
        Rectangle rectC{4, 160, 160, 350, 190};
        Rectangle intersectionA(rectA, rectB);
        Rectangle intersectionB(rectA, rectC);
        Rectangle intersectionC(intersectionA, intersectionB);
        REQUIRE(intersectionC.X1() == 160);
        REQUIRE(intersectionC.X2() == 350);
        REQUIRE(intersectionC.Y1() == 160);
        REQUIRE(intersectionC.Y2() == 180);
        REQUIRE(intersectionC.getIdString() == "1, 3 and 4");
    }
    catch(std::invalid_argument ex)
    {
        REQUIRE(false == true);
    }
}

