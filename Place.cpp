#include"Place.h"
#include<QMouseEvent>
#include<QDebug>
#include<QMessageBox>
#include<QPoint>
#include<QtGui>
#include<QString>
#include<QGraphicsPixmapItem>
#include<QLabel>
#include<QGraphicsSimpleTextItem>
Place::Place(QString str)
{
    SetName((str));
    DrowOnMap();
}

void Place::SetName(QString str)
{
    name=str;
}

void Place::setType(int t)
{
    type=t;
}

int Place::getType()
{
    return type;
}

QString Place::GetName()
{
    return name;
}


City::City(QString str, QPoint point):Place(str)
{
    setType(1);
    DrowOnMap(point);
}


void City::DrowOnMap(QPoint point)
{


    setPixmap(QPixmap(":/images/City.png"));
    setFlag(QGraphicsItem::ItemIsMovable);
    setPos(point.x()-565,point.y()-150);
}

Town::Town(QString  str,QPoint point):Place(str)
{
    setType(2);
    DrowOnMap(point);
}

void Town::DrowOnMap(QPoint point)
{
    setPixmap(QPixmap(":/images/Town.png"));
    setFlag(QGraphicsItem::ItemIsMovable);
    setPos(point.x()-565,point.y()-150);
}

Country::Country(QString str,QPoint point):Place(str)
{
    setType(3);
    DrowOnMap(point);
}

void Country::DrowOnMap(QPoint point)
{
    setPixmap(QPixmap(":/images/Country.png"));
    setFlag(QGraphicsItem::ItemIsMovable);
    setPos(point.x()-565,point.y()-150);
}
