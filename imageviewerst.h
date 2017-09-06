#ifndef IMAGEVIEWERST_H
#define IMAGEVIEWERST_H

#include <QMainWindow>

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
};

#endif // IMAGEVIEWERST_H
