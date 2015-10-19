#include "cube.h"

Cube::Cube(float x, float y, float z, float width) {
    float values[] = {
        -1, 1, 1, 1,
         1, 1, 1, 1,
         1,-1, 1, 1,
        -1,-1, 1, 1,
        -1, 1,-1, 1,
         1, 1,-1, 1,
         1,-1,-1, 1,
        -1,-1,-1, 1
    };

    this->width = width;
    this->center = QVector3D (x, y, z);
    QGenericMatrix<4, 8, float> data(values);
    this->point = data.transposed();
    this->point = scaleMatrix(width/2, width/2, width/2) * this->point;
    this->point = translateMatrix(center.x(), center.y(), center.z()) * this ->point;
}

void Cube::rotate(float xd, float yd, float zd) {
    QGenericMatrix<4, 4, float> rm = this->rotateMatrix(xd, yd, zd);
    QGenericMatrix<4, 4, float> tm = this->translateMatrix(this->center.x(), this->center.y(), this->center.z());
    QGenericMatrix<4, 4, float> ntm = this->translateMatrix(-this->center.x(), -this->center.y(), -this->center.z());
    this->point = ntm * this->point;
    this->point = rm * this->point;
    this->point = tm * this->point;
}

QGenericMatrix<4, 4, float> Cube::translateMatrix(float x, float y, float z){
    float values[] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
    QGenericMatrix<4, 4, float> data(values);
    return data;
}

QGenericMatrix<4, 4, float> Cube::rotateMatrix(float xd, float yd, float zd) {
    float xr = qDegreesToRadians(xd); float xc = qCos(xr); float xs = qSin(xr);
    float yr = qDegreesToRadians(yd); float yc = qCos(yr); float ys = qSin(yr);
    float zr = qDegreesToRadians(zd); float zc = qCos(zr); float zs = qSin(zr);

    float valuex[] = {
        1, 0, 0, 0,
        0, xc, -xs, 0,
        0, xs, xc, 0,
        0, 0, 0, 1
    };

    float valuey[] = {
        yc, 0, ys, 0,
        0, 1, 0, 0,
        -ys, 0, yc, 0,
        0, 0, 0, 1
    };

    float valuez[] = {
        zc,-zs, 0, 0,
        zs, zc, 0, 0,
         0,  0, 1, 0,
         0,  0, 0,  1
    };
    QGenericMatrix<4, 4, float> mx(valuex);
    QGenericMatrix<4, 4, float> my(valuey);
    QGenericMatrix<4, 4, float> mz(valuez);

    QGenericMatrix<4, 4, float> result = mx * my;
    result = result * mz;

    return result;
}

QGenericMatrix<4, 4, float> Cube::scaleMatrix(float a, float f, float k) {
    float value[] = {
        a, 0, 0, 0,
        0, f, 0, 0,
        0, 0, k, 0,
        0, 0, 0, 1,
    };

    QGenericMatrix<4, 4, float> sm(value);
    return sm;
}

void Cube::printCube() {
    for (int i = 0; i < 8; i ++) {
        qDebug()<< this->point(0, i) <<this->point(1, i) << this->point(2, i) <<this->point(3, i);
    }
}
