#ifndef RESULTMAP_HPP
#define RESULTMAP_HPP
#include <set>
#include <map>

/* Used for comparing intersections in this order:
 * 1) Count of parent rectangles that make up intersection
 * 2) Numerical ordering of the IDs of the parent rectangles
 * 
 */
struct intersectionCompare 
{
    bool operator()(const std::set<int>& a, const std::set<int>& b) const 
    {
        if(a.size() != b.size())
        {
            return a.size() < b.size();
        }
        else
        {
            return a < b;
        }
    }
};
typedef std::map<std::set<int>, std::string, intersectionCompare> ResultMap;
/*
class ResultMap
{
private:
    std::map<std::set<int>, std::string, intersectionCompare> m_orderedResultMap;
    
public:
    ResultMap();
    std::map<std::set<int>, std::string, intersectionCompare>& getResultMap();
    void printResults() const;
    void printResultsToFile(const std::string &filename) const;
};
*/
#endif // RESULTMAP_HPP
