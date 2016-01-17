#ifndef DCMOTORWIDGETCONTROLLER_H
#define DCMOTORWIDGETCONTROLLER_H

#include <memory>
#include <QList>
#include <QObject>
#include <QTabWidget>
#include "dcmotorcontrolwidget.h"
#include "dcmotor.h"


class DCMotorWidgetController : public QObject
{
    Q_OBJECT
public:
    explicit DCMotorWidgetController(QTabWidget *tabWidget, QObject *parent = 0);
    ~DCMotorWidgetController();

    void addTab(const QString &label);
    void setSlidersEnabled(bool enable);
    void reset();
    bool startInternalEnumerationAt(unsigned int startAt);
    unsigned int getStartInternalEnumerationAt() const;
    QList<DCMotor> getDcMotorsStates() const;

    int getLastElemUpdatedIndex() const;
    QJsonObject getLastJson();
signals:
    void dcMotorUpdate(int index);
    void dcMotorJsonUpdate(const QJsonObject &json);

public slots:
    void dcMotorUpdateFeedback(const QString &json);

private slots:
    void onDcMotorUpdated(int dcValue);

private:
    unsigned int startAtValue {0};
    QTabWidget *tabWidget;
    QList<std::shared_ptr<DCMotorControlWidget>> tabObjects;
    QList<DCMotor> dcMotorsStates;
    int lastElemUpdatedIndex{0};
};

#endif // DCMOTORWIDGETCONTROLLER_H
