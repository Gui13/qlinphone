
QT += core gui widgets quick quickwidgets

TARGET = qlinphone
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS_WARN_ON = -Wall -Wno-unused-parameter -Wno-unused-variable

SOURCES += main.cpp\
        ui/linphonewindow.cpp \
    qlinphonecore.cpp \
    models/qlchatroom.cpp \
    qlmessage.cpp \
    ui/accountpreferences.cpp \
    qlproxy.cpp

HEADERS  += ui/linphonewindow.h \
    qlinphonecore.h \
    models/qlchatroom.h \
    qlmessage.h \
    ui/accountpreferences.h \
    qlproxy.h

FORMS    += ui/linphonewindow.ui \
    ui/accountpreferences.ui

LIBS += -llinphone -lmediastreamer_base -lmediastreamer_voip -lortp
INCLUDEPATH += ui models

macx:LIBS+= -L/usr/local/lib
macx:INCLUDEPATH += /usr/local/include

DISTFILES += \
    ui/qml/ChatListForm.ui.qml
