#include "win.h"
#include "ui_win.h"
#include<QMovie>
#include<QDebug>
#include"choose.h"
win::win(QWidget *parent)
    : QWidget(parent), picture(":/new/prefix1/iswin.png")
    , ui(new Ui::win)
{
    ui->setupUi(this);
    mov = new QMovie(":/new/prefix1/Victory.gif");
    ui->movie->setMovie(mov);
    ui->movie->show();
    connect(mov, &QMovie::frameChanged, this, [this](int frameNumber) {
        if (frameNumber == mov->frameCount() - 1) {
            mov->stop();
            ui->movie->hide();

        }
    });

}
void win::paintEvent(QPaintEvent* event)
{
    mov->start();
    QPainter painter(this);
    QSize newsize(800, 800);
    picture = picture.scaled(newsize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0, 0), picture);
}
win::~win()
{
    delete mov;
    delete ui;
}

void win::on_return_2_clicked()
{
    extern choose*ch;
    ch->show();
    this->hide();
}

