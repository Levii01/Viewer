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
    actionCrop = ui->actionCrop;
    actionSave = ui->actionSave;

    toggleActivityActions(false);

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true); // full view
    imageLabel->installEventFilter(this);

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

void ImageViewerST::toggleActivityActions(bool updateTo)
{
    actionZoomIn->setEnabled(updateTo);
    actionZoomOut->setEnabled(updateTo);
    actionRotateLeft->setEnabled(updateTo);
    actionRotateRight->setEnabled(updateTo);
    actionCrop->setEnabled(updateTo);
    actionSave->setEnabled(updateTo);
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
             image = QImage(fileName);
             if (image.isNull()) {
                 QMessageBox::information(this,
                                          tr("Image Viewer"),
                                          tr("Cannot load %1.").arg(fileName));

                 return;
             }
             imageLabel->setPixmap(QPixmap::fromImage(image));
             scaleFactor = 1.0;
             croppingImage = false;

             toggleActivityActions(true);

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

void ImageViewerST::rotateImage(int degrees)
{
    QPixmap pixmap(*imageLabel->pixmap());
    QMatrix rm;
    rm.rotate(degrees);
    pixmap = pixmap.transformed(rm);
    image = pixmap.toImage();
    imageLabel->setPixmap(pixmap);
    scaleImage(1);
}

void ImageViewerST::on_actionRotateLeft_triggered()
{
    rotateImage(-90);
}

void ImageViewerST::on_actionRotateRight_triggered()
{
    rotateImage(90);
}

void ImageViewerST::on_actionCrop_triggered()
{
    changeCroppingImage(true);
}

void ImageViewerST::changeCroppingImage(bool changeTo)
{
    croppingImage = changeTo;
    actionCrop->setDisabled(changeTo);
}


bool ImageViewerST::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != imageLabel || !croppingImage)
        return false;

    switch (event->type())
    {
        case QEvent::MouseButtonPress:
        {
            const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
            croppingStart = me->pos() / scaleFactor;
            break;
        }

        case QEvent::MouseButtonRelease:
        {
            const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
            croppingEnd = me->pos() / scaleFactor;

            QRect rect(croppingStart, croppingEnd);
            image = image.copy(rect);
            imageLabel->setPixmap(QPixmap::fromImage(image));
            imageLabel->adjustSize();
            scaleImage(1.0);

            changeCroppingImage(false);
            break;
        }

        default:
            break;
    }

    return false;
}

void ImageViewerST::on_actionSave_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this,
                                                     tr("Save File"),
                                                     "",
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

    image.save(imagePath);
}
