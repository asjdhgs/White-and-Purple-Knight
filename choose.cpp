#include "choose.h"
#include "ui_choose.h"
#include<QPainter>
#include"widget.h"
#include"start.h"
#include"level1.h"
#include"level2.h"
#include"level3.h"
choose::choose(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::choose)
{
    ui->setupUi(this);
}

void choose::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap picture;
    picture.load(":/new/prefix1/choose.png");
    QSize newsize(800,800);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0,0),picture);
}
choose::~choose()
{
    delete ui;
}

void choose::on_first_clicked()
{
    if(!w) w=new level1;
    else {w->close();w=new level1;}
    this->hide();
    w->show();
    w->inigame();
    w->update();
}


void choose::on_second_clicked()
{
    if(!w) w=new level2;
    else {w->close();w=new level2;}
    this->hide();
    w->show();
    w->inigame();
    w->update();
}


void choose::on_third_clicked()
{
    if(!w) w=new level3;
    else {w->close();w=new level3;}
    this->hide();
    w->show();
    w->inigame();
    w->update();
}


void choose::on_return_2_clicked()
{
    extern start*st;
    this->hide();
    st->show();
}

