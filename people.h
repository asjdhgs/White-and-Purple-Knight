#ifndef PEOPLE_H
#define PEOPLE_H
#include<QVector2D>
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QEvent>
#include<QDebug>
#include<QMovie>
#include<QMediaPlayer>
#include<QVideoWidget>
#include<QVector>
class Stone;
class Ground;
class Widget;
class Mechanism;
class people:public QObject
{
     Q_OBJECT
public:
    people(int x,QTimer*p,Widget* w,QVector2D ini);
    QVector2D speed={0,0};
    void update(const Ground& ground,QVector<Stone*>& stones,
                QVector<Mechanism*>&mechanisms,QVector<people*>peopleList,
                QVector<QRectF> triggerAreas);
    int id;
    QTimer*t;
    QMovie* leftrun;
    QMovie* rightrun;
    QVector2D position;
    static constexpr qreal width = 50;  // 添加宽度
    static constexpr qreal height = 50; // 添加高度
    void paintEvent(QPainter *event);
    Widget* jiemian;
private:
    int v=3;
    QVector2D a={0,0.1};
    QString filename;
    QString left;
    QString right;
    QPixmap picture;


};

#endif // PEOPLE_H
