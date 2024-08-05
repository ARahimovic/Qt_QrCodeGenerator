#include "qrcodewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QrCodeWindow w;
    w.show();
    return a.exec();
}
