#include "start.h"
#include "ui_start.h"
#include"choose.h"
start::start(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::start)
{
    ui->setupUi(this);
}
void start::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap picture;
    picture.load(":/new/prefix1/start.png");
    QSize newsize(800,800);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0,0),picture);
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
    extern choose* ch;
    this->hide();
    ch->show();
}

