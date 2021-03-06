TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /home/kuba/Qt/Rozne/wiringPi

SOURCES += main.cpp \
    rpimpu6050.cpp \
    arduino_i2c.cpp

unix:!macx: LIBS += -L$$PWD/../../SFMLqt/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../SFMLqt/include
DEPENDPATH += $$PWD/../../SFMLqt/include

HEADERS += \
    rpimpu6050.h \
    arduino_i2c.h
unix:!macx: LIBS += -L$$PWD/../../SFMLqt/lib/ -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += $$PWD/../../SFMLqt/include
DEPENDPATH += $$PWD/../../SFMLqt/include
