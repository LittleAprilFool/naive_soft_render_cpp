#ifndef CANVAS_H
#define CANVAS_H

#include <QGenericMatrix>
#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QVector>
#include <QTimer>
#include <Qt>

#include "limits.h"
#include "universal.h"
#include "cube.h"
#include "camera.h"

namespace Ui {
class Canvas;
}

typedef struct pixel {
  float depth;
  int face;
  Color color;
} Pixel;

typedef QVector3D Vertex;

typedef struct scanline {
    int number;
    Vertex begin;
    Vertex end;
} Scanline;

typedef struct line {
    bool exist;
    Vertex point;
} Line;



class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();


private slots:
    void updateAnimation();


    void on_pushButton_clicked();

private:
    Ui::Canvas *ui;
    void paintEvent(QPaintEvent *);
    QPainter *paint;
    QTimer *animationTimer;
    Cube *cube;
    Camera *camera;

    void update();

    QVector<QVector<Pixel> > pixel;

    Vertex* vertex;
    Vertex* getVertex();

    void checkFace(Vertex A, Vertex B, Vertex C, Vertex D, int face);
    Scanline checkScanline(int y, Vertex A, Vertex B, Vertex C, Vertex D);
    Line checkLine(int y, Vertex A, Vertex B);

    void zbufferWrite(int x, int y, float z, int face);
    void zbufferFill(Vertex A, Vertex B, int face);
    void zbufferClean();

};

#endif // CANVAS_H
