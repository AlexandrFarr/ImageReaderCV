#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include <QMainWindow>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core/core.hpp"

#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QMessageBox>

//using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class ImageReader; }
QT_END_NAMESPACE

class ImageReader : public QMainWindow
{
    Q_OBJECT

public:
    ImageReader(QWidget *parent = nullptr);
    ~ImageReader();


    void showImage(cv::Mat &img);
    void loadImage();
    void setImg(QString filePath);
    void changeImage(cv::Mat &img,int brightness, int contrast,int gamma);

private slots:
    void on_actionOpen_triggered();

    void on_pushButton_clicked();

    void on_actionSave_As_triggered();
    void changeBrightnes(int value);
    void changeContrast(int value);
    void changeGamma(int value);


private:
    Ui::ImageReader *ui;
     QLabel *imageLabel;

     cv::Mat img;
     int brightness = 0;
     int contrast = 1;
     int gamma = 4;
};
#endif // IMAGEREADER_H
