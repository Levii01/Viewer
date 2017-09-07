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
#include <QMouseEvent>
#include <QStatusBar>
#include <QInputDialog>

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
    bool eventFilter(QObject* watched, QEvent* event);
    void on_actionOpen_triggered();
    void on_actionZoomIn_triggered();
    void on_actionZoomOut_triggered();
    void on_actionRotateLeft_triggered();
    void on_actionRotateRight_triggered();
    void on_actionCrop_triggered();
    void on_actionSave_triggered();
    void on_actionShowToolbar_triggered(bool checked);
    void on_actionScale_triggered();
    void on_actionToggleFullscren_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();

private:
    Ui::ImageViewerST *ui;

    QPoint croppingStart;
    QPoint croppingEnd;

    QLabel *imageLabel;

    QScrollArea *scrollArea;

    QString fileName;

    QImage image;

    QStatusBar *statusBar;

    QToolBar *mainToolBar;

    QAction *actionOpen;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionRotateLeft;
    QAction *actionRotateRight;
    QAction *actionCrop;
    QAction *actionSave;
    QAction *actionShowToolbar;
    QAction *actionScale;
    QAction *actionToggleFullscren;
    QAction *actionUndo;
    QAction *actionRedo;

    double scaleFactor;
    bool croppingImage;

    void scaleImage(double factor);
    void toggleActivityActions(bool updateTo);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void rotateImage(int degrees);
    void changeCroppingImage(bool changeTo);
};

#endif // IMAGEVIEWERST_H
