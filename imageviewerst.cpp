#include "imageviewerst.h"
#include "ui_imageviewerst.h"

ImageViewerST::ImageViewerST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerST)
{
    ui->setupUi(this);

    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true); // full view

    ui->scrollArea->setBackgroundRole(QPalette::Dark);

    QImage image("/Users/emsi/Desktop/image.png");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));

    setWindowTitle(tr("Image Viewer Project"));
}

ImageViewerST::~ImageViewerST()
{
    delete ui;
}
