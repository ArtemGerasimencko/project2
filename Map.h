#ifndef MAP_H
#define MAP_H
#include<QVector>
#include"Place.h"
#include"Road.h"
#include"Solution.h"
#include<QString>
#include<QGraphicsScene>
#include<QWidget>
#include<QGraphicsRectItem>
#include<QMouseEvent>
#include<QDebug>
#include<QLine>
#include<QObject>
#include<QPainter>
#include<qjson/parser.h>
class Map:public QGraphicsScene
{
    QVector<Place*> ListOfPlace;
    QVector<Road*> ListOfRoad;
    QString name;
public:
    Map();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    QVector<Place*> getListOfPlace();
    QVector<Road*> getListOfRoad();

public slots:
    void clearVectors();
    void setName(QString str);
    QString getName();
    void AddNewCity(QString str,QPoint point);
    void AddNewTown(QString str,QPoint point);
    void AddNewCountry(QString str,QPoint point);

    void AddHightSpeedRoad(QString str,QString str2,QString length);
    void AddMediumSpeedRoad(QString str,QString str2,QString length);
    void AddLowSpeedRoad(QString str,QString str2,QString length);

    void UpdateRoads();
    void drawRoute(QVector<int> answerRoad);

    void FindSolution(QVector<Place*> ListOfPlace, QVector<Road*> ListOfRoad, QString start, QString end, int pok);

    Place *FindPlace(QString str1);

    void newMap();
    void DeletePlace(QString name);
    void DeleteRoad(QString start,QString end);

    void save();
    void load(QString str);
};

#endif // MAP_H
