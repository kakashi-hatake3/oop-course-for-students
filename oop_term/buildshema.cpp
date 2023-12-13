#include "buildshema.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "lamp.h"

BuildShema::BuildShema() {}

bool BuildShema::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    shemaString = in.readAll();
    file.close();

    return true;
}

bool BuildShema::saveToFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << shemaString;
    file.close();

    return true;
}

void BuildShema::parseShema()
{
    // Реализация синтаксического разбора
    // Разбиение строки на элементы и сохранение параметров схемы
    parsedString.clear(); // Очищаем предыдущие данные
    counts.clear();
    lens.clear();
    countOfParallels = 0;


    QStringList tokens;
    for (int i = 0; i < shemaString.length(); ++i)
    {
        if (shemaString[i] == '(' || shemaString[i] == ')' || shemaString[i] == ',' || shemaString[i] == '-' || shemaString[i] == '+')
        {
            tokens.append(shemaString[i]);
        }
        else if (shemaString[i].isLetterOrNumber())
        {
            QString elementName;
            while (i < shemaString.length() && shemaString[i].isLetterOrNumber())
            {
                elementName += shemaString[i];
                ++i;
            }
            --i; // Возвращаемся на один шаг назад, чтобы не пропустить следующий символ
            tokens.append(elementName);
        }
    }
    int index = -1;
    bool fl = false;
    int maxLen = tokens[0].length();
    for (int i = 0; i < tokens.length(); i++){

        if(tokens[i] == "("){
            index++;
            countOfParallels++;
            counts.append(0);
            fl = true;
        }
        else if(tokens[i] == ")"){
            fl = false;
            lens.append(maxLen / 2);
        }
        if (fl){
            if(tokens[i].length() > 1){
                counts[index] += 1;
                if (tokens[i].length() > maxLen){
                    maxLen = tokens[i].length();
                }
            }
        }
    }
    parsedString = tokens;
}

void BuildShema::parseLamps()
{
    lampsSwitchesString.clear();
    parallelSwitches.clear();
    allParallelSwitches.clear();
    posledSwitches.clear();
    meetedLamps.clear();
    allLampsByName.clear();
    allSwitchesByName.clear();

    for(int i = 0; i < countOfParallels; i++){
        QList<QList<Switch>> innerList;
        allParallelSwitches.append(innerList);
    }
    bool isPar = false;
    int index = -1;


    for (int i = 0; i < parsedString.length(); ++i)
    {
        QString symbol = parsedString[i];
        if(symbol.length() >= 2)
        {
            if(isPar)
            {
                parallelSwitches.clear();
                int countKeys = 0;

                for (int j = 0; j < symbol.length(); j+=2)
                {
                    QString tmp = "";
                    tmp += symbol[j];
                    tmp += symbol[j + 1];
                    if(symbol[j] == 'K')
                    {
                        countKeys++;
                        Switch sw = tmp;
                        sw.isParallel = true;
                        parallelSwitches.append(sw);
                        allSwitchesByName[tmp] = sw;
                        allSwitchesByName[tmp].isParallel = true;
                    }
                    else
                    {
                        Lamp lmp = tmp;
                        meetedLamps.append(lmp);
                        allLampsByName[tmp] = lmp;

                        if(countKeys != 0){
                            lampsSwitchesString[tmp] = parallelSwitches;

                        }
                        else{
                            lampsSwitchesString[tmp];

                        }
                    }
                }
                if(parallelSwitches.length() != 0){
                    allParallelSwitches[index].append(parallelSwitches);
                }

            }
            else
            {
                for (int j = 0; j < symbol.length(); j+=2)
                {
                    QString tmp = "";
                    tmp += symbol[j];
                    tmp += symbol[j + 1];
                    if(symbol[j] == 'K')
                    {
                        Switch sw = tmp;
                        allSwitchesByName[tmp] = sw;
                        posledSwitches.append(sw);
                    }
                    else
                    {
                        Lamp lmp = tmp;
                        allLampsByName[tmp] = lmp;
                        meetedLamps.append(lmp);
                        lampsSwitchesString[tmp];

                    }
                }
            }
        }
        else if (symbol.length() == 1)
        {
            if (symbol == "(")
            {
                index++;
                isPar = true;
            }
            else if (symbol == ")")
            {
                isPar = false;

            }
        }
    }
    qDebug() << lampsSwitchesString.keys().length();

    for (int i = 0; i < meetedLamps.length(); i++){
        lampsSwitchesString[meetedLamps[i].name] += posledSwitches;
    }


    qDebug() << lampsSwitchesString.keys().length();


    for(int i = 0; i < meetedLamps.length(); i++){
        qDebug() << lampsSwitchesString.keys()[i] << lampsSwitchesString.value(meetedLamps[i].name).length();

        for (int j = 0; j < lampsSwitchesString.value(meetedLamps[i].name).length(); j++){
            qDebug() << lampsSwitchesString.value(meetedLamps[i].name)[j].name << lampsSwitchesString.value(meetedLamps[i].name)[j].getIsParallel();
        }
    }


    for(int i = 0; i < allSwitchesByName.keys().length(); i++){
        qDebug() << allSwitchesByName.keys()[i] << allSwitchesByName.value(allSwitchesByName.keys()[i]).getIsParallel();
    }
}

bool BuildShema::validateShema()
{
    // Реализация проверки корректности схемы
    int openParentheses = shemaString.count('(');
    int closeParentheses = shemaString.count(')');

    if (openParentheses != closeParentheses || (parsedString[0] != '+' || parsedString.last() != '-'))
    {
        qDebug() << "Ошибка в схеме";
        return false;
    }

    QStringList uniqueElements;
    QStringList tmpList;
    QStringList specSymbols = {"+", "-", "(", ")", ","};
    for (const QString& element : parsedString){
        if(element.length() >= 2){
            for(int i = 0; i < element.length(); i+=2){
                QString tmp = "";
                tmp += element[i];
                tmp += element[i + 1];
                uniqueElements.append(tmp);
            }
        }
    }
    qDebug() << uniqueElements;

    for (const QString& element : uniqueElements)
    {
        if(element.length() % 2 == 1 && !specSymbols.contains(element)){
            qDebug() << "els ne chet";
            return false;
        }

        if (tmpList.contains(element))
        {
            qDebug() << "Ошибка: элемент '" << element << "' повторяется в схеме.";
            return false;
        }
        else
        {

            tmpList.append(element);
        }
    }

    int openedParallel = 0;

    for (const QString& element : parsedString)
    {
        if (element == "(")
        {
            openedParallel++;
        }
        else if (element == ")")
        {
            openedParallel--;
        }
        if(openedParallel > 1){
            qDebug() << "Ошибка: вложенные параллельные соединения не допускаются.";
            return false;
        }
        else if(openedParallel < 0){
            qDebug() << "Ошибка: закрывающая скобка до открывающей.";
            return false;
        }
    }
    return true;
}



