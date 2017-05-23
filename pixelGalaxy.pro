#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T15:57:04
#
#-------------------------------------------------

QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixelGalaxy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    bullet.cpp \
    player.cpp \
    game.cpp \
    score.cpp \
    bonus.cpp \
    meteorite.cpp \
    bosstype1.cpp \
    enemytype2.cpp \
    enemytype1.cpp \
    enemytype3.cpp \
    button.cpp

HEADERS  += \
    bullet.h \
    player.h \
    game.h \
    score.h \
    bonus.h \
    meteorite.h \
    bosstype1.h \
    enemytype2.h \
    enemytype1.h \
    enemytype3.h \
    button.h

RESOURCES += \
    res.qrc
