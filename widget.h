#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QIcon>
#include<QTimer>
#include<QEvent>
#include<QPainter>
#include<QMediaPlayer>
#include <QAudioOutput>
#include<QVideoWidget>
#include<QLabel>
#include"ground.h"
QT_BEGIN_NAMESPACE
class people;
class Stone;
class Door;
class Mechanism;
class DeadWater;

namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    people*pe,*pl;
    QTimer*p;
    QVector<Stone*> stones;
    Widget(QWidget *parent = nullptr);
    void inigame();
    ~Widget();
    void keyPressEvent(QKeyEvent* ev)override;
    void updategame();
    void paintEvent(QPaintEvent* event)override;
    void keyReleaseEvent(QKeyEvent *ev)override;
    void run();
    QMediaPlayer* player ;
    QAudioOutput* output;
    QVideoWidget* video;
    int id=0;
    QVector<DeadWater> water;
    QVector<Mechanism*> mechanisms;
    Door*d1;
    Door*d2;
    QVector<people*>peopleList;
    QVector<QRectF> triggerAreas;
    Ground ground;
signals:
    void ifwin();
private slots:
    void winner();
private:
    Ui::Widget *ui;
    QSet<int> keysPressed;
};
#endif // WIDGET_H
