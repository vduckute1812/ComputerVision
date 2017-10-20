#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    s_max=0;
    s_min=0;
    width=0;
    angle=0;
    inTrain = false;
    inTest = false;
    capWebcam.open(0);
    matBinary = Mat::zeros(ui->label->size().width(), ui->label->size().height(), CV_8UC1);
    if(!capWebcam.isOpened()){
        ui->plainTextEdit->appendPlainText("Cap not accessed sucessfully");
        return;
    }
    tmrTimer = new QTimer(this);
    connect(tmrTimer, SIGNAL(timeout()),this, SLOT(processFrameAndUpdateGUI()));
    tmrTimer->start(20);
}


MainWindow::~MainWindow()
{
    delete ui;
    capWebcam.release();
}

void MainWindow::processFrameAndUpdateGUI()
{
    capWebcam.read(matOriginal);
    if(matOriginal.empty()){
        return;
    }

    int rows1 = ui->label->size().width();
    int cols1 = ui->label->size().height();

    cv::resize(matOriginal, matOriginal, Size(rows1, cols1));
    whPoint = getWhPointColorTria(matOriginal);
//    std::string value= floatToString(whPoint.x)+","+floatToString(whPoint.y);
//    QString qstr = QString::fromStdString(value);
//    ui->plainTextEdit->appendPlainText(qstr);

    maskBinary(matOriginal, matBinary, s_min, s_max, angle, width);
    Result = findLinkPixel(matBinary);
    boundingRectImg(matOriginal, Result, dst, rectSegment);
    CalculateListHu();
    cvtColor(matOriginal, matOriginal, CV_BGR2RGB);
    cvtColor(matOriginal, matProcessed, CV_RGB2GRAY);

    QImage qimgOriginal((uchar*)matOriginal.data, matOriginal.cols, matOriginal.rows, matOriginal.step, QImage::Format_RGB888);
    QImage qimgProcessed((uchar*)matProcessed.data, matProcessed.cols, matProcessed.rows, matProcessed.step, QImage::Format_Grayscale8);
    QImage qimgBinary((uchar*)matBinary.data, matBinary.cols, matBinary.rows, matBinary.step, QImage::Format_Indexed8);

    ui->label->setPixmap(QPixmap::fromImage(qimgOriginal));
    ui->label_2->setPixmap(QPixmap::fromImage(qimgProcessed));
    ui->label_3->setPixmap(QPixmap::fromImage(qimgBinary));
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->s_min=(float)value/100;

    ui->label_8->setText(QString::number(s_min));
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    this->s_max=(float)value/100;
    ui->label_9->setText(QString::number(s_max));
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    this->angle=value;
    ui->label_10->setText(QString::number(angle));
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    this->width=value;
    ui->label_11->setText(QString::number(width));
}

void MainWindow::CalculateListHu(){
    HuMomentStruct huValue;
    huVector.clear();
    for(int i=0; i< static_cast<int> (rectSegment.size()); ++i){
        Point x(rectSegment[i].first.y, rectSegment[i].first.x);
        Point y(rectSegment[i].second.y, rectSegment[i].second.x);
        Mat tmp (matBinary, Rect(rectSegment[i].first.y, rectSegment[i].first.x, rectSegment[i].second.y-rectSegment[i].first.y, rectSegment[i].second.x-rectSegment[i].first.x));
        calculateHuMoment(tmp, huValue);
        normalizedLogarit(huValue.Hu);
        ui->plainTextEdit->appendPlainText(QString::number(huValue.Hu[0]));
        huVector.push_back(huValue);                
    }
}

void MainWindow::on_trainButton_clicked()
{
    inTrain = true;

}
