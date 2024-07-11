#ifndef STONE_H
#define STONE_H
#include "ground.h"
#include<QVector2D>
#include<QTimer>
class Ground;
class Stone
{
public:
public:
    Ground rock;
    QVector2D position;
    qreal width, height;

    QVector2D speed = {0, 0}; // 石头的速度
    QVector2D a = {0, 0.05};   // 加速度
    Stone() ;
    int v=3;
    Stone(qreal x, qreal y, qreal width, qreal height)
        : position(x, y), width(width), height(height)
    {
        rock.addFlatGround(x, y, width, height);
    }

    void move(QVector2D offset);
    void update(const Ground& ground);
    void updateposition();
};

#endif // STONE_H
