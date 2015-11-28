#include "SnakeGame.h"
#include <ctime>

namespace restonce {

SnakeGame::SnakeGame(int maxX, int maxY, std::size_t destScore)
    : m_snake( Point(0, 0) , 3, Direction::Down),
      m_status(Status::Undo),
      m_maxX(maxX), m_maxY(maxY),
      m_winerLength(destScore)
{
    m_rd.seed (time(NULL));
}

void SnakeGame::start ()
{
    if ( m_status != Status::Runing ) {
        m_status = Status::Runing;
        m_snake.start();
        randomFood();
        notifyObservers ();
    }
}

void SnakeGame::stop ()
{
    if ( m_status == Status::Runing ) {
        m_status = Status::GameOver;
        m_snake.toDie();
        notifyObservers ();
    }
}

void SnakeGame::turn (Direction direction)
{
    if ( m_snake.isAlive() ) {
        if ( m_snake.setDirection (direction) ) {
            timeout ();
        }
    }
}

void SnakeGame::timeout ()
{
    if ( m_status == Status::Runing && !isWiner () ) {
        if ( m_food == m_snake.headFront () ) {
            m_snake.increaseLength ();
            if ( !isWiner () ) {
                randomFood ();
            }
        }
        m_snake.goAhead ();
        m_snake.updateDie(m_maxX, m_maxY);

        if ( !m_snake.isAlive () || isWiner ()) {
            m_status = Status::GameOver;
        }

        notifyObservers ();
    }
}

Snake const& SnakeGame::getSnake() const
{
    return m_snake;
}

Point const& SnakeGame::getFood() const
{
    return m_food;
}

SnakeGame::Status SnakeGame::getStatus () const
{
    return m_status;
}

bool SnakeGame::isWiner () const
{
    return m_winerLength <= m_snake.getLength() &&
            m_status != Status::Undo ;
}

std::size_t SnakeGame::getWinerLength () const
{
    return m_winerLength;
}

void SnakeGame::randomFood ()
{
    do {
        int x = m_rd() % m_maxX;
        int y = m_rd() % m_maxY;

        m_food.setX (x);
        m_food.setY (y);
    } while ( m_snake.inBody(m_food) );

}

} // namespace restonce
