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

    Cube cube(10, 10, 0, 20);
    Camera camera(-200, 200, 200, -200, -400, -200);

    w.update(camera.projectionCube(cube.point));

    return a.exec();
}
