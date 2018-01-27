TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /home/kuba/Qt/wiringPi

SOURCES += main.cpp \
    rpimpu6050.cpp \
    pid.cpp \
    arducomm.cpp

unix:!macx: LIBS += -L$$PWD/../../SFMLqt/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../SFMLqt/include
DEPENDPATH += $$PWD/../../SFMLqt/include

HEADERS += \
    rpimpu6050.h \
    pid.h \
    arducomm.h
unix:!macx: LIBS += -L$$PWD/../../SFMLqt/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../SFMLqt/include
DEPENDPATH += $$PWD/../../SFMLqt/include
