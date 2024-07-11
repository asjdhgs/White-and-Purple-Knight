#include "mechanism.h"
#include"people.h"
#include"widget.h"

Mechanism::Mechanism() {}

void Mechanism::Move(int dx, int dy)
{
    speed.setX(dx);
    speed.setY(dy);
    updatePosition();

}

void Mechanism::updatePosition()
{
    qreal dx = speed.x();
    qreal dy = speed.y();
    position.setX(position.x() + dx);
    position.setY(position.y() + dy);
    block.updatePosition(dx, dy);
    checkDestination();
}
void Mechanism::checkDestination()
{
    if ((speed.x() > 0 && position.x() >= des_x) || (speed.x() < 0 && position.x() <= des_x))
    {
        position.setX(des_x);
        speed.setX(0);
    }
    if ((speed.y() > 0 && position.y() >= des_y) || (speed.y() < 0 && position.y() <= des_y))
    {
        position.setY(des_y);
        speed.setY(0);
    }
}
void Mechanism::MoveToOriginalPosition()
{
    QVector2D direction = originalPosition - position;
    if (direction.length() < epsilon)
    {
        position = originalPosition;
        speed = QVector2D(0, 0);
    }
    else
    {
        speed = direction.normalized() * triggerSpeed.length();
        qreal dx = speed.x();
        qreal dy = speed.y();
        position.setX(position.x() + dx);
        position.setY(position.y() + dy);
        block.updatePosition(dx, dy);
    }
}
void Mechanism::onPeopleEnter()
{
    // 设置移动方向和速度
    triggerSpeed = {0, -3};  // 这里假设触发速度为 (5, 0)，可以根据需要调整
    Move(triggerSpeed.x(), triggerSpeed.y());
}
void Mechanism::onPeopleLeave()
{
    MoveToOriginalPosition();
}
