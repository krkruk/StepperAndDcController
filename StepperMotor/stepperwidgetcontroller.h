#ifndef STEPPERWIDGETCONTROLLER_H
#define STEPPERWIDGETCONTROLLER_H

#include <memory>
#include <QList>
#include <QObject>
#include <QTabWidget>
#include "steppercontrolwidget.h"
#include "steppersettingsdialog.h"
#include "steppermotor.h"
#include <QDebug>

class StepperWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit StepperWidgetController(QTabWidget *tabWidget, QObject *parent = 0);
    ~StepperWidgetController();

    void addTab(const QString &label);
    void setSlidersEnabled(bool enable);
    bool startInternalEnumerationAt(unsigned int startAt);
    unsigned int getStartInternalEnumerationAt() const;
    QList<StepperMotor> getStepperMotorsStates() const;

    std::shared_ptr<StepperSettingsDialog> createSettingsDialog();

signals:
    void stepperUpdate(int index);

public slots:

private slots:
    void onStepperUpdated(int stepperValue);

private:
    unsigned int startAtValue {0};
    QTabWidget *tabWidget;
    QList<std::shared_ptr<StepperControlWidget>> tabObjects;
    QList<StepperMotor> stepperMotorsStates;
};

#endif // STEPPERWIDGETCONTROLLER_H
