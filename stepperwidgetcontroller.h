#ifndef STEPPERWIDGETCONTROLLER_H
#define STEPPERWIDGETCONTROLLER_H

#include <QObject>
#include "steppercontrolwidget.h"

class StepperWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit StepperWidgetController(QObject *parent = 0);

signals:

public slots:
};

#endif // STEPPERWIDGETCONTROLLER_H
