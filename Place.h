#ifndef PLACE_H
#define PLACE_H
#include<QString>
#include<QGraphicsRectItem>
#include<QMouseEvent>
#include<QDebug>
#include<QGraphicsPixmapItem>
#include<QWidget>
#include<QObject>
#include<QGraphicsScene>
class Place:public QGraphicsPixmapItem
{
protected:
    QString name;
    int type;
public:
    Place(QString str=0);
    void SetName(QString str);
    void setType(int t);
    int getType();
    QString GetName();
    virtual void DrowOnMap(){};
};

class City:public Place,public QWidget
{
signals:
    void signalUpdateRoads();
public:
    City(QString str,QPoint point);
    void DrowOnMap(QPoint point);
};

class Town:public Place
{
public:
    Town(QString str,QPoint point );
    void DrowOnMap(QPoint point);
};

class Country:public Place
{
public:
    Country(QString str,QPoint point );
    void DrowOnMap(QPoint point);
};

#endif // PLACE_H
