#include "people.h"
#include"ground.h"
#include"stone.h"
#include"widget.h"
#include"mechanism.h"
people::people(int x,QTimer*p,Widget* w,QVector2D ini){
    id=x;
    jiemian=w;
    t=p;
    position=ini;
    if(x==1){
        filename=":/new/prefix1/Knight_H.png";
        left=":/new/prefix1/Knight_H-leftmove.gif";
        right=":/new/prefix1/Knight_H-rightmove.gif";
    }
    if(x==2)
    {
        filename=":/new/prefix1/purple.png";
        left=":/new/prefix1/Special-Knight-leftmove.gif";
        right=":/new/prefix1/Special-Knight-rightmove.gif";
    }
    leftrun=new QMovie(left);
    rightrun=new QMovie(right);
}
void people::paintEvent(QPainter *event)
{
    if(speed.x()==0){
    picture.load(filename);
    QSize newsize(50,50);
    picture=picture.scaled(newsize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
    event->drawPixmap(position.toPoint(),picture);}
}
void people::update(const Ground& ground,QVector<Stone*>& stones,
                    QVector<Mechanism*>&mechanisms,QVector<people*>peopleList,
                    QVector<QRectF> triggerAreas)
{
    speed+=a;
    if(position.x()+speed.x()*v>750) speed.setX(0);
    if (position.x()+speed.x()*v<0) speed.setX(0);
    if(position.y()+speed.y()*v>750) speed.setY(0);
    if(position.y()+speed.y()*v<0) speed.setY(0);

    // 暂存当前速度和位置以进行碰撞检测
    QVector2D tempSpeed = speed * v;
    QVector2D tempPosition = position + tempSpeed;
    bool onGround = false;
    bool onWall = false;
    for (const auto& groundPolygon : ground.getGroundPolygons()) {
        if (groundPolygon.canConvert<QLineF>()) {
            QLineF line = groundPolygon.toLineF();
            qreal slope = (line.p2().y() - line.p1().y()) / (line.p2().x() - line.p1().x());
            qreal yIntercept = line.p1().y() - slope * line.p1().x();
            qreal groundY = slope * (tempPosition.x()+width/2) + yIntercept;
            if (tempPosition.x()+width/2 > std::min(line.p1().x(), line.p2().x()) &&
                tempPosition.x()+width/2 < std::max(line.p1().x(), line.p2().x()) &&
                tempPosition.y() + height > groundY &&
                tempPosition.y() + height < groundY + height) {
                tempPosition.setY(groundY - height);
                onGround=true;
                tempSpeed.setY(0);
                if(speed.x()<0){speed.setX(-0.5);speed.setY(-0.5*slope);onGround=false;}
                if(speed.x()>0){speed.setY(slope);onGround=false;}



            }
        } else if (groundPolygon.canConvert<QRectF>())
        {
            QRectF rect = groundPolygon.toRectF();
            if (tempPosition.y() + height > rect.y() &&
                tempPosition.y()<rect.y()+rect.height()&&
                tempPosition.x() + width > rect.x() &&
                tempPosition.x() < rect.x() + rect.width())
            {

                tempSpeed.setY(0);
                onGround = true;
            }
            if (tempPosition.x() <= rect.x() + rect.width() &&
                tempPosition.x() + width >= rect.x() + rect.width() &&
                tempPosition.y() + height > rect.y()+1 &&
                tempPosition.y() < rect.y() + rect.height())
            {
                tempSpeed.setX(0);

                onWall = true;
            }
            if (tempPosition.x() + width >= rect.x() &&
                tempPosition.x() <= rect.x() &&
                tempPosition.y() + height > rect.y()+1 &&
                tempPosition.y() < rect.y() + rect.height())
            {
                tempSpeed.setX(0);

                onWall = true;
            }
        }
    }
    for (Stone* stone : stones)
    {

        stone->update(ground);
        bool ifpush=false;
        stone->speed+=stone->a;
        QRectF rect(stone->position.x(), stone->position.y(), stone->width, stone->height);
        if (tempPosition.y() + height > rect.y() &&
            tempPosition.y()<rect.y()+rect.height()&&
            tempPosition.x() + width > rect.x() &&
            tempPosition.x() < rect.x() + rect.width())
        {
            tempSpeed.setY(0);
            onGround = true;
        }
        if (tempPosition.x() <= rect.x() + rect.width() &&
            tempPosition.x() + width >= rect.x() + rect.width() &&
            tempPosition.y() + height > rect.y()+1 &&
            tempPosition.y() < rect.y() + rect.height())
        {
            if(speed.x()!=0){
                stone->speed.setX(-0.5);
                speed.setX(-0.5);}
            ifpush=true;
            stone->update(ground);
            if(stone->speed.x()==0) onWall = true;
            speed.setX(stone->speed.x());
        }
        if (tempPosition.x() + width >= rect.x() &&
            tempPosition.x() <= rect.x() &&
            tempPosition.y() + height > rect.y()+1 &&
            tempPosition.y() < rect.y() + rect.height())
        {
            if(speed.x()!=0){
                stone->speed.setX(0.5);
                speed.setX(0.5);}
            stone->update(ground);
            ifpush=true;
            if(stone->speed.x()==0) onWall = true;
            speed.setX(stone->speed.x());
        }
        if(!ifpush) stone->speed.setX(0);
        stone->update(ground);
    }
    for (Mechanism* mechanism : mechanisms)
    {
        QRectF rect = mechanism->getRect();
        if (tempPosition.y() + height > rect.y() &&
            tempPosition.y() < rect.y() + rect.height() &&
            tempPosition.x() + width > rect.x() &&
            tempPosition.x() < rect.x() + rect.width())
        {
            tempSpeed.setY(0);
            onGround = true;
            if(mechanism->speed.y()!=0)
            {
                position.setY(rect.y()-height-1);
            }
        }
        if (tempPosition.x() <= rect.x() + rect.width() &&
            tempPosition.x() + width >= rect.x() + rect.width() &&
            tempPosition.y() + height > rect.y() + 1 &&
            tempPosition.y() < rect.y() + rect.height())
        {
            if(mechanism->speed.x()==0)
            {
                tempSpeed.setX(0);
            }
            else if(mechanism->speed.x()>0)
            {
                position.setX(rect.x()+rect.width()+1);
            }
            onWall = true;
        }
        if (tempPosition.x() + width >= rect.x() &&
            tempPosition.x() <= rect.x() &&
            tempPosition.y() + height > rect.y() + 1 &&
            tempPosition.y() < rect.y() + rect.height())
        {
            if(mechanism->speed.x()==0)
            {
                tempSpeed.setX(0);
            }
            else if(mechanism->speed.x()<0)
            {
                position.setX(rect.x()-width-1);
            }
            onWall = true;
        }
        // 检查第一个触发区域
        QRectF rect1 = mechanism->triggerAreas[0];
        bool isAnyPersonInTriggerArea1 = false;
        for (people* p : peopleList)
        {
            QRectF triggerRect = rect1;
            if (p->position.x() + width - 15 <= triggerRect.x() + triggerRect.width() &&
                p->position.x() + 20 >= triggerRect.x() &&
                p->position.y() + height <= triggerRect.y() + triggerRect.height() &&
                p->position.y() + 20 >= triggerRect.y())
            {
                isAnyPersonInTriggerArea1 = true;
                break;
            }
        }

        // 检查第二个触发区域
        QRectF rect2 = mechanism->triggerAreas[1];
        bool isAnyPersonInTriggerArea2 = false;
        for (people* p : peopleList)
        {
            QRectF triggerRect = rect2;
            if (p->position.x() + width - 15 <= triggerRect.x() + triggerRect.width() &&
                p->position.x() + 20 >= triggerRect.x() &&
                p->position.y() + height <= triggerRect.y() + triggerRect.height() &&
                p->position.y() + 20 >= triggerRect.y())
            {
                isAnyPersonInTriggerArea2 = true;
                break;
            }
        }

        // 根据两个触发区域的状态调用机关的进入或离开函数
        if (isAnyPersonInTriggerArea1 || isAnyPersonInTriggerArea2) {
            mechanism->onPeopleEnter();
        } else {
            mechanism->onPeopleLeave();
        }
    }
    // 更新位置和速度
    if (onGround) {
        speed.setY(0);
    }
    if(onWall){
        speed.setX(0);
    }
    position += speed * v;
    for (Stone* stone : stones)
    {
        stone->position+=stone->speed*stone->v;
    }

}
