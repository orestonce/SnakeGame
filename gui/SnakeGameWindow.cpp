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
    // 观察游戏内核对象
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
    // 内核发生改变后，更新界面元素。
    // 由于蛇、食物、墙无法在此处更新，就需要立即重绘
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

    typedef restonce::Point Point;

    // 画墙
    for(int x=-1; x<=MAX_X; ++x)
    {
        drawImage (Point (x, -1), wall);
        drawImage (Point (x, MAX_Y), wall);
    }
    for(int y=-1; y<=MAX_Y; ++y)
    {
        drawImage (Point (-1,  y), wall);
        drawImage (Point (MAX_X, y), wall);
    }
    // 画蛇的身体
    for(restonce::Point const & p : m_game.getSnake ().getBodys () )
    {
        drawImage (p, body);
    }
    // 画蛇头和食物
    if ( restonce::SnakeGame::Status::Undo != m_game.getStatus () ) {
        restonce::Point p = m_game.getFood ();
        drawImage (p, food);
        p = m_game.getSnake ().getBodys ().front ();
        drawImage (p, head);
    }
}

void SnakeGameWindow::keyPressEvent (QKeyEvent *e)
{
    using restonce::SnakeGame;
    // 将按键信息转化成对内核对象的控制信息
    switch (e->key ()) {
    case Qt::Key_Up:
        m_game.setDirection (SnakeGame::Direction::Up);
        break;
    case Qt::Key_Down:
        m_game.setDirection (SnakeGame::Direction::Down);
        break;
    case Qt::Key_Left:
        m_game.setDirection (SnakeGame::Direction::Left);
        break;
    case Qt::Key_Right:
        m_game.setDirection (SnakeGame::Direction::Right);
        break;
    default:
        break;
    }
}

QRect SnakeGameWindow::getRect (restonce::Point const& p)
{
    QPoint topLeft(60, 60);
    int boxSize = 15;

    topLeft.rx () += p.getX() * boxSize;
    topLeft.ry () += p.getY() * boxSize;

    return QRect(topLeft.x (), topLeft.y (), boxSize, boxSize );
}

void SnakeGameWindow::drawImage (const restonce::Point& p,const QImage &image)
{
    QPainter painter(this);
    painter.drawImage( getRect (p), image);
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
    // 将定时器信息转化成控制信息
    m_game.timeout ();
    // 若游戏已停止运行，则弹出窗口显示玩家状态
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
