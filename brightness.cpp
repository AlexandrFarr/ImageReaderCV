#include "brightness.h"

Brightness::Brightness()
{
    int Oldvalue = 0;
}

cv::Mat Brightness::changeImage(const cv::Mat &img, int value)
{
   // img.convertTo(img,-1,1,value);
    cv::Mat newImage = img;

   newImage.convertTo(newImage,-1,1,value);
   return newImage;
    //imageLabel->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));

/*
    double alpha = 1.0;
    int beta = value;
    int ch = img.channels();

    for( int y = 0; y < img.rows; y++ ) {
           for( int x = 0; x < img.cols; x++ ) {
               for( int c = 0; c < img.channels(); c++ ) {
                   if(Oldvalue>value)
                   {
                   img.at<cv::Vec3b>(y,x)[c] =
                     cv::saturate_cast<uchar>( alpha*img.at<cv::Vec3b>(y,x)[c] + abs(value) );
                   }
                   else
                   {
                       img.at<cv::Vec3b>(y,x)[c] =
                         cv::saturate_cast<uchar>( alpha*img.at<cv::Vec3b>(y,x)[c] + value );
                   }
               }
           }
    }
    Oldvalue = value;
   img.convertTo(img, -1, alpha, beta);
  //  int m_nContrastValue = 100; //Contrast value

   // double alpha = m_nContrastValue*0.01;
//    int beta = m_nBrightValue;
   // int ch = m_srcMat.channels();


    //ui->label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8)));
    */
    //img.convertTo(img,-1,1,100);
    //img.convertTo(img,-1,1,100);
    //img.convertTo(img,-1,1,-100);
}
