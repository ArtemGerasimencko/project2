#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"Map.h"
#include <QMainWindow>
#include<QMouseEvent>
#include<QDebug>
#include<QPoint>
#include<QGraphicsView>
#include<qjson/parser.h>
#include<QString>
#include<QVariant>
#include<QLineEdit>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Map *map;
    int pok_place;
    QGraphicsView *view;
    QLineEdit *lineEditLoadName;
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     void mousePressEvent(QMouseEvent *mouse);
private slots:
    void on_lineEditPlace_textChanged(const QString &arg1);
    void on_pushButtonAddPlace_clicked();
  /*  void paintEvent(QPaintEvent *)
    {
    QGraphicsView view2;
        /*QPainter p(view);
                p.begin(view);
        p.setPen(QPen(Qt::red,1,Qt::SolidLine));
        p.drawLine(0,0,1000,1000);
        p.end();
    }*/
    void on_pushButtonAddRoad_clicked();
    void on_pushButtonSolution_clicked();
    void on_pushButtonDeletePlace_clicked();
    void on_pushButtonDeleteRoad_clicked();
    void on_pushButtonSolutionHours_clicked();
    void on_pushButtonOK_clicked();
    void save();
    void load();
    void newMap();
    void startLoading();
    void on_lineEditMapName_textChanged(const QString &arg1);
    void on_lineEditrRoadLength_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
