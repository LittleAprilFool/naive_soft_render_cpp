#include "canvas.h"
#include <QApplication>

#include "cube.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Canvas w;
    w.show();

    Cube cube(10, 10, 0, 20);
    cube.printCube();

    cube.rotate(90, 0, 0);
    cube.printCube();

    return a.exec();
}
