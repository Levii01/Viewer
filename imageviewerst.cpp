#include "imageviewerst.h"
#include "ui_imageviewerst.h"

ImageViewerST::ImageViewerST(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ImageViewerST)
{
    ui->setupUi(this);

    actionCrop = ui->actionCrop;
    actionSave = ui->actionSave;
    actionOpen = ui->actionOpen;
    actionZoomIn = ui->actionZoomIn;
    actionZoomOut = ui->actionZoomOut;
    actionRotateLeft = ui->actionRotateLeft;
    actionRotateRight = ui->actionRotateRight;
    actionShowToolbar = ui->actionShowToolbar;
    actionScale = ui->actionScale;
    actionToggleFullscren = ui->actionToggleFullscren;

    statusBar = ui->statusBar;
    mainToolBar = ui->mainToolBar;

    toggleActivityActions(false);


    imageLabel = new QLabel;
    imageLabel->resize(0, 0);
    imageLabel->setMouseTracking(true);
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

//functions

void ImageViewerST::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
  int newValue = factor * scrollBar->value() + (factor - 1) * scrollBar->pageStep() / 2;
  scrollBar->setValue(newValue);
}

void ImageViewerST::toggleActivityActions(bool updateTo)
{
    actionZoomIn->setEnabled(updateTo);
    actionZoomOut->setEnabled(updateTo);
    actionRotateLeft->setEnabled(updateTo);
    actionRotateRight->setEnabled(updateTo);
    actionCrop->setEnabled(updateTo);
    actionSave->setEnabled(updateTo);
    actionScale->setEnabled(updateTo);
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

             setCursor(Qt::ArrowCursor);
             toggleActivityActions(true);

             imageLabel->adjustSize();
        }
}

void ImageViewerST::rotateImage(int degrees)
{
    QPixmap pixmap(*imageLabel->pixmap());
    QMatrix rm;
    rm.rotate(degrees);
    pixmap = pixmap.transformed(rm);
    image = pixmap.toImage();
    imageLabel->setPixmap(pixmap);
    imageLabel->adjustSize();
}

void ImageViewerST::changeCroppingImage(bool changeTo)
{
    croppingImage = changeTo;
    actionCrop->setDisabled(changeTo);

    if (changeTo)
    {
        setCursor(Qt::CrossCursor);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
    }
}


bool ImageViewerST::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != imageLabel)
        return false;

    switch (event->type())
    {
        case QEvent::MouseButtonPress:
        {
            if (!croppingImage) break;
            const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
            croppingStart = me->pos() / scaleFactor;
            break;
        }

        case QEvent::MouseButtonRelease:
        {
            if (!croppingImage) break;
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

        case QEvent::MouseMove:
        {
            const QMouseEvent* const me = static_cast<const QMouseEvent*>(event);
            const QPoint position = me->pos();
            statusBar->showMessage(QString("(x,y) coordinates: (%1,%2)").arg(position.x()).arg(position.y()));
        }

        default:
            break;
    }

    return false;
}

//slots

void ImageViewerST::on_actionZoomIn_triggered()
{
    scaleImage(1.25);
}

void ImageViewerST::on_actionZoomOut_triggered()
{
    scaleImage(0.8);
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

void ImageViewerST::on_actionSave_triggered()
{
    QString imagePath = QFileDialog::getSaveFileName(this,
                                                     tr("Save File"),
                                                     "",
                                                     tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

    image.save(imagePath);
}

void ImageViewerST::on_actionShowToolbar_triggered(bool checked)
{
    if (checked)
        mainToolBar->show();
    else
        mainToolBar->hide();
}

void ImageViewerST::on_actionScale_triggered()
{
    QPixmap img(*imageLabel->pixmap());
    int width = QInputDialog::getInt(this, "Scale image", "Set width", img.width(), 10, img.width()*100);
    int height = QInputDialog::getInt(this, "Scale image", "Set height", img.height(), 10, img.height()*100);
    imageLabel->setPixmap(img.scaled(width, height, Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    imageLabel->adjustSize();
}

void ImageViewerST::on_actionToggleFullscren_triggered()
{
    if(isFullScreen())
        this->showNormal();
    else
        this->setWindowState(Qt::WindowFullScreen);
}
