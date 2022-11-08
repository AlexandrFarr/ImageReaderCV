#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QObject>
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

class Brightness
{
    //Q_OBJECT
public:
    Brightness();

    cv::Mat changeImage(const cv::Mat &img,int value);


private:
    int oldValueBrightness;
};

#endif // BRIGHTNESS_H
