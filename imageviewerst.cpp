#include "imageviewerst.h"
#include "ui_imageviewerst.h"

ImageViewerST::ImageViewerST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerST)
{
    ui->setupUi(this);

    actionOpen = ui->actionOpen;
    actionZoomIn = ui->actionZoomIn;
    actionZoomOut = ui->actionZoomOut;

    actionZoomIn->setEnabled(false);
    actionZoomOut->setEnabled(false);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true); // full view

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    setCentralWidget(scrollArea);

    setWindowTitle(tr("Image Viewer Project"));
}

ImageViewerST::~ImageViewerST()
{
    delete ui;
}

void ImageViewerST::on_actionOpen_triggered()
{
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
             scaleFactor = 1.0;

             actionZoomIn->setEnabled(true);
             actionZoomOut->setEnabled(true);

             imageLabel->adjustSize();
        }
}

void ImageViewerST::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    actionZoomIn->setEnabled(scaleFactor < 3.0);
    actionZoomOut->setEnabled(scaleFactor > 0.333);
}

void ImageViewerST::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
}

void ImageViewerST::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
}
