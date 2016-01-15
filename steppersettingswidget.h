#ifndef STEPPERSETTINGSWIDGET_H
#define STEPPERSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class StepperSettingsWidget;
}

class StepperSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StepperSettingsWidget(QWidget *parent = 0);
    ~StepperSettingsWidget();

private:
    Ui::StepperSettingsWidget *ui;

};

#endif // STEPPERSETTINGSWIDGET_H
