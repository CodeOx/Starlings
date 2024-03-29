#-------------------------------------------------
#
# Project created by QtCreator 2018-04-13T15:08:41
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += -lglu32 -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StarlingsUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += "C:\Users\HP\Documents\iit_acad\cop290\StalingsPackage\Starlings\obj\Boid.o" \
#        "C:\Users\HP\Documents\iit_acad\cop290\StalingsPackage\Starlings\obj\Swarm.o" \
#        "C:\Users\HP\Documents\iit_acad\cop290\StalingsPackage\Starlings\obj\Vector.o"

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    glwidget.cpp \
    ../srcs/Boid.cpp \
    ../srcs/Swarm.cpp \
    ../srcs/Vector.cpp

HEADERS += \
        mainwindow.h \
    glwidget.h \
    ../headers/Boid.h \
    ../headers/Swarm.h \
    ../headers/Vector.h

FORMS += \
        mainwindow.ui
