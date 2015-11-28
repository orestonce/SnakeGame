#include "Point.h"

namespace restonce {

Point::Point(int x, int y)
    : m_x(x), m_y(y)
{
}

int Point::getX () const
{
    return m_x;
}

int Point::getY () const
{
    return m_y;
}

void Point::setX (int x)
{
    m_x = x;
}

void Point::setY (int y)
{
    m_y = y;
}

bool operator == (const Point& p1, const Point& p2)
{
    return p1.getX () == p2.getX () && p1.getY () == p2.getY ();
}

} // namespace restonce
