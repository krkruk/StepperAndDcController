#ifndef STEPPERSETTINGSWIDGET_H
#define STEPPERSETTINGSWIDGET_H

#include <QWidget>
#include <QDoubleValidator>
#include <QIntValidator>

namespace Ui {
class StepperSettingsWidget;
}

class StepperSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StepperSettingsWidget(QWidget *parent = 0);
    ~StepperSettingsWidget();
    enum MODE { FullStep, HalfStep };

    double getAngleToStep();
    void setAngleToStep(double angleToStep);

    double getGearRatio();
    void setGearRatio(double gear);

    void setStepperMode(short mode);
    short getStepperMode();

    void setTimeIntervalMs(int timeInterval);
    int getTimeIntervalMs();

private:
    Ui::StepperSettingsWidget *ui;
    QDoubleValidator doubleValidator;
    QIntValidator intValidator;
    QLocale localePreferences;
};

#endif // STEPPERSETTINGSWIDGET_H
