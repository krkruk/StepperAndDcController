#-------------------------------------------------
#
# Project created by QtCreator 2016-01-15T10:54:34
#
#-------------------------------------------------

QT       += core gui serialport
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StepperAndDCController
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    StepperMotor/steppercontrolwidget.cpp \
    StepperMotor/steppersettingsdialog.cpp \
    StepperMotor/steppersettingswidget.cpp \
    DCMotor/dcmotorcontrolwidget.cpp \
    StepperMotor/stepperwidgetcontroller.cpp \
    DCMotor/dcmotorwidgetcontroller.cpp \
    DCMotor/dcmotor.cpp \
    StepperMotor/steppermotor.cpp \
    serialport.cpp

HEADERS  += mainwindow.h \
    StepperMotor/steppercontrolwidget.h \
    StepperMotor/steppersettingsdialog.h \
    StepperMotor/steppersettingswidget.h \
    DCMotor/dcmotorcontrolwidget.h \
    StepperMotor/stepperwidgetcontroller.h \
    DCMotor/dcmotorwidgetcontroller.h \
    DCMotor/dcmotor.h \
    StepperMotor/steppermotor.h \
    consts.h \
    serialport.h

FORMS    += mainwindow.ui \
    StepperMotor/steppercontrolwidget.ui \
    StepperMotor/steppersettingsdialog.ui \
    StepperMotor/steppersettingswidget.ui \
    DCMotor/dcmotorcontrolwidget.ui
