#include"Road.h"
#include<QPen>
#include<QGraphicsSimpleTextItem>
void Road::SetWidth(int k)
{
    //this->getLength()
    this->update(getStart()->x(),getStart()->y(),getEnd()->x(),getEnd()->y());
}

Place *Road::getStart()
{
    return start;
}

Place *Road::getEnd()
{
    return end;
}

void Road::setSpeed(int s)
{
    speed=s;
}


int Road::getSpeed()
{
    return speed;
}

void Road::setLength(QString l)
{
    length=l;
}

QString Road::getLength()
{
    return length;
}

HightSpeedRoad::HightSpeedRoad(Place *obj1, Place *obj2,QString length,int width)
{
    setSpeed(120);
    SetStart(obj1);
    SetEnd(obj2);
    setLength(length);

    QPen *pen=new QPen;
    pen->setWidth(width);
    pen->setColor(Qt::green);

    this->setPen(*pen);

    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(this);
    this->setLine(obj1->x()+30,obj1->y()+30,obj2->x()+30,obj2->y()+30);
    qDebug()<<"----------------->";

    text->setText(this->getLength()+" km");
    text->setPos(((obj1->x()+obj2->x())/2),((obj1->y()+obj2->y())/2));


}



MediumSpeedRoad::MediumSpeedRoad(Place *start, Place *end, QString length, int width)
{
    setSpeed(90);
    SetStart(start);
    SetEnd(end);
    setLength(length);

    QPen *pen=new QPen;
    pen->setWidth(width);
    pen->setColor(Qt::yellow);
    this->setPen(*pen);

    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(this);
    text->setText(this->getLength()+" km");
    setLine(start->x()+30,start->y()+30,end->x()+30,end->y()+30);
    text->setPos((start->x()+end->x())/2,((start->y()+end->y())/2));
}


LowSpeedRoad::LowSpeedRoad(Place *start, Place *end, QString length, int width)
{
    setSpeed(60);
    SetStart(start);
    SetEnd(end);
    setLength(length);

    QPen *pen=new QPen;
    pen->setWidth(width);
    pen->setColor(Qt::red);
    this->setPen(*pen);

    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(this);
    text->setText(this->getLength()+" km");
    setLine(start->x()+30,start->y()+30,end->x()+30,end->y()+30);
    text->setPos(((start->x()+end->x())/2),((start->y()+end->y())/2));
}
