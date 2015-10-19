#ifndef CAMERA_H
#define CAMERA_H
#include"universal.h"

class Camera
{
public:
    Camera(float left, float right, float top, float bottom, float far, float near);
    QGenericMatrix<8, 4, float> projectionCube(QGenericMatrix<8, 4, float> cube);

private:
    QGenericMatrix<4, 4, float> projectionMatrix;
};

#endif // CAMERA_H
