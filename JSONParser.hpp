#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP
#include <string>
#include "Rectangle.hpp"
#include "json.hpp"

class JSONParser
{
private:
    nlohmann::json m_json;
    
public:
    JSONParser();
    void parseJSONFromFile(const std::string &jsonFilename, std::vector<Rectangle> &rectangleVector, const int rectangleLimit);
};

#endif // JSONPARSER_HPP
