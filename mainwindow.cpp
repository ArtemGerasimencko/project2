#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include<QGraphicsView>
#include<QWidget>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QGridLayout>
#include<QMouseEvent>
#include<QPainter>
#include<QPoint>
#include<QMessageBox>
#include<qjson/parser.h>
#include<QVariant>
#include<QString>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonAddPlace->setEnabled(false);
    ui->pushButtonDeletePlace->setEnabled(false);
    ui->pushButtonAddRoad->setEnabled(false);
    if(!ui->lineEditPlace->text().isEmpty() &&
            (ui->radioButtonCity->isChecked() ))
            //|| ui->radioButtonCountry->isChecked() || ui->radioButtonTown->isChecked()))
        ui->pushButtonAddPlace->setEnabled(true);
    ui->groupBox_place->setStyleSheet("QGroupBox { border: 1px solid gray;"
                                      "border-radius: 3px;"
                                      "margin-top: 1ex; }");
    ui->groupBox_road->setStyleSheet("QGroupBox { border: 1px solid gray;"
                                     "border-radius: 3px;"
                                     "margin-top: 1ex; }");
    ui->groupBox_solution->setStyleSheet("QGroupBox { border: 1px solid gray;"
                                         "border-radius: 3px;"
                                         "margin-top: 1ex; }");
    //ui->groupBoxMapName->setStyleSheet("QGroupBox { border: 1px solid gray;"
    //                                     "border-radius: 3px;"
    //                                     "margin-top: 1ex; }");
    pok_place=0;
    map=new Map;
    map->setSceneRect(0,0,500,500);
    view=new QGraphicsView(map);
    //view->setFixedSize(800,800);
    //map->setSceneRect(0,0,800,800);
    view->show();
    QWidget *widget=new QWidget;
    QHBoxLayout *HBoxLayout=new QHBoxLayout;
    QVBoxLayout *VBoxLayout=new QVBoxLayout;

    VBoxLayout->addWidget(ui->groupBoxMapName,1);
    VBoxLayout->addWidget(ui->groupBox_place,6);
    VBoxLayout->addWidget(ui->groupBox_road,8);
    VBoxLayout->addWidget(ui->groupBox_solution,6);
    //VBoxLayout->setGeometry(setSizePolicy(););

    HBoxLayout->addLayout(VBoxLayout,1);
    HBoxLayout->addWidget(view,4);

    widget->setLayout(HBoxLayout);
    setCentralWidget(widget);

    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionLoadMap,SIGNAL(triggered()),this,SLOT(load()));
    connect(ui->actionNewMap,SIGNAL(triggered()),this,SLOT(newMap()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *mouse)
{
    if(mouse->button()==Qt::LeftButton)
    {
        if(pok_place==1)
        {
            map->AddNewCity(ui->lineEditPlace->text(),mouse->pos());
            ui->radioButtonCity->setAutoExclusive(false);
            ui->radioButtonCity->setChecked(false);
        }
        if(pok_place==2)
        {
            map->AddNewTown(ui->lineEditPlace->text(),mouse->pos());
            ui->radioButtonTown->setAutoExclusive(false);
            ui->radioButtonTown->setChecked(false);
        }
        if(pok_place==3)
        {
            map->AddNewCountry(ui->lineEditPlace->text(),mouse->pos());
            ui->radioButtonCountry->setAutoExclusive(false);
            ui->radioButtonCountry->setChecked(false);
        }
       pok_place=0;
       ui->lineEditPlace->clear();
    }
}


void MainWindow::on_lineEditPlace_textChanged(const QString &arg1)
{
    ui->pushButtonAddPlace->setEnabled(!arg1.isEmpty());
    ui->pushButtonDeletePlace->setEnabled(!arg1.isEmpty());
}

void MainWindow::on_pushButtonAddPlace_clicked()
{
    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditPlace->text())
        {
            QMessageBox *message=new QMessageBox;
            message->setText("Населений пункт з такою назвою вже існує.");
            message->show();
            return;
        }
    }
    if(ui->radioButtonCity->isChecked()) pok_place=1;
    if(ui->radioButtonTown->isChecked()) pok_place=2;
    if(ui->radioButtonCountry->isChecked()) pok_place=3;
}

void MainWindow::on_pushButtonAddRoad_clicked()
{
    if(ui->lineEditEndRoad->text()==ui->lineEditStartRoad->text()){
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть різні назви міст");
        message->show();
        return;
    }
    int pok=0;
    for(int i=0;i<map->getListOfRoad().size();i++)
    {
        if(((map->getListOfRoad()[i]->getStart()->GetName()==ui->lineEditEndRoad->text()) &&
        (map->getListOfRoad()[i]->getEnd()->GetName()==ui->lineEditStartRoad->text())) ||
            ((map->getListOfRoad()[i]->getEnd()->GetName()==ui->lineEditEndRoad->text()) &&
            (map->getListOfRoad()[i]->getStart()->GetName()==ui->lineEditStartRoad->text())))
        {
            QMessageBox *message=new QMessageBox;
            message->setText("Між цими містами вже є дорога.");
            message->show();
            return;
        }
    }


    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditEndRoad->text()) pok++;
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditStartRoad->text()) pok++;
    }
    if(pok<2)
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть коректні назви міст.");
        message->show();
        return;
    }
    if(ui->radioButtonHightSpeedRoad->isChecked())
        map->AddHightSpeedRoad(ui->lineEditStartRoad->text(),ui->lineEditEndRoad->text(),ui->lineEditrRoadLength->text());
    if(ui->radioButtonMediumSpeedRoad->isChecked())
        map->AddMediumSpeedRoad(ui->lineEditStartRoad->text(),ui->lineEditEndRoad->text(),ui->lineEditrRoadLength->text());
    if(ui->radioButtonLowSpeedRoad->isChecked())
        map->AddLowSpeedRoad(ui->lineEditStartRoad->text(),ui->lineEditEndRoad->text(),ui->lineEditrRoadLength->text());
}


void MainWindow::on_pushButtonDeletePlace_clicked()
{
    int pok=0;
    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditPlace->text()) pok=1;
    }
    if(!pok)
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Населеного пункту з такою назвою не існує.");
        message->show();
        return;
    }
    map->DeletePlace(ui->lineEditPlace->text());
}

void MainWindow::on_pushButtonDeleteRoad_clicked()
{
    int pok=0;
    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditEndRoad->text()) pok++;
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditStartRoad->text()) pok++;
    }
    if(pok<2)
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть коректні назви міст.");
        message->show();
        return;
    }
    map->DeleteRoad(ui->lineEditStartRoad->text(),ui->lineEditEndRoad->text());
}

void MainWindow::on_pushButtonSolution_clicked()
{
    int pok=0;
    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditStart->text()) pok++;
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditEnd->text()) pok++;
    }
    if(pok<2)
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть коректні назви міст.");
        message->show();
        return;
    }
    map->FindSolution(map->getListOfPlace(),map->getListOfRoad(),ui->lineEditStart->text(),ui->lineEditEnd->text(),1);
}


void MainWindow::on_pushButtonSolutionHours_clicked()
{
    int pok=0;
    for(int i=0;i<map->getListOfPlace().size();i++)
    {
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditStart->text()) pok++;
        if(map->getListOfPlace()[i]->GetName()==ui->lineEditEnd->text()) pok++;
    }
    if(pok<2)
    {
        QMessageBox *message=new QMessageBox;
        message->setText("Уведіть коректні назви міст.");
        message->show();
        return;
    }
    map->FindSolution(map->getListOfPlace(),map->getListOfRoad(),ui->lineEditStart->text(),ui->lineEditEnd->text(),0);
}

void MainWindow::on_pushButtonOK_clicked()
{
    for(int i=0;i<map->getListOfRoad().size();i++)
        map->getListOfRoad()[i]->show();
}

void MainWindow::save()
{
    map->save();
}

void MainWindow::load()
{
    QDialog *dialog=new QDialog;
    QLabel *lbl=new QLabel("Уведіть назву");
    lineEditLoadName=new QLineEdit;
    QPushButton *OkButton=new QPushButton("Ok");
    QHBoxLayout *HLayout=new QHBoxLayout;
    QVBoxLayout *VLayout=new QVBoxLayout;
    HLayout->addWidget(lbl);
    HLayout->addWidget(lineEditLoadName);
    VLayout->addLayout(HLayout);
    VLayout->addWidget(OkButton);
    dialog->setLayout(VLayout);
    dialog->show();
    connect(OkButton,SIGNAL(clicked()),this,SLOT(startLoading()));
    connect(OkButton,SIGNAL(clicked()),dialog,SLOT(close()));
}

void MainWindow::newMap()
{
    map->newMap();
}

void MainWindow::startLoading()
{
    map->load(lineEditLoadName->text());
}

void MainWindow::on_lineEditMapName_textChanged(const QString &arg1)
{
    map->setName(arg1);
}

void MainWindow::on_lineEditrRoadLength_textChanged(const QString &arg1)
{
    ui->pushButtonAddRoad->setEnabled(!arg1.isEmpty());
}
