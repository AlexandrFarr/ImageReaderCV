#include "imagereader.h"
#include "ui_imagereader.h"

ImageReader::ImageReader(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ImageReader)
{
    imageLabel = new QLabel;
    ui->setupUi(this);
    ui->scrollArea->setBackgroundRole(QPalette::Dark);
    ui->scrollArea->setWidget(imageLabel);

     connect(ui->horizontalSlider, &QSlider::valueChanged, this, &ImageReader::changeBrightnes);
     connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, &ImageReader::changeContrast);
     connect(ui->horizontalSlider_4, &QSlider::valueChanged, this, &ImageReader::changeGamma);
}

ImageReader::~ImageReader()
{
    delete ui;
}

void ImageReader::showImage(cv::Mat &img)
{
    const int channels = img.channels();
    if(channels == 1) //GREY
    {
        imageLabel->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8)));
    }else    //RGB
        imageLabel->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));

}

void ImageReader::loadImage()
{
    QString filePath = QFileDialog::getOpenFileName
    (
         this,
         "Open image",
         "c/",
         tr("Image Files (*.png *.jpg *.bmp)")
     );

    if(filePath != ""){
    this->setImg(filePath);

    }
}

// open image and BRG -> RGB for output on display
void ImageReader::setImg(QString filePath)
{
    this->img = cv::imread(filePath.toStdString(),cv::IMREAD_COLOR);

    if(this->img.empty()){
        qDebug()<<"Error open image.....";
    }
    else
    {
        cvtColor(this->img, this->img, cv::COLOR_BGR2RGB);
        this->showImage(this->img);
    }
}


void ImageReader::changeImage(cv::Mat &img, int newBrightness, int newContrast, int newGamma)
{
    brightness = newBrightness;
    contrast = newContrast;
    cv::Mat imt_temp;

    if( newGamma != gamma)
    {
        double gam = newGamma/4.0;
        gamma = gam;

        unsigned char lut[256];
          for (int i = 0; i < 256; i++)
          {
            lut[i] = cv::saturate_cast<uchar>(pow((float)(i / 255.0), 1.0/gam) * 255.0f);
          }

           img.convertTo(imt_temp, -1, contrast,brightness);
          const int channels = img.channels();

          switch (channels)
            {
              case 1:
              {
                cv::MatIterator_<uchar> it, end;
                for (it = imt_temp.begin<uchar>(), end = imt_temp.end<uchar>(); it != end; it++)
                *it = lut[(*it)];
                break;
              }
          case 3:
             {
               cv::MatIterator_<cv::Vec3b> it, end;
               for (it = imt_temp.begin<cv::Vec3b>(), end = imt_temp.end<cv::Vec3b>(); it != end; it++)
               {
                 (*it)[0] = lut[((*it)[0])];
                 (*it)[1] = lut[((*it)[1])];
                 (*it)[2] = lut[((*it)[2])];
               }
               break;
             }
          }
          this->showImage(imt_temp);
    }else
    {
        img.convertTo(imt_temp, -1, contrast,brightness);
        this->showImage(imt_temp);
    }

}

void ImageReader::on_actionOpen_triggered()
{
    this->loadImage();
}


void ImageReader::on_pushButton_clicked()
{
    if(!this->img.empty()){
        //RGB->GREY
        const int channels = img.channels();
            if(channels == 3) //GREY
            {
            cv::cvtColor(this->img,this->img, cv::COLOR_RGB2GRAY);
            img.convertTo(this->img, -1, contrast,brightness);
            showImage(img);
            }
        }
}


void ImageReader::on_actionSave_As_triggered()
{
    if (  this->img.empty() )
     {
       QMessageBox::warning(NULL,"empty file","");
     }
     else
     {
     //диалоговое окно
     QString fileNames = QFileDialog::getSaveFileName(this,"");
        if (fileNames.isNull()){
        QMessageBox::warning(NULL,"no","Good");
        }

        QImage imgSave;
        const int channels = this->img.channels();
        if(channels == 3)
        {
             imgSave= QImage((uchar*) this->img.data, this->img.cols, this->img.rows, this->img.step, QImage::Format_RGB888);
        }
        if(channels == 1)
        {
             imgSave= QImage((uchar*) this->img.data, this->img.cols, this->img.rows, this->img.step, QImage::Format_Indexed8);
        }


        imgSave.save(fileNames, "JPG");

    }

}

void ImageReader::changeBrightnes(int value)
{
    changeImage(this->img,value, this->contrast, this->gamma);
}

void ImageReader::changeContrast(int value)
{
    changeImage(this->img, this->brightness, value, this->gamma);
}

void ImageReader::changeGamma(int value)
{
    changeImage(this->img, this->brightness, this->contrast, value);

}



