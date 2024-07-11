#ifndef DOOR_H
#define DOOR_H
#include<QVector2D>
#include<QMovie>
class people;
class Widget;
class Door
{
public:
    int id;
    QVector2D position_door;
    int width,height;
    Widget* w;
    QString filename;
    QString infile;
    Door(int id,int x,int y,int width,int height,Widget*p):id(id),width(width),height(height),w(p){
        position_door.setX(x);
        position_door.setY(y);
        if(id==1){filename=":/new/prefix1/whitedoor.png";}
        else filename=":/new/prefix1/purpledoor.png";
        infile=":/new/prefix1/dooropen.gif";
        in=new QMovie(infile);
    }
    QMovie* in;
    bool indoor=false;
    void GoinDoor(people* peo);
    void Putgif(int x,int y);

};

#endif // DOOR_H
