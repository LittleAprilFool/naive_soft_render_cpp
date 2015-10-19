#include "canvas.h"
#include "cube.h"
#include "camera.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Canvas w;
    w.show();

    Cube cube(10, 10, 0, 20);
    cube.printCube();

    cube.rotate(90, 0, 0);
    cube.printCube();

    Camera camera(-200, 200, 200, -200, -400, -200);

    return a.exec();
}
