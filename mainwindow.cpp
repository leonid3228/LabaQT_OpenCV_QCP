#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)

{
    start = new QPushButton("Загрузить данные");
    load = new QPushButton("Проверить изображение");
    plot = new QCustomPlot;
    imageName  = new QLineEdit;
    topLayout = new QVBoxLayout;
    plot->xAxis->setRange(0,6);
    plot->yAxis->setRange(-7,7);
    topLayout->addWidget(plot);
    topLayout->addWidget(start);
    botLayout = new QHBoxLayout;
    botLayout->addWidget(imageName);
    botLayout->addWidget(load);
    topLayout->addLayout(botLayout);
    resize(900,600);
    setLayout(topLayout);

    penOne.setWidth(1);
    penOne.setColor(QColor(Qt::red));

    pen2.setWidth(1);
    pen2.setColor(Qt::blue);

    penPredict.setWidth(4);
    penPredict.setColor(Qt::black);
    dialog.setBaseSize(QSize(150,150));

    plot->legend->setVisible(true);
    plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);
    plot->legend->setBrush(QColor(255, 255, 255, 100));
    plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    plot->legend->setFont(legendFont);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->xAxis->setLabel("Момент");
    plot->yAxis->setLabel("Значение момента");
    connect(start, SIGNAL(clicked()),this,SLOT(traning()));
    connect(load, SIGNAL(clicked()),this,SLOT(addPredict()));
}
void MainWindow::traning()
{
    for(int i =0;i<11;++i){
        Standart temporary;
        temporary.image = QString("resources/for1/1_%1.jpg").arg(i);
        temporary.id = 1;
        momentsCreator(temporary,penOne);
        Standart1.push_back(std::move(temporary));
        if(i>0)
            plot->legend->removeAt(1);
    }
    for(int i =0;i<10;++i){
        Standart temporary;
        temporary.image = QString("resources/for2/2_%1.jpg").arg(i);
        momentsCreator(temporary,pen2);
        temporary.id = 2;
        Standart2.push_back(std::move(temporary));
        if(i>0)
            plot->legend->removeAt(2);
    }
}

void MainWindow::momentsCreator(  Standart& pictureInfo, QPen pen)
{
    plot->addGraph();
    plot->graph()->setName("moments for"+QString::number(pictureInfo.id));
    graphCount++;
    cv::Mat out,im;
    cv::Mat data = cv::imread(pictureInfo.image.toStdString(),1);
    cv::cvtColor(data,im,cv::COLOR_BGR2GRAY);
    cv::Canny(im,out,100,200);
    cv::Moments moments = cv::moments(out, true);
    cv::HuMoments(moments, pictureInfo.huMoments);
    for(int i = 0; i < 7; i++) {
        pictureInfo.huMoments[i] = -1 * copysign(1.0, pictureInfo.huMoments[i]) * log10(cv::abs(pictureInfo.huMoments[i]));
        plot->graph(graphCount)->addData(i,pictureInfo.huMoments[i]);
        plot->graph(graphCount)->setPen(pen);
    }
    plot->replot();
}

void MainWindow::addPredict()
{
    QString str(imageName->text()+".jpg");
    Standart temporary;
    temporary.image = str;
    momentsCreator(temporary,penPredict);

    plot->graph()->setName("moments for "+str);

    QVector<Standart> similar ;

    for(auto it = Standart1.begin();it!=Standart1.end();++it){
        if (((temporary.huMoments[6]*1.4<=it->huMoments[6]) &&(temporary.huMoments[6]*0.6>=it->huMoments[6]))
                || ((temporary.huMoments[5]*1.4<=it->huMoments[5]) &&(temporary.huMoments[5]*0.6>=it->huMoments[5])))
        {
            similar.push_back(*it);
        }
    }

    for(auto it = Standart2.begin();it!=Standart2.end();++it){
        if (((temporary.huMoments[6]*1.4<=it->huMoments[6]) &&(temporary.huMoments[6]*0.6>=it->huMoments[6]))
                || ((temporary.huMoments[5]*1.4<=it->huMoments[5]) &&(temporary.huMoments[5]*0.6>=it->huMoments[5])))
        {
            similar.push_back(*it);
        }
    }

    if(similar.size()==0){
        dialog.setText("ВАША КАРТИНКА НЕ 1 ИЛИ 2");
        dialog.show();
        return;
    }
    if(similar.size()==1){
        QString str{"ВЫ ВВЕЛИ - "};
        str = str +QString::number(similar.at(0).id)+"\tШрифт как у картинки - "+similar.at(0).image;
        dialog.setText(str);
        dialog.show();
        return;
    }

    double temp = 100; Standart total;


    for(auto it = similar.begin();it!=similar.end();++it){
        if ((qFabs(temporary.huMoments[4] - it->huMoments[4]))<temp){
            temp = (qFabs(temporary.huMoments[4] - it->huMoments[4]));
            total.image = it->image;
            total.id = it->id;
        }
    }
    QString str2{"ВАША КАРТИНКА - "};
    str2 = str2 + QString::number(total.id)+"\tШрифт как у - "+total.image;
    dialog.setText(str2);
    dialog.show();
}
