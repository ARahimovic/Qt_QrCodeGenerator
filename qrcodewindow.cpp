#include "qrcodewindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <qrencode.h> // Include the QRcode header from libqrencode
#include <QImage>
#include <QMessageBox>
#include <QFileDialog>

QrCodeWindow::QrCodeWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QVBoxLayout* vLayout = new QVBoxLayout();
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(vLayout);
    setCentralWidget(centralWidget);
    centralWidget->setFocus();

    userInput = new QTextEdit(this);
    userInput->setMinimumHeight(100);
    userInput->setMinimumWidth(200);
    userInput->setAlignment(Qt::AlignLeft);
    userInput->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    generateButton = new QPushButton("Generate");
    generateButton->setFixedHeight(100);
    generateButton->setFixedWidth(100);

    saveButton = new QPushButton("Save");
    saveButton->setFixedHeight(100);
    saveButton->setFixedWidth(100);

    QHBoxLayout *topPanel = new QHBoxLayout(this);
    topPanel->setSpacing(50);
    topPanel->addWidget(userInput);
    topPanel->addWidget(generateButton);
    topPanel->addWidget(saveButton);

    qrCodeLabel = new QLabel();
    qrCodeLabel->setFixedSize(200,200);
    qrCodeLabel->setStyleSheet("background-color : white;");





 //   QSpacerItem *vSpacer = new QSpacerItem(20,20,QSizePolicy::Minimum, QSizePolicy::Expanding);

    vLayout->addLayout(topPanel);
    vLayout->addWidget(qrCodeLabel, Qt::AlignBottom, Qt::AlignCenter);

    //vLayout->addItem(vSpacer);

    // connect the generate button signal to a slot that will generate the qr code
    connect(generateButton,&QPushButton::clicked, this, &QrCodeWindow::generateQrCode);
    connect(saveButton, &QPushButton::clicked, this, &QrCodeWindow::saveQrCode);

    setWindowTitle("QRCode Generator");
    //resize(500,500);
    setFixedSize(500,500);

}

void QrCodeWindow::generateQrCode()
{
    //get the user data
    if(userInput->toPlainText().isEmpty())
        return;

    QString qrcodeData = userInput->toPlainText();
   // qrCodeLabel->setText(qrcodeData);

    //create a qr code
    QRcode *qrcode = QRcode_encodeString(qrcodeData.toUtf8().constData(), 0,QR_ECLEVEL_L, QR_MODE_8, 1);
    if(!qrcode)
    {
        qrCodeLabel->setText("Failed to Generate QR Code");
        return;
    }

    //create an image of the size of the qlabel
    QSize labelSize = qrCodeLabel->size();
    QImage qrImg(labelSize, QImage::Format_RGB32);
    qrImg.fill(Qt::white);

    //we need the scale so that the qr code fit in the image
    int scale = labelSize.width() / qrcode->width;

    //the bit difference between the label size and the scaled qrcode size
    int offsetX = (labelSize.width() - qrcode->width * scale) / 2;
    int offsetY = (labelSize.height() - qrcode->width * scale) / 2;


    for(int y = 0; y < qrcode->width; y++)
    {
        for(int x = 0; x < qrcode->width; x++)
        {
            if(qrcode->data[y*qrcode->width + x] & 0x01)
            {
                for(int i = 0; i < scale ; i++)
                {
                    for(int j =0; j < scale; j++)
                    {
                        qrImg.setPixel(offsetX + x * scale + i, offsetY + y * scale + j, qRgb(0,0,0));
                    }
                }

            }
        }
    }

    // Convert the QImage to a QPixmap and display it in the QLabel
    qrCodeLabel->setPixmap(QPixmap::fromImage(qrImg));
    QRcode_free(qrcode);

}

void QrCodeWindow::saveQrCode()
{
    if(qrCodeLabel->pixmap().isNull())
    {
        QMessageBox::warning(this, "No Qr code", "Generate QR code before saving");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save QrCode", "", "Images (*.png *.xpm *.jpg)");
    if(fileName.isEmpty())
    {
        return;
    }
    if (!qrCodeLabel->pixmap().save(fileName))
    {
        QMessageBox::warning(this, "Save Error", "Failed to save the QR code image.");
    }


}

QrCodeWindow::~QrCodeWindow() {
    if(userInput)
        delete userInput;
}
