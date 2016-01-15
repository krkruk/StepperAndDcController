#ifndef CONTROLWIDGETABSTRACT_H
#define CONTROLWIDGETABSTRACT_H

class ControWidgetAbstract
{
public:
    virtual void sliderValueUpdated(double sliderValue) = 0;
    virtual ~ControWidgetAbstract() {}
};

#endif // CONTROLWIDGETABSTRACT_H
