#include "qrcodewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <qrencode.h> // Include the QRcode header from libqrencode

QrCodeWindow::QrCodeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* vLayout = new QVBoxLayout();
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);


    userInput = new QTextEdit(this);
    userInput->setMinimumHeight(100);
    userInput->setMinimumWidth(200);
    userInput->setAlignment(Qt::AlignLeft);
    userInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    generateButton = new QPushButton("generate");
    generateButton->setFixedHeight(100);
    generateButton->setFixedWidth(150);

    QHBoxLayout *topPanel = new QHBoxLayout(this);
    topPanel->setSpacing(50);
    topPanel->addWidget(userInput);
    topPanel->addWidget(generateButton);

    qrCodeLabel = new QLabel();
    qrCodeLabel->setFixedSize(200,200);
    qrCodeLabel->setStyleSheet("border:5px solid black");

 //   QSpacerItem *vSpacer = new QSpacerItem(20,20,QSizePolicy::Minimum, QSizePolicy::Expanding);

    vLayout->addLayout(topPanel);
    vLayout->addWidget(qrCodeLabel, Qt::AlignBottom, Qt::AlignCenter);

    //vLayout->addItem(vSpacer);

    // connect the generate button signal to a slot that will generate the qr code
    connect(generateButton,&QPushButton::clicked, this, &QrCodeWindow::generateQrCode);


    setWindowTitle("QRCode Generator");
    resize(500,500);

}

void QrCodeWindow::generateQrCode()
{
    //get the user data
    if(userInput->toPlainText().isEmpty())
        return;

    QString qrcodeData = userInput->toPlainText();


}

QrCodeWindow::~QrCodeWindow() {
    if(userInput)
        delete userInput;
}
