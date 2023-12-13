// interface.h
#ifndef INTERFACE_H
#define INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "buildshema.h"
#include <QCoreApplication>
#include <QMouseEvent>
#include <QDir>


class Interface : public QWidget
{
    Q_OBJECT

public:
    Interface(QWidget *parent = nullptr);
    void updateShemaView();
    BuildShema shema;


private slots:
    void rebuildShema();
    void drawShema();
    void chooseFile();


private:

    QString currentPath = QCoreApplication::applicationDirPath();
    QString filePath = currentPath + QDir::separator() + "shema.txt";

    QPushButton *rebuildButton;
    QPushButton* chooseFileButton;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsEllipseItem* createLamp(int x, int y, int size);
    QGraphicsRectItem* createSwitch(int x, int y, int width, int height);
    QGraphicsLineItem* createLine(int x1, int y1, int x2, int y2);
    QMap<QGraphicsRectItem*, QList<QGraphicsEllipseItem*>> connectedLamps;

    QMap<QGraphicsRectItem*, bool> switchStates;

    QMap<QGraphicsRectItem*, Switch*> switchItems;
    QMap<QString, QGraphicsEllipseItem*> lampItems;


    void turnLamps();
    void updateLampsColor();

    // Для каждой лампочки хранит соответствующий ей ключ
//    QMap<QGraphicsEllipseItem*, QGraphicsRectItem*> lampSwitches;

protected:
    // Добавляем обработчик события нажатия мыши на элементе сцены
    void mousePressEvent(QMouseEvent *event) override;

    // Дополнительные элементы интерфейса могут быть добавлены по необходимости
};

#endif // INTERFACE_H
