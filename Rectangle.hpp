#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <string>
#include <set>

class Rectangle
{
private:
    std::set<int> m_setOfParentRectangles;
    int m_x;
    int m_y;
    int m_w;
    int m_h;
    
public:
    /* Regular Rectangles call this constructor */
    Rectangle(const int singleId, const int x, const int y, const int w, const int h);
    /* Rectangles formed through intersection call this */
    Rectangle(const Rectangle &rectA, const Rectangle &rectB);
    Rectangle();
    
    static bool rectanglesIntersect(const Rectangle &rectangleA, const Rectangle &rectangleB);

    std::set<int> getIdSet() const;
    void setIdSet(const std::set<int> &inputSet);
    std::string getIdString() const;
    
    int X1() const;
    int X2() const;
    int Y1() const;
    int Y2() const;
    
    std::string toInputString() const;
    std::string toOutputString() const;
    std::string toJSONString() const;
    std::string toCartesianString() const;
};

#endif // RECTANGLE_HPP
