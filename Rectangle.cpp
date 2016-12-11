#include "Rectangle.hpp"
#include <stdexcept>
#include <set>

Rectangle::Rectangle(const int singleId, const int x, const int y, const int w, const int h)
    : m_x{x}, m_y{y}, m_w{w}, m_h{h} 
{
    (m_w > 0) ? m_w = w : throw std::invalid_argument("Width must be greater than 0!");
    (m_h > 0) ? m_h = h : throw std::invalid_argument("Height must be greater than 0!");
    (singleId > 0) ? m_setOfParentRectangles.insert(singleId) : throw std::invalid_argument("ID must be greater than 0!");
}

Rectangle::Rectangle(const Rectangle &rectA, const Rectangle &rectB)
{
    /* Confirm they intersect */
    if(Rectangle::rectanglesIntersect(rectA, rectB))
    {
        /* Set the coordinates */
        m_x = rectA.X1() > rectB.X1() ? rectA.X1() : rectB.X1();//larger X1
        m_y = rectA.Y1() > rectB.Y1() ? rectA.Y1() : rectB.Y1();//larger Y1
        m_w = (rectA.X2() < rectB.X2() ? rectA.X2() : rectB.X2()) - m_x;//smaller X2
        m_h = (rectA.Y2() < rectB.Y2() ? rectA.Y2() : rectB.Y2()) - m_y;//smaller Y2
        
        /* Set the Parent IDs */
        std::set<int> idSetUnion;
        std::set<int> rectangleAIds = rectA.getIdSet();
        std::set<int> rectangleBIds = rectB.getIdSet();
        idSetUnion.insert(rectangleAIds.begin(), rectangleAIds.end());
        idSetUnion.insert(rectangleBIds.begin(), rectangleBIds.end());
        this->setIdSet(idSetUnion);
    }
    else
    {
        throw std::invalid_argument("Rectangles passed to constructor do not intersect!");
    }
}
    
Rectangle::Rectangle()
    : m_x{0}, m_y{0}, m_w{0}, m_h{0} 
{ 

}

bool Rectangle::rectanglesIntersect(const Rectangle &rectangleA, const Rectangle &rectangleB)
{
    bool aToTheRightOfB = rectangleA.X1() > rectangleB.X2();
    bool aToTheLeftOfB = rectangleA.X2() < rectangleB.X1();   
    bool aIsBelowB = rectangleA.Y1() > rectangleB.Y2();    
    bool aIsAboveB = rectangleA.Y2() < rectangleB.Y1();

    return (aToTheRightOfB || aToTheLeftOfB || aIsBelowB || aIsAboveB) ? false : true;
}

std::set<int> Rectangle::getIdSet() const
{
    return m_setOfParentRectangles;
}

void Rectangle::setIdSet(const std::set<int> &inputSet)
{
    m_setOfParentRectangles.clear();
    m_setOfParentRectangles.insert(inputSet.begin(), inputSet.end());
}

std::string Rectangle::getIdString() const
{
    std::string str = "";
    int countOfIds = m_setOfParentRectangles.size();
    int countOfIdsProcessed = 0;
    
    for(auto eachId : m_setOfParentRectangles)
    {
        countOfIdsProcessed++;
        if(countOfIdsProcessed == countOfIds)
        {
            str += (std::to_string(eachId));
        }
        else if(countOfIdsProcessed+1 == countOfIds)
        {
            str += (std::to_string(eachId)+" and ");
        }
        else
        {
            str += (std::to_string(eachId)+", ");
        }
    }
    return str;
}

int Rectangle::X1() const
{
    return m_x;
}

int Rectangle::X2() const
{
    return m_x+m_w;
}

int Rectangle::Y1() const
{
    return m_y;
}

int Rectangle::Y2() const
{
    return m_y+m_h;
}

std::string Rectangle::toInputString() const
{
    std::string str = this->getIdString()+": Rectangle at ("
                            +std::to_string(m_x)+","
                            +std::to_string(m_y)+"), w="
                            +std::to_string(m_w)+", h="
                            +std::to_string(m_h)+".";
    return str;
}

std::string Rectangle::toOutputString() const
{
    std::string str = "Between rectangle "+this->getIdString()+" at ("
                            +std::to_string(m_x)+","
                            +std::to_string(m_y)+"), w="
                            +std::to_string(m_w)+", h="
                            +std::to_string(m_h)+".";
    return str;
}

std::string Rectangle::toJSONString() const
{
    std::string str = "{\"x\": "+std::to_string(m_x)+
                     ", \"y\": "+std::to_string(m_y)+
                     ", \"w\": "+std::to_string(m_w)+
                     ", \"h\": "+std::to_string(m_h)+"}";
    return str;
}

std::string Rectangle::toCartesianString() const
{
    std::string str = "{\"X1\": "+std::to_string(X1())+
                     ", \"Y1\": "+std::to_string(Y1())+
                     ", \"X2\": "+std::to_string(X2())+
                     ", \"Y2\": "+std::to_string(Y2())+"}";
    return str;
}

