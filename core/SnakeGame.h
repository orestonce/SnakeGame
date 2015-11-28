#ifndef RESTONCE_SNAKEGAME_H
#define RESTONCE_SNAKEGAME_H

#include "Subject.h"
#include "Snake.h"
#include <random>

namespace restonce {

class SnakeGame
        : public Subject
{
public:
    typedef Snake::Direction Direction;
    enum class Status {
        Undo, Runing, GameOver
    };
    SnakeGame(int maxX, int maxY, std::size_t destScore);
    void start();
    void stop();
    void turn(Direction direction);
    void timeout();
    // 用于GUI绘制
    Snake const& getSnake() const;
    Point const& getFood() const;
    Status getStatus() const;
    bool isWiner() const;
    std::size_t getWinerLength() const;
private:
    void randomFood();
private:
    Snake m_snake;
    Point  m_food;
    Status m_status;

    int m_maxX;
    int m_maxY;
    std::mt19937 m_rd;
    std::size_t m_winerLength;
};

} // namespace restonce

#endif // RESTONCE_SNAKEGAME_H
