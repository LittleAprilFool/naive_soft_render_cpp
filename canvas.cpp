#include "canvas.h"
#include "ui_canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::paintEvent(QPaintEvent *)
{
    paint = new QPainter;
    paint->begin(this);
    paint->setPen(QPen(QColor(150, 150, 150), 2));
    paint->drawRect(20, 70, 460, 250);
}
