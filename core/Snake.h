#ifndef RESTONCE_SNAKE_H
#define RESTONCE_SNAKE_H

#include "Point.h"
#include <list>

namespace restonce {

class Snake
{
public:
    enum class Direction {
        Up , Down, Left, Right
    };
    Snake(Point const& startPosition, std::size_t initLength, Direction initDirection);
    void start();
    void toDie();
    Point headFront() const;
    void increaseLength();
    void goAhead();
    bool setDirection(Direction direction);
    bool inBody(Point const& p) const;
    void updateDie(int maxX, int maxY);
    // 以下函数一般用于绘制GUI
    const std::list<Point> &getBodys() const;
    bool isAlive() const;
    std::size_t getLength() const;
private:
    std::list<Point> m_bodys;
    std::size_t m_destLength;
    Direction m_direction;
    bool m_alive;

    Point m_startPosition;
    std::size_t m_initLength;
    Direction m_initDirection;
};

} // namespace restonce

#endif // RESTONCE_SNAKE_H
