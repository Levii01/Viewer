#include "imageviewerst.h"
#include "ui_imageviewerst.h"

ImageViewerST::ImageViewerST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerST)
{
    ui->setupUi(this);

    QImage image("/Users/emsi/Desktop/image.png");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}

ImageViewerST::~ImageViewerST()
{
    delete ui;
}
