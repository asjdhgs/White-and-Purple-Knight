#include "level1.h"
#include "ui_level1.h"
#include"widget.h"
#include<QVector2D>
#include"people.h"
#include<QSoundEffect>
#include"ground.h"
#include"deadwater.h"
#include"door.h"
#include"stone.h"
#include"mechanism.h"
#include"win.h"
#include"stop.h"
level1::level1(QWidget *parent)
    : Widget(parent)
    , ui(new Ui::level1)
{
    ui->setupUi(this);
    ground.addFlatGround(0,780,800,20);
    pe=new people(1,p,this,QVector2D{20,730});
    ground.addFlatGround(0,700,100,20);
    ground.addFlatGround(600,740,200,200);
    ground.addFlatGround(680,660,200,100);
    ground.addFlatGround(300,620,260,20);
    ground.addFlatGround(0,560,240,80);
    ground.addFlatGround(50,420,300,40);
    ground.addFlatGround(440,500,360,20);
    ground.addFlatGround(510,360,240,40);
    ground.addFlatGround(220,240,160,60);
    ground.addFlatGround(0,270,220,40);
    ground.addFlatGround(0,150,60,120);
    ground.addFlatGround(220,140,580,40);
    ground.addSlope(600,740,660,680);
    ground.addSlope(240,560,300,620);
    ground.addSlope(340,410,440,510);
    ground.addSlope(380,240,500,360);
    ground.addSlope(130,150,160,120);
    ground.addSlope(180,100,220,140);
    pl=new people(2,p,this,QVector2D{0,650});
    Stone* stone1 = new Stone(300, 180, 50, 50);
    stones.append(stone1);
    QRect q1(190,510,50,50),q2(190,370,50,50);
    triggerAreas.append(q1);
    triggerAreas.append(q2);
    Mechanism* m=new Mechanism(1,0,550,50,20,triggerAreas,0,420);
    mechanisms.append(m);
    triggerAreas.clear();
    QRect q3(600,450,50,50),q4(600,310,50,50);
    triggerAreas.append(q3);
    triggerAreas.append(q4);
    Mechanism* m1=new Mechanism(2,750,490,50,20,triggerAreas,750,360);
    mechanisms.append(m1);
    peopleList.append(pe);
    peopleList.append(pl);
    d1=new Door(1,700,90,50,50,this);
    d2=new Door(2,650,90,50,50,this);
    DeadWater river1(2,400,770,80,20,this);
    DeadWater river2(1,280,770,80,20,this);
    DeadWater river3(3,300,610,80,20,this);
    water.append(river1);
    water.append(river2);
    water.append(river3);
    player->setSource(QUrl::fromLocalFile("../../You - Approaching Nirvana.mp3"));
    player->play();
    id=1;
}

level1::~level1()
{
    delete ui;
}
