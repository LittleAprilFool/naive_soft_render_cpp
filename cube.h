#ifndef CUBE_H
#define CUBE_H
#include "universal.h"

class Cube {
public:
    Cube(float center_x, float center_y, float center_z, float width);
    QVector3D center;
    QGenericMatrix<8, 4, float> point;
    void printCube();
    void rotate(float xd, float yd, float zd);

private:
    float width;
    QGenericMatrix<4, 4, float> translateMatrix(float x, float y, float z);
    QGenericMatrix<4, 4, float> rotateMatrix(float xd, float yd, float zd);
    QGenericMatrix<4, 4, float> scaleMatrix(float a, float f, float k);
};

#endif // CUBE_H
