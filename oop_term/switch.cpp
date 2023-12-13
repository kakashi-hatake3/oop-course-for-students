
#include "switch.h"
#include <QString>

Switch::Switch(QString nameSwitch)
{
    name = nameSwitch;
}

Switch::Switch()
{

}

bool Switch::getIsOn(){
    return isOn;
}

bool Switch::getIsParallel(){
    return isParallel;
}

void Switch::setIsOn(bool status){
    isOn = status;
}
