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
    actionRotateLeft = ui->actionRotateLeft;
    actionRotateRight = ui->actionRotateRight;

    actionZoomIn->setEnabled(false);
    actionZoomOut->setEnabled(false);
    actionRotateLeft->setEnabled(false);
    actionRotateRight->setEnabled(false);

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


void ImageViewerST::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    int newValue = factor * scrollBar->value() + (factor - 1) * scrollBar->pageStep() / 2;
    scrollBar->setValue(newValue);
}


void ImageViewerST::on_actionOpen_triggered()
{
        QString lastFileName = fileName.isEmpty() ? QDir::currentPath() : fileName;
        fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"),
                                                     lastFileName);
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
             actionRotateLeft->setEnabled(true);
             actionRotateRight->setEnabled(true);

             imageLabel->adjustSize();
        }
}

void ImageViewerST::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

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
