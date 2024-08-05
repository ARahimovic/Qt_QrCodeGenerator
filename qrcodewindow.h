#ifndef QRCODEWINDOW_H
#define QRCODEWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class QrCodeWindow : public QMainWindow
{
    Q_OBJECT

public:
    QrCodeWindow(QWidget *parent = nullptr);
    ~QrCodeWindow();
private:
    QTextEdit* userInput;
    QPushButton* generateButton;
    QLabel* qrCodeLabel;

private slots:
    void generateQrCode();

};
#endif // QRCODEWINDOW_H
