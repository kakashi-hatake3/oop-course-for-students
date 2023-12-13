
#include "lamp.h"
#include <QString>

Lamp::Lamp(QString nameLamp)
{
    name = nameLamp;
}

Lamp::Lamp()
{

}

bool Lamp::getIsOn(){
    return isOn;
}

void Lamp::setIsOn(bool status){
    isOn = status;
}
