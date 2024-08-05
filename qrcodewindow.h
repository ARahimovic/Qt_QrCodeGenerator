#ifndef QRCODEWINDOW_H
#define QRCODEWINDOW_H

#include <QMainWindow>

class QrCodeWindow : public QMainWindow
{
    Q_OBJECT

public:
    QrCodeWindow(QWidget *parent = nullptr);
    ~QrCodeWindow();
};
#endif // QRCODEWINDOW_H
