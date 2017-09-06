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

private:
    Ui::ImageViewerST *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

    QAction *actionOpen;
    QAction *actionZoomIn;
    QAction *actionZoomOut;

    double scaleFactor;

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
};

#endif // IMAGEVIEWERST_H
