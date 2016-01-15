#ifndef STEPPERSETTINGSDIALOG_H
#define STEPPERSETTINGSDIALOG_H

#include <QDialog>
#include "steppersettingswidget.h"

namespace Ui {
class StepperSettingsDialog;
}

class StepperSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StepperSettingsDialog(QWidget *parent = 0);
    ~StepperSettingsDialog();

private:
    Ui::StepperSettingsDialog *ui;
    StepperSettingsWidget *stepper1;
};

#endif // STEPPERSETTINGSDIALOG_H
