#include <fstream>
#include <stdexcept>
#include "JSONParser.hpp"

JSONParser::JSONParser()
{
}

void JSONParser::parseJSONFromFile(const std::string &jsonFilename, std::vector<Rectangle> &rectangleVector, const int rectangleLimit)
{
    int rectangleID = 1;
    
    try
    {
        //ifstream closes itself when it goes out of scope, RAII
        std::ifstream inputStream(jsonFilename);
        inputStream >> m_json;
    }
    catch(const std::invalid_argument &invFileEx)
    {
        std::cout<<"Exception attempting to open file: "<<invFileEx.what()<<std::endl;
        throw invFileEx;
    }
    
    for(auto& element : m_json) 
    {        
        for(auto& subElement: element)
        {
            int x = 0, y = 0, w = 0, h = 0;

            auto it = subElement.find("x");
            if (it != subElement.end()) 
            {
              x = it.value();
            }
            
            it = subElement.find("y");
            if (it != subElement.end()) 
            {
              y = it.value();
            }
            
            it = subElement.find("w");
            if (it != subElement.end()) 
            {
              w = it.value();
            }
            
            it = subElement.find("h");
            if (it != subElement.end()) 
            {
              h = it.value();
            }
            
            try
            {
                Rectangle tmpRectangle{rectangleID, x, y, w, h};
                rectangleVector.push_back(tmpRectangle);
            }
            catch(const std::invalid_argument &invEx)
            {
                std::cout<<"Exception - Rectangle number "+std::to_string(rectangleID)+": "<<invEx.what()<<std::endl;
                throw invEx;
            }
            
            if(rectangleID == rectangleLimit)
            {
                break;
            }
            else
            {
                rectangleID++;
            }
        }
    }    
}