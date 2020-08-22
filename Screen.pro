#-------------------------------------------------
#
# Project created by QtCreator 2019-05-22T17:11:02
#
#-------------------------------------------------

TARGET = Screen
TEMPLATE = lib

DEFINES += SCREEN_LIBRARY
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += D:\git\CameroNet

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    screentoolbar.cpp \
    screen.cpp \
    soundpushbutton.cpp

HEADERS += \
        screen_global.h \ 
    screentoolbar.h \
    screen.h \
    soundpushbutton.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS +=

RESOURCES += \
    images.qrc
