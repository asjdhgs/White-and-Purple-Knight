#include "deadwater.h"
#include"people.h"
#include"widget.h"
#include"dead.h"
bool DeadWater::IsinWater(people*pe)
{

    if(pe->position.y()+pe->height>position_water.y()&&
        pe->position.y()<position_water.y()&&
        pe->position.x()+pe->width/2>position_water.x()&&
        pe->position.x()+pe->width/2<position_water.x()+width&&id!=pe->id)
    {
        return true;
    }else return false;
}
void DeadWater::GoinWater(people*pe)
{
    if(DeadWater::IsinWater(pe)){
        //结束游戏
        if(d==nullptr) d=new dead;
        d->id=w->id;
        delete w->player;
        w->close();
        d->show();

    }
}
void DeadWater::paint(QPainter *event)
{
    picture.load(filename);
    QSize newsize(20,20);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    for(int i=0;i<width/20;i++)
    {
        QPoint p=position_water.toPoint();
        p.setX(p.x()+i*20);
        event->drawPixmap(p,picture);
    }
}
