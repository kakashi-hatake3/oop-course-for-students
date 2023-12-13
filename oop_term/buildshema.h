#ifndef BUILDSHEMA_H
#define BUILDSHEMA_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QMap>
#include "lamp.h"
#include "switch.h"


class BuildShema
{
public:
    BuildShema();
    bool loadFromFile(const QString &fileName);
    bool saveToFile(const QString &fileName);
    void parseShema();
    void parseLamps();
    bool validateShema();
    QStringList parsedString;
    QList<int> counts;
    QList<int> lens;
    int countOfParallels = 0;

    QMap<QString, QList<Switch>> lampsSwitchesString;


    QList<Switch> parallelSwitches;
    QList<QList<QList<Switch>>> allParallelSwitches;
    QList<Switch> posledSwitches;
    QList<Lamp> meetedLamps;

    QMap<QString, Switch> allSwitchesByName;
    QMap<QString, Lamp> allLampsByName;


private:
    QString shemaString;
};

#endif // BUILDSHEMA_H
