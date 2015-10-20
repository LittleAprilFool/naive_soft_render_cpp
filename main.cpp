#include "canvas.h"
#include "cube.h"
#include "camera.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Canvas w;
    w.show();

    return a.exec();
}
