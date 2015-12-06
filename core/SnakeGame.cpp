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
    // 启动游戏，需要保证游戏没有运行
    if ( m_status != Status::Runing ) {
        // 更新游戏状态、蛇状态，产生食物
        m_status = Status::Runing;
        m_snake.start();
        randomFood();
        // 通知观察者，自身已经改变
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

void SnakeGame::setDirection (Direction direction)
{
    if ( m_snake.isAlive() ) {
        if ( m_snake.setDirection (direction) ) {
            timeout ();
        }
    }
}

void SnakeGame::timeout ()
{
    if ( m_status != Status::Runing) {
        return ;
    }
    // 2015-12-06 : 删除多于的验证是否为胜利者的操作
    // 原因：每次在之后都会验证并更新胜利者状态
    //         && !isWiner ()
    if ( m_food == m_snake.headFront () ) {
        m_snake.increaseLength ();
        m_snake.goAhead ();
        if ( !isWiner () ) { // here
            randomFood ();
            m_snake.updateDie(m_maxX, m_maxY);
            if ( !m_snake.isAlive () ) { // 蛇死了，你输了
                m_status = Status::GameOver;
            }
        } else {
            // 你已经赢了
            m_status = Status::GameOver;
        }
    } else {
        m_snake.updateDie(m_maxX, m_maxY);
        if ( !m_snake.isAlive () ) { // 蛇死了，你输了
            m_status = Status::GameOver;
        } else {
            m_snake.goAhead ();
        }
    }
    notifyObservers ();
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
