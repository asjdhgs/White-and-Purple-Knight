#include "stone.h"
#include"ground.h"
void Stone::update(const Ground& ground)
{
    if(position.x()+speed.x()*v>750) speed.setX(0);
    if (position.x()+speed.x()*v<0) speed.setX(0);
    if(position.y()+speed.y()*v>750) speed.setY(0);
    if(position.y()+speed.y()*v<0) speed.setY(0);

    // 暂存当前速度和位置以进行碰撞检测
    QVector2D tempSpeed = speed * v;
    QVector2D tempPosition = position + tempSpeed;
    bool onGround = false;
    bool onWall = false;
    bool onTopOfWall=false;
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
            if(onWall)
            {
                if(tempPosition.y() + height <= rect.y())
                {
                    onTopOfWall=true;
                }
            }
        }

    }
    if (onGround) {
        speed.setY(0);
    }
    if(onWall){
        speed.setX(0);
    }

}
void Stone::updateposition()
{
    position+=speed*v;
}
