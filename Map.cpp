#include"Map.h"
#include<QLabel>
#include<QGraphicsPixmapItem>
#include<QGraphicsSimpleTextItem>
#include<QWidget>
#include<QGraphicsRectItem>
#include<QHBoxLayout>
#include<QLine>
#include<QGraphicsLineItem>
#include"Road.h"
#include<QDebug>
#include<QFile>
#include<fstream>
#include<iostream>
#include<string>
#include<QMessageBox>
#include<QLineEdit>
#include<QPushButton>
#include<cstdlib>
Map::Map()
{
    setBackgroundBrush(QBrush(QImage(":/images/bg4.png")));
}

void Map::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"+";
    this->UpdateRoads();
    QGraphicsScene::mouseMoveEvent(event);
}

QVector<Place *> Map::getListOfPlace()
{
    return ListOfPlace;
}

QVector<Road *> Map::getListOfRoad()
{
    return ListOfRoad;
}

void Map::clearVectors()
{
    for(int i=0;i<ListOfRoad.size();i++)
        delete ListOfRoad[i];
    ListOfRoad.clear();
    for(int i=0;i<ListOfPlace.size();i++)
        delete ListOfPlace[i];
    ListOfPlace.clear();
}

void Map::setName(QString str)
{
    name=str;
}

QString Map::getName()
{
    return name;
}

void Map::AddNewCity(QString str, QPoint point)
{
    City *city=new City(str,point);
    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(city);
    text->setText(str);
    text->setFlag(QGraphicsItem::ItemIsMovable);
    text->setPos(text->x(),text->y()-20);
    addItem(city);
    ListOfPlace.push_back(city);
}

void Map::AddNewTown(QString str,QPoint point)
{
    Town *town=new Town(str,point);
    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(town);
    text->setText(str);
    text->setFlag(QGraphicsItem::ItemIsMovable);
    text->setPos(text->x(),text->y()-20);
    addItem(town);
    ListOfPlace.push_back(town);
    int id=ListOfPlace.indexOf((Place*)sender());
    qDebug()<<id;
}

void Map::AddNewCountry(QString str,QPoint point)
{
    Country *country=new Country(str,point);
    QGraphicsSimpleTextItem *text=new QGraphicsSimpleTextItem(country);
    text->setText(str);
    text->setFlag(QGraphicsItem::ItemIsMovable);
    text->setPos(text->x(),text->y()-20);
    addItem(country);
    ListOfPlace.push_back(country);
}

void Map::UpdateRoads()
{
    //qDebug()<<"update";
    for(int i=0;i<ListOfRoad.size();i++)
    {
        Road *road;
        if(ListOfRoad[i]->getSpeed()==120)
        {
            road=new HightSpeedRoad(ListOfRoad[i]->getStart(),ListOfRoad[i]->getEnd(),ListOfRoad[i]->getLength(),3);
            road->setSpeed(120);
            road->setLength(ListOfRoad[i]->getLength());
        }
        if(ListOfRoad[i]->getSpeed()==90)
        {
            road=new MediumSpeedRoad(ListOfRoad[i]->getStart(),ListOfRoad[i]->getEnd(),ListOfRoad[i]->getLength(),3);
            road->setSpeed(90);
        }
        if(ListOfRoad[i]->getSpeed()==60)
        {
            road=new LowSpeedRoad(ListOfRoad[i]->getStart(),ListOfRoad[i]->getEnd(),ListOfRoad[i]->getLength(),3);
            road->setSpeed(60);
        }
            removeItem(ListOfRoad[i]);
            delete ListOfRoad[i];
            ListOfRoad[i]=road;
            addItem(road);
    }
}

void Map::drawRoute(QVector<int> answerRoad)
{
    /*for(int i=0;i<answerRoad.size();i++)
    {
        Road *road;
        if(ListOfRoad[answerRoad[i]]->getSpeed()==120)
        {
            road=new HightSpeedRoad(ListOfRoad[answerRoad[i]]->getStart(),ListOfRoad[answerRoad[i]]->getEnd(),
                    ListOfRoad[answerRoad[i]]->getLength(),6);
            road->setSpeed(120);
            road->setLength(ListOfRoad[answerRoad[i]]->getLength());
        }
        if(ListOfRoad[answerRoad[i]]->getSpeed()==90)
        {
            road=new MediumSpeedRoad(ListOfRoad[answerRoad[i]]->getStart(),ListOfRoad[answerRoad[i]]->getEnd(),
                    ListOfRoad[answerRoad[i]]->getLength(),6);
            road->setSpeed(90);
        }
        if(ListOfRoad[answerRoad[i]]->getSpeed()==60)
        {
            road=new LowSpeedRoad(ListOfRoad[answerRoad[i]]->getStart(),ListOfRoad[answerRoad[i]]->getEnd()
                    ,ListOfRoad[answerRoad[i]]->getLength(),6);
            road->setSpeed(60);
        }
            removeItem(ListOfRoad[answerRoad[i]]);
            delete ListOfRoad[answerRoad[i]];
            ListOfRoad[answerRoad[i]]=road;
            addItem(road);
    }*/
}

void Map::FindSolution(QVector<Place *> ListOfPlace, QVector<Road *> ListOfRoad, QString start, QString end,int pok)
{
    Solution *solution=new Solution(ListOfPlace,ListOfRoad,start,end,pok);
    delete solution;
}

Place *Map::FindPlace(QString str1)
{
    for(int i=0;i<ListOfPlace.size();i++)
    {
        if(ListOfPlace[i]->GetName()==str1) return ListOfPlace[i];
    }
}

void Map::newMap()
{
    clearVectors();
}

void Map::DeletePlace(QString name)
{
    for(int i=0;i<ListOfPlace.size();i++)
        if(ListOfPlace[i]->GetName()==name)
        {
            QVector<Place*>::iterator it=ListOfPlace.begin();
            it+=i;
            this->removeItem(ListOfPlace[i]);;
            ListOfPlace.erase(it);
            break;
        }

    for(int i=ListOfRoad.size()-1;i>=0;i--)
        if(ListOfRoad[i]->getStart()->GetName()==name || ListOfRoad[i]->getEnd()->GetName()==name)
        {
            QVector<Road*>::iterator it=ListOfRoad.begin();
            it+=i;
            this->removeItem(ListOfRoad[i]);
            ListOfRoad.erase(it);
        }
}

void Map::DeleteRoad(QString start, QString end)
{
    for(int i=0;i<ListOfRoad.size();i++)
        if((ListOfRoad[i]->getStart()->GetName()==start && ListOfRoad[i]->getEnd()->GetName()==end) ||
            (ListOfRoad[i]->getStart()->GetName()==end && ListOfRoad[i]->getEnd()->GetName()==start))
        {
            QVector<Road*>::iterator it=ListOfRoad.begin();
            it+=i;
            this->removeItem(ListOfRoad[i]);
            ListOfRoad.erase(it);
        }
}

void Map::save()
{
    if(this->getName()=="")
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть назву карти.");
        message->show();
        return;
    }
    qDebug()<<"Save";
    std::ifstream in("Save.txt");
    std::string line;

    while(in)
    {
        char ch[80];
        in.getline(ch,80);
        std::string line(ch);
        qDebug()<<QString::fromStdString(line);
        if(line[0]=='M')
        {
            std::string::iterator it=line.begin();
            for(int i=0;i<4;i++) line.erase(it);
            qDebug()<<"erased--->"<<QString::fromStdString(line);

            if(line==this->getName().toStdString())
            {
                qDebug()<<"isnye";
                QMessageBox *message=new QMessageBox;
                message->setText("Карта з таким іменем вже існує. Уведіть інше ім’я.");
                message->show();
                //in.close();
                return;
            }
        }
}
    std::ofstream out("Save.txt", std::ios_base::app);
    out<<"Map,";
    std::string str;
    str=this->getName().toStdString();
    out<<str;
    out<<"\nPlaces{\n";
    for(int i=0;i<ListOfPlace.size();i++)
    {
        if(ListOfPlace[i]->getType()==1) out<<"city,";
        if(ListOfPlace[i]->getType()==2) out<<"town,";
        if(ListOfPlace[i]->getType()==3) out<<"country,";
        out<<ListOfPlace[i]->GetName().toStdString()<<","<<ListOfPlace[i]->x()<<","<<ListOfPlace[i]->y()<<",\n";
    }
    out<<"}\n";
    out<<"Roads{\n";
    for(int i=0;i<ListOfRoad.size();i++)
    {
        out<<ListOfRoad[i]->getSpeed()<<","<<ListOfRoad[i]->getStart()->GetName().toStdString()<<","
          <<ListOfRoad[i]->getEnd()->GetName().toStdString()<<","<<ListOfRoad[i]->getLength().toStdString()<<",\n";
    }
    out<<"}\n\n";

}

void Map::load(QString str)
{
    qDebug()<<"loading "<< str;
    clearVectors();
    std::ifstream in("Save.txt");
    char ch[80];
    while(in)
    {
        in.getline(ch,80);
        std::string line(ch);
        if(ch[0]=='M')
        {
            std::string::iterator it=line.begin();
            for(int i=0;i<4;i++) line.erase(it);
            qDebug()<<QString::fromStdString(line);
            if(line==str.toStdString())
            {
                qDebug()<<"є така катрта";

                    in.getline(ch,80);
                    in.getline(ch,80);
                    std::string line(ch);
                    int temp;
                    while(ch[0]!='}')
                    {
                        if(ch[0]=='c' && ch[1]=='i')
                        {
                            std::string lineName1;

                            int i=0,j=0;
                            for(i=5;i<80;i++)
                            {
                                if(ch[i]==',') break;
                                lineName1.push_back(ch[i]);
                            }
                            qDebug()<<"NAME="<<QString::fromStdString(lineName1);
                            int temp_x=0;
                            int pok=1;
                            for(j=i+1;j<80;j++)
                            {

                                if(ch[j]==',') break;
                                if(ch[j]=='-') pok=-1;
                                else{
                                    temp_x*=10;
                                    temp_x+=(ch[j]-48);
                                }
                            }
                            temp_x*=pok;
                            qDebug()<<"x="<<temp_x;
                            int temp_y=0;
                            pok=1;
                            int k=0;
                            for(k=j+1;k<80;k++)
                            {
                                if(ch[k]==',') break;
                                if(ch[k]=='-') pok=-1;
                                else{
                                    temp_y*=10;
                                    temp_y+=(ch[k]-48);
                                }
                            }
                            temp_y*=pok;
                            qDebug()<<"y="<<temp_y;
                        QString n=QString::fromStdString(lineName1);
                        QPoint point;
                        point.setX(temp_x+565);
                        point.setY(temp_y+150);
                        AddNewCity(n,point);

                        }

                        if(ch[0]=='t')
                        {
                            std::string lineName2;

                            //lineName.clear();
                            int i=0,j=0;
                            for(i=5;i<80;i++)
                            {
                                if(ch[i]==',') break;
                                lineName2.push_back(ch[i]);
                            }
                            qDebug()<<"NAME="<<QString::fromStdString(lineName2);
                            int temp_x=0;
                            int pok=1;
                            for(j=i+1;j<80;j++)
                            {

                                if(ch[j]==',') break;
                                if(ch[j]=='-') pok=-1;
                                else{
                                    temp_x*=10;
                                    temp_x+=(ch[j]-48);
                                }
                            }
                            temp_x*=pok;
                            qDebug()<<"x="<<temp_x;
                            int temp_y=0;
                            pok=1;
                            int k=0;
                            for(k=j+1;k<80;k++)
                            {
                                if(ch[k]==',') break;
                                if(ch[k]=='-') pok=-1;
                                else{
                                    temp_y*=10;
                                    temp_y+=(ch[k]-48);
                                }
                            }
                            temp_y*=pok;
                            qDebug()<<"y="<<temp_y;
                            QString n=QString::fromStdString(lineName2);
                            QPoint point;
                            point.setX(temp_x+565);
                            point.setY(temp_y+150);
                            AddNewTown(n,point);
                        }

                        if(ch[0]=='c' && ch[1]=='o')
                        {
                            std::string lineName3;

//                            lineName.clear();
                            int i=0,j=0;
                            for(i=8;i<80;i++)
                            {
                                if(ch[i]==',') break;
                                lineName3.push_back(ch[i]);
                            }
                            qDebug()<<"NAME="<<QString::fromStdString(lineName3);
                            int temp_x=0;
                            int pok=1;
                            for(j=i+1;j<80;j++)
                            {

                                if(ch[j]==',') break;
                                if(ch[j]=='-') pok=-1;
                                else{
                                    temp_x*=10;
                                    temp_x+=(ch[j]-48);
                                }
                            }
                            temp_x*=pok;
                            qDebug()<<"x="<<temp_x;
                            int temp_y=0;
                            pok=1;
                            int k=0;
                            for(k=j+1;k<80;k++)
                            {
                                if(ch[k]==',') break;
                                if(ch[k]=='-') pok=-1;
                                else{
                                    temp_y*=10;
                                    temp_y+=(ch[k]-48);
                                }
                            }
                            temp_y*=pok;
                            qDebug()<<"y="<<temp_y;
                            QString n=QString::fromStdString(lineName3);
                            QPoint point;
                            point.setX(temp_x+565);
                            point.setY(temp_y+150);
                            AddNewCountry(n,point);
                        }

                        qDebug()<<QString::fromStdString(line);
                        in.getline(ch,80);
                        line=std::string(ch);
                    }
                    in.getline(ch,80);
                    in.getline(ch,80);
                    line=std::string(ch);
                    qDebug()<<"->>"<<QString::fromStdString(line);
                    while(1)
                    {
                        int speed=0;
                        std::string startName,endName,length;
                        int i=0,k=0,j=0;
                        qDebug()<<"road="<<QString::fromStdString(line);
                        if(line[0]=='1')
                        {
                            speed=120;
                            qDebug()<<120;
                        }else
                        if(ch[0]=='9')
                        {
                            speed=90;
                            qDebug()<<90;
                        }else
                        if(ch[0]=='6')
                        {
                            speed=60;
                            qDebug()<<120;
                        } else break;
                        for(i=0;i<80;i++)
                            if(ch[i]==',') break;
                        for(j=i+1;j<80;j++)
                        {
                            if(ch[j]==',') break;
                            startName.push_back(ch[j]);
                        }
                        for(k=j+1;k<80;k++)
                        {
                            if(ch[k]==',') break;
                            endName.push_back(ch[k]);
                        }
                        for(i=k+1;i<80;i++)
                        {
                            if(ch[i]==',') break;
                            length.push_back(ch[i]);
                        }
                        in.getline(ch,80);
                        line=std::string(ch);
                        //for(int i=0;i<80;i++) ch[i]=' ';
                        QString Sn=QString::fromStdString(startName);
                        QString En=QString::fromStdString(endName);
                        QString l=QString::fromStdString(length);
                        qDebug()<<"speed="<<speed;
                        qDebug()<<"startName="<<Sn;
                        qDebug()<<"endNamw="<<En;
                        qDebug()<<"length="<<l;

                        if(speed==120) AddHightSpeedRoad(Sn,En,l);
                        qDebug()<<"i am here";

                        if(speed==90) AddMediumSpeedRoad(Sn,En,l);
                        if(speed==60) AddLowSpeedRoad(Sn,En,l);

                    }
            return;
            }

        }
    }
    QMessageBox *message=new QMessageBox;
    message->setText("Карта з таким іменем не існує.");
    message->show();
}

void Map::AddHightSpeedRoad(QString str,QString str2,QString length)
{

    HightSpeedRoad *HSRoad=new HightSpeedRoad(FindPlace(str),FindPlace(str2),length,3);

    ListOfRoad.push_back(HSRoad);
    addItem(HSRoad);
}

void Map::AddMediumSpeedRoad(QString str, QString str2,QString length)
{
    MediumSpeedRoad *MSRoad=new MediumSpeedRoad(FindPlace(str),FindPlace(str2),length,3);
    ListOfRoad.push_back(MSRoad);
    addItem(MSRoad);
}

void Map::AddLowSpeedRoad(QString str, QString str2,QString length)
{
    LowSpeedRoad *LSRoad=new LowSpeedRoad(FindPlace(str),FindPlace(str2),length,3);
    ListOfRoad.push_back(LSRoad);
    addItem(LSRoad);
}
