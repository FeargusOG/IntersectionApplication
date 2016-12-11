#ifndef INTERSECTIONAPPLICATION_HPP
#define INTERSECTIONAPPLICATION_HPP

#include <vector>
#include <string>
#include "Rectangle.hpp"
#include "ResultMap.hpp"

class IntersectionApplication
{
private:
    const int M_RECTANGLE_LIMIT{1000};
    ResultMap m_resultMap;
    std::vector<Rectangle> m_rectangleVector;
    
    void findAllIntersections();
    void findIntersectionsOfIntersections(const std::vector<Rectangle> &intersectionVector, 
        std::set<std::set<int>> &uniqueIntersections);

public:
    IntersectionApplication();
    void execute(const std::string &jsonFilename);
    void printOutputToConsole();
    void printOutputToFile(const std::string& filename);
};
#endif // INTERSECTIONAPPLICATION_HPP
