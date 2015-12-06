#ifndef SNAKEGAMEWINDOW_H
#define SNAKEGAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "core/SnakeGame.h"
#include "core/Observer.h"

namespace Ui {
class SnakeGameWindow;
}

class SnakeGameWindow
        : public QMainWindow, public restonce::Observer
{
    Q_OBJECT
    enum {
        MAX_X = 20,
        MAX_Y = 20
    };
public:
    explicit SnakeGameWindow(QWidget *parent = 0);
    ~SnakeGameWindow();
protected:
    virtual void onSubjectChanged() override final;
    virtual void paintEvent (QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *);

private slots:
    void on_action_startGame_triggered();

    void on_action_stopGame_triggered();
    void slot_timeout();
private:
    QRect getRect(const restonce::Point &p);
    void drawImage(const restonce::Point &p, const QImage &image);
private:
    Ui::SnakeGameWindow *ui;
    restonce::SnakeGame m_game;
    QTimer m_timer;
};

#endif // SNAKEGAMEWINDOW_H
