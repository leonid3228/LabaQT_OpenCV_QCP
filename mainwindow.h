#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLineEdit>
#include <QPushButton>
#include <QPen>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMainWindow>
#include "qcustomplot.h"
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <QDebug>

struct Standart{
    QString image;
    double huMoments[7];
    int id;
};

class MainWindow :  public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void momentsCreator(Standart &, QPen pen);

private slots:
    void addPredict();
    void traning();

private:
    QVector<Standart> Standart1;
    QVector<Standart> Standart2;
    QPen penOne,pen2,penPredict;
    QPushButton *start;
    QPushButton *load;
    QCustomPlot *plot;
    QLineEdit * imageName;
    QVBoxLayout * topLayout;
    QHBoxLayout * botLayout;
    QMessageBox dialog;
    int graphCount =-1;
};
#endif
