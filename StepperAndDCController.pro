#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T10:54:34
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StepperAndDCController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    steppercontrolwidget.cpp \
    steppersettingsdialog.cpp \
    steppersettingswidget.cpp \
    dcmotorcontrolwidget.cpp \
    stepperwidgetcontroller.cpp \
    dcmotorwidgetcontroller.cpp \
    dcmotor.cpp \
    steppermotor.cpp

HEADERS  += mainwindow.h \
    steppercontrolwidget.h \
    steppersettingsdialog.h \
    steppersettingswidget.h \
    dcmotorcontrolwidget.h \
    stepperwidgetcontroller.h \
    dcmotorwidgetcontroller.h \
    dcmotor.h \
    steppermotor.h

FORMS    += mainwindow.ui \
    steppercontrolwidget.ui \
    steppersettingsdialog.ui \
    steppersettingswidget.ui \
    dcmotorcontrolwidget.ui
