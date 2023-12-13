
#ifndef SWITCH_H
#define SWITCH_H
#include <QString>




class Switch
{
public:
    Switch(QString);
    Switch();
    bool isOn = false;
    bool isParallel = false;
    QString name;
    bool getIsOn();
    bool getIsParallel();
    void setIsOn(bool);
};

#endif // SWITCH_H
