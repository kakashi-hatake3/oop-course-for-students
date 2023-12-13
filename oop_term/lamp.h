
#ifndef LAMP_H
#define LAMP_H
#include <QString>




class Lamp
{
public:
    Lamp(QString);
    Lamp();
    bool isOn = 0;
    QString name;
    bool isParallel = 0;
    bool getIsOn();
    void setIsOn(bool);
};


inline bool operator<(const Lamp &lmp1, const Lamp &lmp2){
    if(lmp1.name < lmp2.name){
        return lmp1.name < lmp2.name;
    }
    return lmp2.name < lmp1.name;
}

inline bool operator==(const Lamp &lmp1, const Lamp &lmp2){
    return lmp1.name == lmp2.name;
}

#endif // LAMP_H
