#include "imageviewerst.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewerST w;
    w.show();

    return a.exec();
}
