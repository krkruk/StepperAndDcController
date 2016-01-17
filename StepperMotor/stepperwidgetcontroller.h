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
    void reset();
    bool startInternalEnumerationAt(unsigned int startAt);
    unsigned int getStartInternalEnumerationAt() const;
    QList<StepperMotor> getStepperMotorsStates() const;

    std::shared_ptr<StepperSettingsDialog> createSettingsDialog();
    int getLastElemUpdatedIndex() const;
    QJsonObject getLastJson();

signals:
    void stepperUpdate(int index);
    void stepperJsonUpdate(const QJsonObject &json);

public slots:
    void stepperUpdateFeedback(const QString &json);

private slots:
    void onStepperUpdated(int stepperValue);

private:
    unsigned int startAtValue {0};
    QTabWidget *tabWidget;
    QList<std::shared_ptr<StepperControlWidget>> tabObjects;
    QList<StepperMotor> stepperMotorsStates;
    int lastElemUpdatedIndex{0};
};

#endif // STEPPERWIDGETCONTROLLER_H
