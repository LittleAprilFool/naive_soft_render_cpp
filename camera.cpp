#include "camera.h"

Camera::Camera(float left, float right, float  top, float bottom, float far, float near)
{
    float value[] = {
        2/(right - left), 0, 0, -(right + left) / (right - left),
        0, 2/(top - bottom), 0, -(top + bottom) / (top - bottom),
        0, 0, -2/(far - near), -(far + near)/(far - near),
        0, 0, 0, 1
    };

    this->projectionMatrix = QGenericMatrix<4, 4, float> (value);
}

QGenericMatrix<8, 4, float> Camera::projectionCube(QGenericMatrix<8, 4, float> cube){
    return this->projectionMatrix * cube;
}

