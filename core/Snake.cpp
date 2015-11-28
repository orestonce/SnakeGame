#include "Snake.h"
#include <algorithm>

namespace restonce {

Snake::Snake(const Point &startPosition, std::size_t initLength, Direction initDirection)
    : m_startPosition(startPosition), m_initLength(initLength),
      m_initDirection(initDirection)
{

}

void Snake::start ()
{
    m_bodys.clear ();
    m_bodys.push_front (m_startPosition);
    m_destLength = m_initLength;
    m_direction = m_initDirection;
    m_alive = true;
}

void Snake::toDie ()
{
    m_alive = false;
}

bool Snake::setDirection (Direction direction)
{
    bool result = false;

    if ( isAlive () ) {
        switch ( direction )
        {
        case Direction::Down :
            if ( m_direction != Direction::Up ) {
                m_direction = direction;
                result = true;
            }
            break;
        case Direction::Up:
            if ( m_direction != Direction::Down ) {
                m_direction = direction;
                result = true;
            }
            break;
        case Direction::Left:
            if ( m_direction != Direction::Right ) {
                m_direction = direction;
                result = true;
            }
            break;
        case Direction::Right:
            if ( m_direction != Direction::Left ) {
                m_direction = direction;
                result = true;
            }
            break;
        default:
            break;
        }
    }
    return result;
}

Point Snake::headFront () const
{
    Point front ( m_bodys.front () ) ;

    switch ( m_direction )
    {
    case Direction::Up:
        front.setY ( front.getY () - 1 );
        break;
    case Direction::Down:
        front.setY ( front.getY () + 1 );
        break;
    case Direction::Left :
        front.setX ( front.getX () - 1 );
        break;
    case Direction::Right :
        front.setX ( front.getX () + 1 );
        break;
    default :
        break;
    }
    return front;
}

void Snake::increaseLength ()
{
    if ( isAlive () ) {
        ++ m_destLength ;
    }
}

void Snake::goAhead ()
{
    if ( isAlive () ) {
        Point front = headFront ();
        m_bodys.push_front ( front );
        if ( m_bodys.size () > m_destLength ) {
            m_bodys.pop_back ();
        }
    }
}



bool Snake::isAlive () const
{
    return m_alive;
}

std::size_t Snake::getLength () const
{
    return m_destLength;
}

bool Snake::inBody (const Point &p) const
{
    return std::find(m_bodys.begin (), m_bodys.end (), p) != m_bodys.end () ;
}

void Snake::updateDie (int x, int y)
{
    if ( !m_alive ) {
        return ;
    }
    for(Point const& p: m_bodys)
    {
        if ( std::count(m_bodys.begin (), m_bodys.end (), p) > 1 ) {
            m_alive = false;
            break;
        }
    }
    if ( m_alive ) {
        Point const& head = m_bodys.front ();

        if ( head.getX () >= x  || head.getX () < 0 ||
             head.getY () >= y || head.getY () < 0 ) {
            m_alive = false;
        }
    }
}

const std::list<Point>& Snake::getBodys() const
{
    return m_bodys;
}

} // namespace restonce
