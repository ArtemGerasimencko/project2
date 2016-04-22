//#include<Solution.h>
#include<iostream>
#include<QDialog>
#include<QMessageBox>
#include"Map.h"
#include<QGraphicsScene>
Solution::Solution(QVector<Place *> ListOfPlace, QVector<Road *> ListOfRoad, QString start, QString end, int pok):pok(pok)
{
    SListOfPlace=ListOfPlace;
    SListOfRoad=ListOfRoad;
    answerLength=-1;
    int StartPlace,EndPlace,d_i,d_j;
    n=ListOfPlace.size();
    d_massKm=new double*[n];
    d_massHours=new double*[n];
    for(int i=0;i<n;i++)
    {
        d_massKm[i]=new double[n];
        d_massHours[i]=new double[n];
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            d_massKm[i][j]=9999;
            d_massHours[i][j]=9999;
        }
            d_massKm[i][i]=0;
            d_massHours[i][i]=0;
    }

    for(int j=0;j<ListOfPlace.size();j++)
    {
        if(ListOfPlace[j]->GetName()==start) StartPlace=j;
        if(ListOfPlace[j]->GetName()==end) EndPlace=j;
    }
    for(int i=0;i<ListOfRoad.size();i++)
    {
        for(int j=0;j<ListOfPlace.size();j++)
        {
            if(ListOfRoad[i]->getStart()->GetName()==ListOfPlace[j]->GetName()) d_i=j;
            if(ListOfRoad[i]->getEnd()->GetName()==ListOfPlace[j]->GetName()) d_j=j;

        }
        bool ok;
        int dec = ListOfRoad[i]->getLength().toInt(&ok, 10);
        d_massKm[d_i][d_j]=dec;
        d_massKm[d_j][d_i]=dec;
        d_massHours[d_i][d_j]=float(float(dec)/float(ListOfRoad[i]->getSpeed()));
        d_massHours[d_j][d_i]=float(float(dec)/float(ListOfRoad[i]->getSpeed()));
    }

    Dejkstra(StartPlace,EndPlace,d_massKm);

    Dejkstra(StartPlace,EndPlace,d_massHours);

}

void Solution::Dejkstra(int StartPlace,int EndPlace, double **mass)
{
    int used=0,tempPlace=0;
    int *MLastPoint=new int[n];
    double *MLengths=new double[n];
    bool *MVisit=new bool[n];

    for(int i=0;i<n;i++)
        MLastPoint[i]=StartPlace;
    for(int i=0;i<n;i++)
        MLengths[i]=9999;
    MLengths[StartPlace]=0;
    for(int i=0;i<n;i++)
        MVisit[i]=false;

    while(used<n)
    {

        int i,min=9999;
        for(i=0;i<n;i++)
            if(MLengths[i]<min && MVisit[i]==false)
            {
                min=MLengths[i];
                tempPlace=i;
            }
        used++;
        MVisit[tempPlace]=true;

        for(int i=0;i<n;i++)
            if(MLengths[tempPlace]+mass[tempPlace][i]<MLengths[i])
            {
                MLengths[i]=MLengths[tempPlace]+mass[tempPlace][i];
                MLastPoint[i]=tempPlace;
            }
    }
    if(answerLength==-1)
    {
        answerLength=MLengths[EndPlace];
        int temp=EndPlace;
        while(1)
        {
            RoadAnswerKm.push_back(temp);
            if(temp==StartPlace) break;
            temp=MLastPoint[temp];
        }
    }
    else
    {
        answerHours=MLengths[EndPlace];
        int temp=EndPlace;
        while(1)
        {
            RoadAnswerHours.push_back(temp);
            if(temp==StartPlace) break;
            temp=MLastPoint[temp];
        }
    }
}

QVector<Road *> Solution::getSListOfRoad()
{
    return SListOfRoad;
}
int  Solution::getPok()
{
    return pok;
}

void Solution::getRoute(QVector<int> PlaceAnswer)
{
    QVector<int> answerRoad;
    for(int j=0;j<SListOfRoad.size();j++)
    {
        for(int i=0;i<PlaceAnswer.size()-1;i++)
        {
            if(((SListOfRoad[j]->getStart()->GetName()==SListOfPlace[PlaceAnswer[i]]->GetName())
                && (SListOfRoad[j]->getEnd()->GetName()==SListOfPlace[PlaceAnswer[i+1]]->GetName()))
            || ((SListOfRoad[j]->getStart()->GetName()==SListOfPlace[PlaceAnswer[i+1]]->GetName())
                && (SListOfRoad[j]->getEnd()->GetName()==SListOfPlace[PlaceAnswer[i]]->GetName())))
            {
                answerRoad.push_back(j);
            }
        }
    }
    int k;
    for(int i=0;i<SListOfRoad.size();i++)
    {
        k=0;
        for(int j=0;j<answerRoad.size();j++)
            if(i==answerRoad[j]) k=1;
        if(!k) (getSListOfRoad()[i])->hide();

    }

    for(int i=0;i<answerRoad.size();i++)
        qDebug()<<answerRoad[i];
}


Solution::~Solution()
{

    QMessageBox *box=new QMessageBox;
    QString str;
    if(answerLength==9999)
        str+="Між даними містами немає жодної дороги";
    else{
        if(getPok()==1)
        {
            str+="Мінімальна відстань між '";
            str+=SListOfPlace[RoadAnswerKm[RoadAnswerKm.size()-1]]->GetName();
            str+="' та '";
            str+=SListOfPlace[RoadAnswerKm[0]]->GetName();
            str+="' становить ";
            str+=QString::number(answerLength);
            str+=" km.";
            str+=" Даний шлях включає в себе такі міста: ";
            for(int j=RoadAnswerKm.size()-1;j>=0;j--)
            {
                str+="'";
                str+=SListOfPlace[RoadAnswerKm[j]]->GetName();
                str+="' ";
            }
            getRoute(RoadAnswerKm);
        } else
        {
            str+=" Найменше часу - ";
            str+=QString::number(answerHours,'f',2);
            str+="годин(и) - займе поїздка за наступним маршрутом: ";
            for(int j=RoadAnswerHours.size()-1;j>=0;j--)
            {
                str+="'";
                str+=SListOfPlace[RoadAnswerHours[j]]->GetName();
                str+="' ";
            }
            getRoute(RoadAnswerHours);
        }
    }
    str+=".";
    box->setText(str);
    box->show();

}
