#include "lucky.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Lucky w;
    w.show();

    return a.exec();
}
