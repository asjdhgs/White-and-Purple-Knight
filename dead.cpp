#include "dead.h"
#include "ui_dead.h"
#include"widget.h"
#include"choose.h"
#include"level1.h"
#include"level2.h"
#include"level3.h"
dead::dead(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::dead)
{
    ui->setupUi(this);
}

dead::~dead()
{
    delete ui;
    delete p;
}
void dead::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap picture;
    picture.load(":/new/prefix1/gameover.png");
    QSize newsize(800,800);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0,0),picture);
}

void dead::on_onceagain_clicked()
{
    if(id==1)
    {
        if(p==nullptr)
        {
            p=new level1;
        }
    }
    if(id==2)
    {
        if(p==nullptr)
        {
            p=new level2;
        }
    }
    if(id==3)
    {
        if(p==nullptr)
        {
            p=new level3;
        }
    }
    p->show();
    p->inigame();
    p->update();
    this->close();
}


void dead::on_return_2_clicked()
{
    extern choose* ch;
    ch->show();
    this->hide();
}

