#ifndef ROAD_H
#define ROAD_H
#include<QGraphicsLineItem>
#include<QTime>
#include<QPoint>
#include"Place.h"
#include<QObject>
class Road :public QGraphicsLineItem
{
    Place *start,*end;
    int speed;
    QString length;

public:
    void SetWidth(int k);
    void SetStart(Place *obj){start=obj;};
    void SetEnd(Place *obj){end=obj;};
    Place *getStart();
    Place *getEnd();
    virtual void setSpeed(int s);
    int getSpeed();
    void setLength(QString l);
    QString getLength();
};

class HightSpeedRoad:public Road
{
public:
    HightSpeedRoad(Place *start, Place *end, QString length, int width);
};

class MediumSpeedRoad:public Road
{
public:
    MediumSpeedRoad(Place *start,Place *end,QString length,int width);
};

class LowSpeedRoad:public Road
{
public:
    LowSpeedRoad(Place *start,Place *end,QString length,int width);
};

#endif // ROAD_H
