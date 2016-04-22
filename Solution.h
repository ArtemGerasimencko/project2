#ifndef SOLUTION_H
#define SOLUTION_H
#include<QVector>
//#include"Place.h"
//#include"Road.h"
#include"Map.h"
class Solution
{
    double **d_massKm,**d_massHours;
    int pok;
    int n;
    QVector<int> RoadAnswerKm;
    QVector<int> RoadAnswerHours;
    int answerLength;
    QVector<Place*>SListOfPlace;
    QVector<Road*>SListOfRoad;
public:
    double answerHours;
    Solution(QVector<Place*> ListOfPlace,QVector<Road*> ListOfRoad,QString start,QString end,int pok);
    void Dejkstra(int StartPlace,int EndPlace,double **mass);
    QVector<Road*> getSListOfRoad();
    int getPok();
    void getRoute(QVector<int> PlaceAnswer);
    ~Solution();
};

#endif // SOLUTION_H
