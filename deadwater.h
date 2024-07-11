#ifndef DEADWATER_H
#define DEADWATER_H
#include<QVector2D>
#include<QVector>
#include<QPainter>
class people;
class Widget;
class dead;
class DeadWater
{
public:
    int id;
    int width,height;
    QVector2D position_water;
    DeadWater();
    DeadWater(int id,int x,int y,int width,int height,Widget* p):id(id),width(width),height(height),w(p){
        position_water.setX(x);
        position_water.setY(y);
        if(id==2)filename=":/new/prefix1/river1.png";
        if(id==1)filename=":/new/prefix1/white.png";
        if(id==3)filename=":/new/prefix1/green.png";
    }
    QString filename;
    bool IsinWater(people*pe);
    void GoinWater(people*pe);
    Widget* w;
    dead*d=nullptr;
    void paint(QPainter *event);
    QPixmap picture;

};

#endif // DEADWATER_H
