#include "imagereader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageReader w;
    w.setWindowTitle("Image reader");
    w.show();
    return a.exec();
}
