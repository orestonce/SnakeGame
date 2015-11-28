#-------------------------------------------------
#
# Project created by QtCreator 2015-11-28T15:17:45
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SnakeGame-qt
TEMPLATE = app


SOURCES += main.cpp\
		gui/SnakeGameWindow.cpp \
    core/Observer.cpp \
    core/Point.cpp \
    core/Snake.cpp \
    core/SnakeGame.cpp \
    core/Subject.cpp

HEADERS  += gui/SnakeGameWindow.h \
    core/Observer.h \
    core/Point.h \
    core/Snake.h \
    core/SnakeGame.h \
    core/Subject.h

FORMS    += gui/SnakeGameWindow.ui

RESOURCES += \
    gui/images.qrc
