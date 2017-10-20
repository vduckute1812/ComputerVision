#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <findlinkpixel.h>
#include "segmentation.h"
#include "QMessageBox"
#include "QImage"
#include "QTimer"
#include "humoment.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    VideoCapture capWebcam;
    Mat matOriginal;
    Mat matProcessed;
    Mat matBinary;
    std::vector<Vec3f> vecCircles;
    std::vector<Vec3f>::iterator itrCircles;
    vector<vector<point>> Result, dst;
    vector<HuMomentStruct> huVector;
    vector<pair<point, point>> rectSegment;
    QTimer* tmrTimer;
    Mat rgImg;
    pointValue whPoint;
    float s_max, s_min, width, angle;
    bool inTrain, inTest;
    void CalculateListHu();

public slots:
    void processFrameAndUpdateGUI();

private slots:

    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_horizontalSlider_3_valueChanged(int value);
    void on_horizontalSlider_4_valueChanged(int value);
    void on_trainButton_clicked();
};

#endif // MAINWINDOW_H
