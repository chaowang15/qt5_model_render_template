#-------------------------------------------------
#
# Project created by QtCreator 2018-03-12T23:01:24
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mesh_partition
TEMPLATE = app

# You can add `warn_off` in CONFIG to hide the warning messages during compilation
# CONFIG += c++11 warn_off
CONFIG += c++11 c++14
INCLUDEPATH += /usr/include/eigen3
SOURCES += main.cpp\
        mainwindow.cpp\
        covariance.cpp\
        glwidgetsettings.cpp \
    glwidget.cpp
HEADERS  += mainwindow.h\
        covariance.h\
        glwidgetsettings.h \
        glwidget.h
FORMS    += mainwindow.ui
