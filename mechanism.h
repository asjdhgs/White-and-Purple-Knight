#ifndef MECHANISM_H
#define MECHANISM_H
#include "ground.h"
#include<QVector2D>
class people;
class Ground;
class Mechanism:public QObject
{
    Q_OBJECT
public:
    Ground block;
    QVector2D position;
    QVector2D originalPosition;
    int block_width,block_height;
    int type;
    QVector2D speed={0,0};
    QVector<QRectF> triggerAreas;
    int des_x,des_y;
    QString mefilename;
    QString chfilename;
    QVector2D triggerSpeed;
    const qreal epsilon = 0.1;
    Mechanism();
    Mechanism(int type,int x,int y,int width,int height, QVector<QRectF> triggers,int desx,int desy):
        block_width(width),block_height(height),type(type),triggerAreas(triggers),des_x(desx),des_y(desy)
    {
        position.setX(x);
        position.setY(y);
        originalPosition = position;
        block.addFlatGround(x,y,block_width,block_height);
        switch(type)
        {
        case 1:mefilename=":/new/prefix1/board.png";chfilename=":/new/prefix1/button-up.png";break;
        case 2:mefilename=":/new/prefix1/greenboard.png";chfilename=":/new/prefix1/greenbutton-up.png";break;
        case 3:mefilename=":/new/prefix1/redboard.png";chfilename=":/new/prefix1/redbutton-up.png";break;
        }
    }
    void Move(int dx, int dy);
    void MoveToOriginalPosition();
    QRectF getRect() const {
        return QRectF(position.x(), position.y(), block_width, block_height);
    }
    void checkDestination();
    void updatePosition();

public slots:
    void onPeopleEnter();
    void onPeopleLeave();

private:

};

#endif // MECHANISM_H
