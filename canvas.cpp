#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    for(int i = 0; i < 800; i ++) {
        QVector<Pixel> row;
        for(int j = 0; j < 600; j ++) {
            Pixel pix;
            Color white(255,255,255);
            pix.depth = INT_MIN;
            pix.face = 0;
            pix.color = white;
            row.append(pix);
        }
        this->pixel.append(row);
    }

    cube = new Cube(10, 10, 0, 200);
    camera = new Camera(-200, 200, 200, -200, -400, -200);

    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()), this, SLOT(updateAnimation()));

    ui->setupUi(this);
}

void Canvas::updateAnimation(){
    cube->rotate(5,5,5);
    this->zbufferClean();
    this->update();
    repaint();
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::paintEvent(QPaintEvent *)
{
    paint = new QPainter;
    paint->begin(this);

    float max_depth = float(INT_MIN);
    float min_depth = float(INT_MAX);

    for(int i = 0; i < 800; i ++)
        for(int j =0; j<600; j ++) {
            if(this->pixel[i][j].face!=0){
                if (this->pixel[i][j].depth > max_depth) max_depth = this->pixel[i][j].depth;
                if (this->pixel[i][j].depth < min_depth) min_depth = this->pixel[i][j].depth;
            }
        }

    for(int i = 0; i < 800; i ++)
        for(int j = 0; j < 600; j ++) {
            if(this->pixel[i][j].face!= 0){
                float k = (max_depth - pixel[i][j].depth) / (max_depth - min_depth) ;
                paint->setPen(QColor(200 - 100*k,200 - 100*k,200 - 100*k));
                paint->drawPoint(i,j);
            }
        }
}

Vertex* Canvas::getVertex() {
    Vertex *result = new Vertex[8];
    for (int i = 0; i < 8; i ++) {
        result[i].setX(cube->point(0,i));
        result[i].setY(cube->point(1,i));
        result[i].setZ(cube->point(2,i));
    }
    return result;
}

void Canvas::update() {
    this->vertex = this->getVertex();
    this->checkFace(this->vertex[0], this->vertex[1], this->vertex[2], this->vertex[3], 1);
    this->checkFace(this->vertex[0], this->vertex[4], this->vertex[5], this->vertex[1], 2);
    this->checkFace(this->vertex[1], this->vertex[5], this->vertex[6], this->vertex[2], 3);
    this->checkFace(this->vertex[2], this->vertex[6], this->vertex[7], this->vertex[3], 4);
    this->checkFace(this->vertex[3], this->vertex[7], this->vertex[4], this->vertex[0], 5);
    this->checkFace(this->vertex[4], this->vertex[7], this->vertex[6], this->vertex[5], 6);
}

void Canvas::checkFace(Vertex A, Vertex B, Vertex C, Vertex D, int face) {
    for(int i = 0; i < 600; i ++) {
        Scanline scanline = this->checkScanline(i - 300, A, B, C, D);
        if (scanline.number == 1) {
            this->zbufferWrite(int(scanline.begin.x() + 400), int(scanline.begin.y() + 300), scanline.begin.z(), face);
        }
        else if (scanline.number > 1) {
            this->zbufferFill(scanline.begin, scanline.end, face);
        }
    }
}

Scanline Canvas::checkScanline(int y, Vertex A, Vertex B, Vertex C, Vertex D) {
    Scanline result;
    QVector<Line> line;
    line.append(this->checkLine(y, A, B));
    line.append(this->checkLine(y, B, C));
    line.append(this->checkLine(y, C, D));
    line.append(this->checkLine(y, D, A));

    result.number = 0;

    for(int i = 0; i < line.size(); i ++) {
        if(line[i].exist) {
            if(result.number == 0){
                result.number ++;
                result.begin = line[i].point;
            } else if(result.number == 1) {
                if(line[i].point.x()!=result.begin.x()){
                    result.number ++;
                    if(line[i].point.x() < result.begin.x()) {
                        result.end = result.begin;
                        result.begin = line[i].point;
                    }else result.end = line[i].point;
                }
            }
        }
    }

    return result;
}

Line Canvas::checkLine(int y, Vertex A, Vertex B) {
    Line result;
    if(A.y() == B.y() && y == A.y()) {
        result.exist = true;
        if(A.x() < B.x()) result.point = A;
        else result.point = B;
        return result;
    }

    if((y - A.y()) * (y - B.y()) < 0) {
        result.exist = true;
        float k = (y - B.y()) / (B.y() - A.y());
        result.point.setX(k * (B.x() - A.x()) + B.x());
        result.point.setY(y);
        result.point.setZ(k * (B.z() - A.z()) + B.z());
    }
    else result.exist = false;
    return result;
}

void Canvas::zbufferFill(Vertex A, Vertex B, int face) {
    for(int i = int(A.x()); i < int(B.x()); i++) {
        float iz;
        if(A.z() == B.z()) iz = A.z();
        else iz = (A.z() - B.z()) * (i - B.x()) / (A.x() - B.x()) + B.z();
        this->zbufferWrite(i + 400, int(A.y() + 300), iz, face );
    }
}

void Canvas::zbufferWrite(int x, int y, float z, int face){
    if(z > this->pixel[x][y].depth) {
        this->pixel[x][y].depth = z;
        this->pixel[x][y].face = face;
    }
}

void Canvas::zbufferClean(){
    for(int i = 0; i < 800; i ++)
        for(int j = 0; j < 600; j ++) {
            this->pixel[i][j].depth = INT_MIN;
            this->pixel[i][j].face = 0;
        }
}

void Canvas::on_pushButton_clicked()
{
    animationTimer->start();
}
