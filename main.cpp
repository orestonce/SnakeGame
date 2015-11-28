#include "gui/SnakeGameWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeGameWindow w;
    w.show();

    return a.exec();
}
