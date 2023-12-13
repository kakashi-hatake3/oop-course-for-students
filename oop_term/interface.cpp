#include "interface.h"
#include "buildshema.h"
#include "switch.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QMessageBox>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QDebug>
#include <QCoreApplication>
#include <QMouseEvent>
#include <QDir>
#include <QFileDialog>



Interface::Interface(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(800, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    rebuildButton = new QPushButton("Перестроить", this);
    chooseFileButton = new QPushButton("Найти файл", this);


    // Подключение слота к кнопке
    connect(rebuildButton, &QPushButton::clicked, this, &Interface::rebuildShema);
    connect(chooseFileButton, &QPushButton::clicked, this, &Interface::chooseFile);  // Подключение слота к новой кнопке


    // Добавление элементов в интерфейс
    layout->addWidget(rebuildButton);
    layout->addWidget(chooseFileButton);  // Добавление новой кнопки в интерфейс

    layout->addWidget(view);

    view->setFixedSize(750, 400);
    layout->addWidget(rebuildButton, 0, Qt::AlignBottom);
    layout->addWidget(chooseFileButton, 0, Qt::AlignBottom);


    switchStates.clear();
    connectedLamps.clear();


    // Дополнительная настройка интерфейса может быть добавлена по необходимости
}

void Interface::chooseFile()
{
    // Открыть диалог выбора файла
    QString filePathC = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Текстовые файлы (*.txt);;Все файлы (*)");

    // Если пользователь выбрал файл, обработать его
    if (!filePathC.isEmpty()) {
        filePath = filePathC;
        rebuildShema();
    }
}


void Interface::updateShemaView()
{

    if (scene)
    {
        // Очистка сцены перед обновлением
        scene->clear();

        // Рисование схемы
        drawShema();
    }
    else
    {
        qDebug() << "Error: Scene is not initialized!";
    }
    // Рисование схемы
}

void Interface::rebuildShema()
{
    qDebug() << filePath;
    if (shema.loadFromFile(filePath))
    {

        // Если успешно, пытаемся разобрать и валидировать схему

        shema.parseShema();

        if (shema.validateShema())
        {
            // Если схема валидна, обновляем отображение
            qDebug() << "Schema loaded and validated successfully.";
            updateShemaView();

            // Можно добавить дополнительные действия по обработке структуры схемы
            // Например, создать объекты для отрисовки графического представления схемы
        }
        else
        {
            // Если схема не валидна, выводим сообщение об ошибке
            QMessageBox::critical(this, "Ошибка", "Некорректная схема!");
        }
    }
    else
    {
        // Если загрузка из файла не удалась, выводим сообщение об ошибке
        QMessageBox::critical(this, "Ошибка", "Не удалось загрузить файл схемы!");
    }

}

void Interface::drawShema()
{
    qDebug() << "Schema draw successfully.";

    int x = 0;
    int y = 200;
    bool isParallel = false;
    int index = -1;
    int delta = 0;
    int parallelY = y;
    int parallelX = x;
    int startParallelX = parallelX;
    int endParallelX = 0;
    QList<int> Xs;
    QGraphicsRectItem* switchItem = nullptr;  // Инициализируем указатель вне условия
    Switch *currentSwitch = nullptr;
    Lamp *currentLamp = nullptr;
    shema.parseLamps();



    for (int i = 0; i < shema.parsedString.length(); i++)
    {
        QString symbol;
        symbol = shema.parsedString[i];
        if(symbol.length() >= 2)
        {
            if(isParallel)
            {
                QGraphicsLineItem* line = createLine(startParallelX - 20, parallelY + 15, endParallelX, parallelY + 15);
                scene->addItem(line);

                for (int j = 0; j < symbol.length(); j+=2)
                {

                    QString tmp = "";
                    tmp += symbol[j];
                    tmp += symbol[j + 1];

                    if(symbol[j] == 'K')
                    {

                        switchItem = createSwitch(parallelX, parallelY, 30, 40);
                        scene->addItem(switchItem);
                        parallelX += 60;
                        currentSwitch = new Switch(tmp);
                        switchItems[switchItem] = currentSwitch;
                    }
                    else
                    {
                        QGraphicsEllipseItem* lamp = createLamp(parallelX, parallelY, 30);
                        scene->addItem(lamp);
                        parallelX += 60;
                        lampItems[tmp] = lamp;
                    }
                }
                Xs.append(parallelX);
                parallelX = startParallelX;
                parallelY += delta;
            }
            else
            {
                for (int j = 0; j < symbol.length(); j+=2)
                {
                    QGraphicsLineItem* line = createLine(x - 20, y + 15, x + 40, y + 15);
                    scene->addItem(line);

                    QString tmp = "";
                    tmp += symbol[j];
                    tmp += symbol[j + 1];

                    if(symbol[j] == 'K')
                    {
                        switchItem = createSwitch(x, y, 30, 40);
                        scene->addItem(switchItem);
                        x += 60;
                        currentSwitch = new Switch(tmp);
                        switchItems[switchItem] = currentSwitch;
                    }
                    else
                    {
                        QGraphicsEllipseItem* lamp = createLamp(x, y, 30);
                        scene->addItem(lamp);
                        x += 60;
                        lampItems[tmp] = lamp;
                    }
                }
            }
        }
        else if (symbol.length() == 1)
        {
            if (symbol == "(")
            {
                index++;
                isParallel = true;
                delta = 300 / shema.counts[index];
                parallelY = y - delta * (int(shema.counts[index] / 2));
                if (shema.counts[index] % 2 == 0)
                {
                    parallelY += delta / 2;
                }
                parallelX = x;
                startParallelX = parallelX;
                endParallelX = startParallelX + 60 * shema.lens[index] - 20;
                QGraphicsLineItem* line = createLine(startParallelX - 20, parallelY + 15, startParallelX - 20, parallelY + 15 + delta * (shema.counts[index] - 1));
                scene->addItem(line);
            }
            else if (symbol == ")")
            {
                isParallel = false;
                QGraphicsLineItem* line = createLine(endParallelX, parallelY - delta + 15, endParallelX, parallelY - delta * shema.counts[index] + 15);
                scene->addItem(line);
                x = *std::max_element(Xs.begin(), Xs.end());
                parallelY = y;
            }
        }
    }
}

QGraphicsEllipseItem* Interface::createLamp(int x, int y, int size)
{
    QGraphicsEllipseItem* lamp = new QGraphicsEllipseItem(x, y, size, size);
    lamp->setBrush(QBrush(Qt::gray));
    return lamp;
}

QGraphicsRectItem* Interface::createSwitch(int x, int y, int width, int height)
{
    QGraphicsRectItem* switchItem = new QGraphicsRectItem(x, y, width, height);
    switchItem->setBrush(QBrush(Qt::red));
    return switchItem;
}

QGraphicsLineItem* Interface::createLine(int x1, int y1, int x2, int y2)
{
    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
    line->setPen(QPen(Qt::black, 2));
    return line;
}

void Interface::mousePressEvent(QMouseEvent *event)
{
    // Преобразуем координаты события мыши в координаты сцены
    QPointF scenePos = view->mapToScene(event->pos());
    scenePos.setX(scenePos.x() - 13);
    scenePos.setY(scenePos.y() - 13);

    // Получаем объект, на который было произведено нажатие мыши
    QGraphicsItem *item = scene->itemAt(scenePos, view->transform());

    if (item && item->type() == QGraphicsRectItem::Type)
    {
        QGraphicsRectItem *switchItem = qgraphicsitem_cast<QGraphicsRectItem *>(item);
        if (switchItem)
        {
            Switch *currentSwitch = switchItems.value(switchItem);  // Получаем объект Switch по ключу
            if (currentSwitch)
            {
                // Меняем цвет и устанавливаем параметр isOn в true
                bool isClicked = currentSwitch->getIsOn();  // Получаем текущее состояние isOn
                switchItem->setBrush(isClicked ? QBrush(Qt::red) : QBrush(Qt::green));

                currentSwitch->setIsOn(!isClicked);
                shema.allSwitchesByName[currentSwitch->name].setIsOn(currentSwitch->getIsOn());
                for(int i = 0; i < shema.meetedLamps.length(); i++){
                    for(int j = 0; j < shema.lampsSwitchesString[shema.meetedLamps[i].name].length(); j++){
                        shema.lampsSwitchesString[shema.meetedLamps[i].name][j].setIsOn(shema.allSwitchesByName[shema.lampsSwitchesString[shema.meetedLamps[i].name][j].name].getIsOn());
                    }
                }
                for(int i = 0; i < shema.allParallelSwitches.length(); i++){
                    for (int j = 0; j < shema.allParallelSwitches[i].length(); j++){
                        for (int k = 0; k < shema.allParallelSwitches[i][j].length(); k++){
                            shema.allParallelSwitches[i][j][k].setIsOn(shema.allSwitchesByName[shema.allParallelSwitches[i][j][k].name].getIsOn());
                        }
                    }
                }

            }

        }
    }

    turnLamps();

    QWidget::mousePressEvent(event);
}

void Interface::turnLamps(){

    int countPosled = shema.posledSwitches.length();
    QList<bool> parallelIsOnList;

    for(int i = 0; i < shema.countOfParallels; i++){
        bool inner = false;
        parallelIsOnList.append(inner);
    }

    bool parallelIsOn = false;
    int countParallel = 0;

    for(int i = 0; i < shema.allParallelSwitches.length(); i++){
        if(shema.allParallelSwitches[i].length() != shema.counts[i]){
            parallelIsOnList[i] = true;
            continue;
        }

        for(int j = 0; j < shema.allParallelSwitches[i].length(); j++){
            int counter = 0;

            for(int k = 0; k < shema.allParallelSwitches[i][j].length(); k++){

                if(shema.allParallelSwitches[i][j][k].getIsOn()){
                    counter++;
                }
            }

            if (counter == shema.allParallelSwitches[i][j].length()){

                parallelIsOnList[i] = true;

                break;
            }

        }
    }

    for(int i = 0; i < parallelIsOnList.length(); i++){
        if(parallelIsOnList[i]){
            countParallel++;
        }
    }
    if(countParallel == parallelIsOnList.length()){
        parallelIsOn = true;
    }
    for (int i = 0; i < shema.meetedLamps.length(); i++){
        int counter = 0;
        for(int j = 0; j < shema.lampsSwitchesString[shema.meetedLamps[i].name].length(); j++){
            if(shema.lampsSwitchesString[shema.meetedLamps[i].name][j].getIsOn()){
                counter++;
            }
        }
        if((counter == shema.lampsSwitchesString[shema.meetedLamps[i].name].length()) && parallelIsOn){
            shema.meetedLamps[i].setIsOn(true);
        }
        else{
            shema.meetedLamps[i].setIsOn(false);
        }
    }

    updateLampsColor();

}

void Interface::updateLampsColor()
{
    for(int i = 0; i < shema.meetedLamps.length(); i++){
        if(shema.meetedLamps[i].getIsOn()){
            lampItems[shema.meetedLamps[i].name]->setBrush(QBrush(Qt::yellow));
        }
        else{
            lampItems[shema.meetedLamps[i].name]->setBrush(QBrush(Qt::gray));
        }
    }
}
