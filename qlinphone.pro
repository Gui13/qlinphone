#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T18:48:49
#
#-------------------------------------------------

QT += core gui widgets

TARGET = qlinphone
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter -Wno-unused-variable

SOURCES += main.cpp\
        linphonewindow.cpp \
    qlinphonecore.cpp \
    qlchatrooms.cpp \
    qlchatroom.cpp \
    qlmessage.cpp \
    accountpreferences.cpp \
    qlproxy.cpp

HEADERS  += linphonewindow.h \
    qlinphonecore.h \
    qlchatrooms.h \
    qlchatroom.h \
    qlmessage.h \
    accountpreferences.h \
    qlproxy.h

FORMS    += linphonewindow.ui \
    accountpreferences.ui

LIBS += -L/usr/local/lib/ -llinphone -lmediastreamer_base -lmediastreamer_voip -lortp
INCLUDEPATH += /usr/local/include
