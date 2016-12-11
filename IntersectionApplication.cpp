#include <stdexcept>
#include <fstream>
#include "IntersectionApplication.hpp"
#include "JSONParser.hpp"

IntersectionApplication::IntersectionApplication(){}

/* IntersectionApplication::execute:
 *          Read an input JSON file and finds the Intersections.
 * 
 * inputs:
 *          jsonFilename - Filepath of the input JSON rectangles 
 */ 
void IntersectionApplication::execute(const std::string &jsonFilename)
{
    JSONParser jsonParser;
    
    try
    {
        jsonParser.parseJSONFromFile(jsonFilename, m_rectangleVector, M_RECTANGLE_LIMIT);
    }
    catch (const std::exception &ex)
    {
        throw ex;
    }

    findAllIntersections();
}

/* IntersectionApplication::findAllIntersections: 
 *           Iterates throught the vector of Rectangles created
 *           from the input JSON file. For each Rectangle it creates
 *           a new vector of all of its intersections with the rest
 *           of the Rectangles after it in the vector. This way, we do
 *           not get repeating intersections generated. The new vector
 *           of intersections created is passed to findIntersectionsOfIntersections
 *                                                 
 * inputs:
 *         jsonFilename - Filepath of the input JSON rectangles 
 */ 
void IntersectionApplication::findAllIntersections()
{   
    const int count = m_rectangleVector.size();
    
    for(int i=0; i<count; i++)
    {
        std::vector<Rectangle> intersectionVector;
        int countOfIntersections = 0;
        std::set<std::set<int>> uniqueIntersections;
        
        for(int j=i+1; j<count; j++)
        {
            if(Rectangle::rectanglesIntersect(m_rectangleVector[i], m_rectangleVector[j]))
            {
                Rectangle intersection{m_rectangleVector[i], m_rectangleVector[j]};
                
                /* Copy intersection object here */
                intersectionVector.push_back(intersection);
                
                /* Insert this intersection into the final sorted result set */
                m_resultMap.insert({intersection.getIdSet(), intersection.toOutputString()});
                
                countOfIntersections++;
            }
        }
        
        if(countOfIntersections > 1)
        {
            findIntersectionsOfIntersections(intersectionVector, uniqueIntersections);
        }
    }
}

/* IntersectionApplication::findIntersectionsOfIntersections:
 *          Recursively finds where each intersection intersects with
 *          other intersections for the parent Rectangle. This is to
 *          detect intersections involving multiple parent Rectangles.
 * 
 * inputs:
 *         intersectionVector  - A vector or all intersections not yet handled, involving just 2 parent Rectangles, 
 *                               for a given rectangle
 *         uniqueIntersections - Used to enfore uniquness of intersections of intersections. Using this set rather
 *                               than the Result HashMap because the number of entries in this set is smaller.
 */
void IntersectionApplication::findIntersectionsOfIntersections(const std::vector<Rectangle> &intersectionVector, std::set<std::set<int>> &uniqueIntersections)
{
    const int count = intersectionVector.size();
    std::vector<Rectangle> newIntersectionVector;
    int countOfIntersections = 0;
    
    for(int i=0; i<count; i++)
    {
        for(int j=i+1; j<count; j++)
        {
            if(Rectangle::rectanglesIntersect(intersectionVector[i], intersectionVector[j]))
            {
                Rectangle intersection{intersectionVector[i], intersectionVector[j]};
                
                if(uniqueIntersections.find(intersection.getIdSet()) == uniqueIntersections.end())
                {
                    /* Copy intersection object here */
                    newIntersectionVector.push_back(intersection);
                    
                    /* Insert this new set into the unique set */
                    uniqueIntersections.insert(intersection.getIdSet());
                    
                    /* Insert into result map */
                    m_resultMap.insert({intersection.getIdSet(), intersection.toOutputString()});
                    countOfIntersections++;
                }
            }
        }
    }
    
    if(countOfIntersections > 1)
    {
        findIntersectionsOfIntersections(newIntersectionVector, uniqueIntersections);
    }
}

/* IntersectionApplication::printOutputToConsole:
 *          Prints the output to console.
 * 
 */
void IntersectionApplication::printOutputToConsole()
{
    //Print the input first...
    std::cout<<"Input:\n";
    for(Rectangle& eachInputRectangle : m_rectangleVector)
    {
        std::cout<<"\t"<<eachInputRectangle.toInputString()<<std::endl;
    }
    
    //... now the intersection output
    std::cout<<"\nIntersections\n";
    for(const auto eachIntersection : m_resultMap)
    {
        std::cout<<"\t"<<eachIntersection.second<<std::endl;
    }  
}

/* IntersectionApplication::printOutputToFile:
 *          Prints the output to console.
 * 
 * inputs:
 *          filename - Filepath to output to
 */
void IntersectionApplication::printOutputToFile(const std::string& filename)
{
    //ofstream closes itself when it goes out of scope, RAII
    std::ofstream outputFile(filename, std::ofstream::out);
    
    //Print the input first...
    outputFile<<"Input:\n";
    for(Rectangle& eachInputRectangle : m_rectangleVector)
    {
        outputFile<<"\t"<<eachInputRectangle.toInputString()<<std::endl;
    }
    
    //... now the intersection output
    outputFile<<"\nIntersections\n";
    for(const auto eachIntersection : m_resultMap)
    {
        outputFile<<"\t"<<eachIntersection.second<<std::endl;
    }
}