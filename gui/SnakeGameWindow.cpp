#include "SnakeGameWindow.h"
#include "ui_SnakeGameWindow.h"
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

SnakeGameWindow::SnakeGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SnakeGameWindow), m_game(MAX_X, MAX_Y, 25)
{
    ui->setupUi(this);
    m_game.attachObserver (this);
    connect (&m_timer, SIGNAL(timeout()),
             this, SLOT(slot_timeout()));
}

SnakeGameWindow::~SnakeGameWindow()
{
    delete ui;
}

void SnakeGameWindow::onSubjectChanged ()
{
    typedef restonce::SnakeGame::Status Status;
    QString gameStatus ;
    switch ( m_game.getStatus () )
    {
    case Status::Runing:
        gameStatus = trUtf8("当前状态：正在游戏");
        break;
    case Status::Undo:
        gameStatus = trUtf8("当前状态：未开始");
        break;
    case Status::GameOver:
        gameStatus = trUtf8("当前状态：游戏结束");
        break;
    default :
        break;
    }

    ui->label_gameStatus->setText (gameStatus);
    if ( m_game.getStatus () != Status::Undo ) {
        ui->label_destLength->setText (trUtf8 ("当前进度：%0/%1").arg (
                                           m_game.getSnake ().getLength ()).arg (
                                           m_game.getWinerLength ()));
    }
    repaint ();
}

void SnakeGameWindow::paintEvent (QPaintEvent *)
{
    QImage wall(":/images/wall.png");
    QImage body(":/images/body.png");
    QImage food(":/images/food.png");
    QImage head(":/images/head.png");

    QPainter painter(this);

    for(int x=-1; x<=MAX_X; ++x)
    {
        painter.drawImage (getRect (x, -1), wall);
        painter.drawImage (getRect (x, MAX_Y), wall);
    }
    for(int y=-1; y<=MAX_Y; ++y)
    {
        painter.drawImage (getRect (-1,  y), wall);
        painter.drawImage (getRect (MAX_X, y), wall);
    }

    for(restonce::Point const & p : m_game.getSnake ().getBodys () )
    {
        painter.drawImage (getRect (p.getX (), p.getY ()), body);
    }

    if ( restonce::SnakeGame::Status::Undo != m_game.getStatus () ) {
        restonce::Point p = m_game.getFood ();
        painter.drawImage (getRect (p.getX (), p.getY ()), food);
        p = m_game.getSnake ().getBodys ().front ();
        painter.drawImage (getRect (p.getX (), p.getY ()), head);
    }
}

void SnakeGameWindow::keyPressEvent (QKeyEvent *e)
{
    using restonce::SnakeGame;

    switch (e->key ()) {
    case Qt::Key_Up:
        m_game.turn (SnakeGame::Direction::Up);
        break;
    case Qt::Key_Down:
        m_game.turn (SnakeGame::Direction::Down);
        break;
    case Qt::Key_Left:
        m_game.turn (SnakeGame::Direction::Left);
        break;
    case Qt::Key_Right:
        m_game.turn (SnakeGame::Direction::Right);
        break;
    default:
        break;
    }
}

QRect SnakeGameWindow::getRect (int x, int y)
{
    QPoint topLeft(60, 60);
    int boxSize = 15;

    topLeft.rx () += x * boxSize;
    topLeft.ry () += y * boxSize;

    return QRect(topLeft.x (), topLeft.y (), boxSize, boxSize );
}

void SnakeGameWindow::on_action_startGame_triggered()
{
    if ( m_game.getStatus () != restonce::SnakeGame::Status::Runing ) {
        m_timer.start (500);
        m_game.start ();
    }
}

void SnakeGameWindow::on_action_stopGame_triggered()
{
    if ( m_game.getStatus () == restonce::SnakeGame::Status::Runing ) {
        m_timer.stop ();
        m_game.stop ();
    }
}

void SnakeGameWindow::slot_timeout ()
{
    m_game.timeout ();
    if ( m_game.getStatus () != restonce::SnakeGame::Status::Runing ) {
        m_timer.stop ();
        QString result ;
        if ( m_game.isWiner () ) {
            result = trUtf8("游戏结束，你赢了！");
        } else {
            result = trUtf8("游戏结束，你输了！");
        }
        QMessageBox::about (this, trUtf8("游戏结束"), result );
    }
}
