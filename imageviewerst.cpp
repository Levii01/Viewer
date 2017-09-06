#include "imageviewerst.h"
#include "ui_imageviewerst.h"

ImageViewerST::ImageViewerST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerST)
{
    ui->setupUi(this);

    actionOpen = ui->actionOpen;

    imageLabel = ui->imageLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true); // full view

    scrollArea = ui->scrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);

    setWindowTitle(tr("Image Viewer Project"));
}

ImageViewerST::~ImageViewerST()
{
    delete ui;
}

void ImageViewerST::on_actionOpen_triggered()
{
    qDebug() << "open()";
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open File"),
                                                        QDir::currentPath());
        if (!fileName.isEmpty()) {
             QImage image(fileName);
             if (image.isNull()) {
                 QMessageBox::information(this,
                                          tr("Image Viewer"),
                                          tr("Cannot load %1.").arg(fileName));

                 return;
             }
             imageLabel->setPixmap(QPixmap::fromImage(image));
        }
}
