#include "widget.h"
#include "ui_widget.h"
#include"people.h"
#include<QSoundEffect>
#include"ground.h"
#include"deadwater.h"
#include"door.h"
#include"stone.h"
#include"mechanism.h"
#include"win.h"
#include"stop.h"
Ground ground;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    p=new QTimer(this);
    p->callOnTimeout(this,[=]{
        update();
    });
    p->start(1000/60);
    output=new QAudioOutput(this);
    player=new QMediaPlayer;
    player->setAudioOutput(output);
}

Widget::~Widget()
{
    delete ui;
    delete pe;
    delete pl;
    delete player;
    delete d1;
    delete d2;
    delete video;
    delete output;
    for (Stone* stone : stones) delete stone;
    for(Mechanism* me:mechanisms) delete me;

}
void Widget::inigame()
{
    this->setWindowTitle("森林冰火人");

}
void Widget::keyPressEvent(QKeyEvent *ev)
{
    if (keysPressed.contains(ev->key())) {
        return; // If the key is already pressed, do nothing
    }
    keysPressed.insert(ev->key());

    if(ev->key()==Qt::Key_Escape){
        this->player->stop();
        extern stop*sp;
        sp=new stop(this);
        sp->show();
        this->hide();
    }
    if (ev->key() == Qt::Key_A) {
        if (!keysPressed.contains(Qt::Key_D)) {
            pe->speed.setX(pe->speed.x() - 1);
            if (pe->speed.x() <= -1) pe->speed.setX(-1);
        }
    } else if (ev->key() == Qt::Key_W && pe->speed.y() == 0) {
        pe->speed.setY(pe->speed.y() - 2.5);
    } else if (ev->key() == Qt::Key_D) {
        pe->speed.setX(pe->speed.x() + 1);
        if (pe->speed.x() >= 1) pe->speed.setX(1);
    }

    if (ev->key() == Qt::Key_Left) {
        if (!keysPressed.contains(Qt::Key_Right)) {
            pl->speed.setX(pl->speed.x() - 1);
            if (pl->speed.x() <= -1) pl->speed.setX(-1);
        }

    } else if (ev->key() == Qt::Key_Up && pl->speed.y() == 0) {
        pl->speed.setY(pl->speed.y() - 2.5);

    } else if (ev->key() == Qt::Key_Right) {
        pl->speed.setX(pl->speed.x() + 1);
        if (pl->speed.x() >= 1) pl->speed.setX(1);

    }
}

void Widget::keyReleaseEvent(QKeyEvent *ev)
{
    keysPressed.remove(ev->key());

    if (ev->key() == Qt::Key_A) {
        if (keysPressed.contains(Qt::Key_D)) {
            pe->speed.setX(1); // Continue moving right if D is pressed
        } else {
            pe->speed.setX(0);
        }
    } else if (ev->key() == Qt::Key_W) {
    } else if (ev->key() == Qt::Key_D) {
        if (keysPressed.contains(Qt::Key_A)) {
            pe->speed.setX(-1); // Continue moving left if A is pressed
        } else {
            pe->speed.setX(0);
        }
    }

    if (ev->key() == Qt::Key_Left) {
        if (keysPressed.contains(Qt::Key_Right)) {
            pl->speed.setX(1); // Continue moving right if D is pressed
        } else {
            pl->speed.setX(0);
        }

    } else if (ev->key() == Qt::Key_Up) {

    } else if (ev->key() == Qt::Key_Right) {
        if (keysPressed.contains(Qt::Key_Left)) {
            pl->speed.setX(-1); // Continue moving left if A is pressed
        } else {
            pl->speed.setX(0);
        }

    }

}
void Widget::paintEvent(QPaintEvent* event)
{

    QPainter painter(this);
    QPixmap picture;
    picture.load(":/new/prefix1/background.png");
    QSize newsize(800,800);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(0,0),picture);
    for(auto i=water.begin();i<water.end();i++)
    {
        (*i).paint(&painter);
        (*i).GoinWater(pe);
        (*i).GoinWater(pl);
    }

    for (const auto& groundPolygon : ground.getGroundPolygons()) {
        if (groundPolygon.canConvert<QRectF>()) {
            QRectF c=groundPolygon.toRectF();
            for(int i=0;i<c.height()/20;i++)
                for(int j=0;j<c.width()/20;j++)
                {
                    if(i==0)   picture.load(":/new/prefix1/ground.png");
                    else picture.load(":/new/prefix1/ground-nograss.png");
                    QSize newsize(20,20);
                    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    QPoint p(c.x()+j*20,c.y()+i*20);
                    painter.drawPixmap(p,picture);
                }
            //painter.fillRect(groundPolygon.toRectF(), Qt::green);
        } else if (groundPolygon.canConvert<QLineF>()) {
            QLineF line = groundPolygon.toLineF();
            qreal slope = (line.p2().y() - line.p1().y()) / (line.p2().x() - line.p1().x());
            if(slope < 0) {
                picture.load(":/new/prefix1/slop1.png");
            } else {
                picture.load(":/new/prefix1/slop2.png");
            }

            QPointF p;
            qreal length = line.length();
            qreal stepSize = 50;  // 每一步移动 50 像素

            if(slope>0)
            {
                for(qreal i = 0; i < length; i += stepSize) {
                    qreal ratio = i / length;
                    p.setX(line.x1() + ratio * (line.x2() - line.x1()));
                    p.setY(line.y1() + ratio * (line.y2() - line.y1()));
                    painter.drawPixmap(p.toPoint(), picture);
                }
            }
            if(slope<0)
            {
                qreal pictureHeight = picture.height();
                qreal pictureWidth = picture.width();
                for (qreal i = 0; i < length; i += stepSize) {
                    qreal ratio = i / length;
                    p.setX(line.x1() + ratio * (line.x2() - line.x1()));
                    p.setY(line.y1() + ratio * (line.y2() - line.y1()));

                    // 调整图片的位置，使其正确对齐线段
                    QPointF adjustedP = p;
                    if (slope > 0) {
                        adjustedP.setY(p.y() - pictureHeight);  // 根据图片的高度调整Y坐标
                    } else {
                        adjustedP.setY(p.y() - pictureHeight );  // 根据图片的高度调整Y坐标
                    }
                    painter.drawPixmap(adjustedP.toPoint(), picture);
                }
            }
        }

    }
    for(Mechanism* me:mechanisms)
    {
        for(QRectF te:me->triggerAreas){
            picture.load(me->chfilename);
            QPoint p(te.x(),te.y());
            painter.drawPixmap(p, picture);
        }
        QSize newsize(me->block_width,me->block_height);
        picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        picture.load(me->mefilename);
        QPoint p(me->position.x(),me->position.y());
        painter.drawPixmap(p,picture);
    }
    picture.load(":/new/prefix1/stone.png");
    for (Stone* stone : stones)
    {
        QSize newsize(50,50);
        picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPoint p=stone->position.toPoint();
        painter.drawPixmap(p,picture);
    }


    if(d1->indoor==false){
        picture.load(d1->filename);
        QSize newsize(50,50);
        picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPoint p=d1->position_door.toPoint();
        painter.drawPixmap(p,picture);
        ui->movie3->hide();
    }
    else {
        ui->movie3->setMovie(d1->in);
        d1->in->start();
        ui->movie3->move(d1->position_door.x(),d1->position_door.y());
        ui->movie3->show();}

    if(d2->indoor==false){
        picture.load(d2->filename);
        QSize newsize(50,50);
        picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPoint p=d2->position_door.toPoint();
        painter.drawPixmap(p,picture);
        ui->movie4->hide();
    }
    else {
        ui->movie4->setMovie(d2->in);
        d2->in->start();
        ui->movie4->move(d2->position_door.x(),d2->position_door.y());
        ui->movie4->show();
    }
    d1->GoinDoor(pe);
    d2->GoinDoor(pl);
    pe->paintEvent(&painter);
    pl->paintEvent(&painter);
    p->stop();
    pe->update(ground,stones,mechanisms,peopleList,triggerAreas);
    pl->update(ground,stones,mechanisms,peopleList,triggerAreas);
    if(d1->indoor&&d2->indoor)
    {
        extern win* w;
        delete this->player;
        w->show();
        this->hide();
    }
    p->start(1000/60);
    p->callOnTimeout(this,[=]{
    if(pe->speed.x()<0)
    {
        ui->movie1->setMovie(pe->leftrun);
        pe->leftrun->start();
        ui->movie1->move(pe->position.x(),pe->position.y());
        ui->movie1->show();
    }
    else if(pe->speed.x()>0)
    {
        ui->movie1->setMovie(pe->rightrun);
        pe->rightrun->start();
        ui->movie1->move(pe->position.x(),pe->position.y());
        ui->movie1->show();
    }
    else if(pe->speed.x()==0)
    {
        ui->movie1->clear();
        ui->movie1->hide();
    }
    if(pl->speed.x()<0)
    {
        ui->movie2->setMovie(pl->leftrun);
        pl->leftrun->start();
        ui->movie2->move(pl->position.x(),pl->position.y());
        ui->movie2->show();
    }
    else if(pl->speed.x()>0)
    {
        ui->movie2->setMovie(pl->rightrun);
        pl->rightrun->start();
        ui->movie2->move(pl->position.x(),pl->position.y());
        ui->movie2->show();
    }
    else if(pl->speed.x()==0)
    {
        ui->movie2->clear();
        ui->movie2->hide();
    }
    });
}
void Widget::winner()
{

    //this->hide();
}
