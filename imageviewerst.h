#ifndef IMAGEVIEWERST_H
#define IMAGEVIEWERST_H

#include <QMainWindow>
#include <qlabel>
#include <qscrollarea>

namespace Ui {
class ImageViewerST;
}

class ImageViewerST : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageViewerST(QWidget *parent = 0);
    ~ImageViewerST();

private:
    Ui::ImageViewerST *ui;
    QLabel *imageLabel;
    QScrollArea *scrollArea;
};

#endif // IMAGEVIEWERST_H
