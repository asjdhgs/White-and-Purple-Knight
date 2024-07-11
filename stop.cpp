#include "stop.h"
#include "ui_stop.h"
#include<QPainter>
#include"widget.h"
#include"start.h"
stop::stop(Widget* p,QWidget *parent)
    : QWidget(parent),w(p)
    , ui(new Ui::stop)
{
    ui->setupUi(this);
}
void stop::paintEvent(QPaintEvent* event)
{
    picture.load(":/new/prefix1/stop.png");
    QPainter painter(this);
    QSize newsize(800, 800);
    picture = picture.scaled(newsize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0, 0), picture);
}
stop::~stop()
{
    delete ui;
}

void stop::on_pushButton_clicked()
{
    w->close();
    extern start*st;
    st->show();
    this->close();
}


void stop::on_pushButton_2_clicked()
{
    w->show();
    this->close();
    w->player->play();
}

