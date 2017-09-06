#ifndef IMAGEVIEWERST_H
#define IMAGEVIEWERST_H

#include <QMainWindow>
#include <qlabel>
#include <qscrollarea>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QScrollBar>

namespace Ui {
class ImageViewerST;
}

class ImageViewerST : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewerST(QWidget *parent = 0);
    ~ImageViewerST();

private slots:
    void on_actionOpen_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionRotateLeft_triggered();
    void on_actionRotateRight_triggered();

private:
    Ui::ImageViewerST *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
    QString fileName;

    QAction *actionOpen;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionRotateLeft;
    QAction *actionRotateRight;
    QAction *actionCrop;

    double scaleFactor;

    void scaleImage(double factor);
    void toggleActivityActions(bool updateTo);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void rotateImage(int degrees);
};

#endif // IMAGEVIEWERST_H
