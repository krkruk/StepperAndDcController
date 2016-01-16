#ifndef STEPPERSETTINGSDIALOG_H
#define STEPPERSETTINGSDIALOG_H

#include <QDialog>
#include <QList>
#include <memory>
#include "steppersettingswidget.h"
class StepperMotor;

namespace Ui {
class StepperSettingsDialog;
}

class StepperSettingsDialog : public QDialog
{
    Q_OBJECT

    void setWidgetData(int index, StepperSettingsWidget *widget);
public:
    explicit StepperSettingsDialog(QList<StepperMotor> *stepperMotorsStates, QWidget *parent = 0);
    ~StepperSettingsDialog();

    void addTab(const QString &label);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::StepperSettingsDialog *ui;
    QList<std::shared_ptr<StepperSettingsWidget>> settingsWidgets;
    QList<StepperMotor> *stepperMotorsStates;
};

#endif // STEPPERSETTINGSDIALOG_H
