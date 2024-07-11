#include "door.h"
#include"widget.h"
#include"people.h"
#include"start.h"
void Door::GoinDoor(people* peo)
{
    if(peo->position.x()+peo->width-15<=position_door.x()+width&&
        peo->position.x()+20>=position_door.x()&&
        peo->speed.x()==0&&peo->speed.y()==0&&
        peo->position.y()+peo->height<=position_door.y()+height&&
        peo->position.y()+20>=position_door.y())
    {
        //插入进门的gif
        /*start* st=new start;
        w->hide();
        st->show();*/
        indoor=true;

    }
    else {indoor=false;}
}
void Door::Putgif(int x,int y){
    //插入门的图片


}
