#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T10:54:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StepperAndDCController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    steppercontrolwidget.cpp \
    steppersettingsdialog.cpp \
    steppersettingswidget.cpp \
    dcmotorcontrolwidget.cpp

HEADERS  += mainwindow.h \
    steppercontrolwidget.h \
    steppersettingsdialog.h \
    steppersettingswidget.h \
    dcmotorcontrolwidget.h

FORMS    += mainwindow.ui \
    steppercontrolwidget.ui \
    steppersettingsdialog.ui \
    steppersettingswidget.ui \
    dcmotorcontrolwidget.ui
