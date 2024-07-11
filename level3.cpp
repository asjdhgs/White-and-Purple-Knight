#include "level3.h"
#include "ui_level3.h"
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
level3::level3(QWidget *parent)
    : Widget(parent)
    , ui(new Ui::level3)
{
    ui->setupUi(this);
    pe=new people(1,p,this,QVector2D{20,730});
    pl=new people(2,p,this,QVector2D{730,730});
    peopleList.append(pe);
    peopleList.append(pl);
    ground.addFlatGround(0,780,800,20);
    ground.addFlatGround(380,300,40,500);
    ground.addFlatGround(160,700,220,20);
    ground.addFlatGround(580,600,220,60);
    ground.addFlatGround(700,520,20,20);
    ground.addFlatGround(180,460,400,20);
    ground.addFlatGround(220,180,20,280);
    ground.addFlatGround(540,180,20,280);
    ground.addFlatGround(200,300,110,20);
    ground.addFlatGround(480,300,120,20);
    ground.addFlatGround(0,380,80,20);
    ground.addFlatGround(700,380,100,20);
    ground.addFlatGround(0,220,100,20);
    ground.addFlatGround(700,220,100,20);
    QRect q1(320,650,50,50),q2(800,800,50,50);
    triggerAreas.append(q1);
    triggerAreas.append(q2);
    Mechanism* m=new Mechanism(1,420,780,50,20,triggerAreas,420,680);
    mechanisms.append(m);
    triggerAreas.clear();
    QRect q3(590,550,50,50);
    triggerAreas.append(q3);
    triggerAreas.append(q2);
    Mechanism* m1=new Mechanism(2,0,630,50,20,triggerAreas,0,530);
    mechanisms.append(m1);
    triggerAreas.clear();
    QRect q5(20,170,50,50);
    triggerAreas.append(q5);
    triggerAreas.append(q2);
    Mechanism* m2=new Mechanism(3,420,300,50,20,triggerAreas,420,100);
    mechanisms.append(m2);
    triggerAreas.clear();
    QRect q7(410,410,50,50);
    triggerAreas.append(q7);
    triggerAreas.append(q2);
    Mechanism* m3=new Mechanism(1,320,300,50,20,triggerAreas,420,100);
    mechanisms.append(m3);
    Stone* stone1 = new Stone(800, 800, 50, 50);
    stones.append(stone1);
    DeadWater river3(3,800,800,80,20,this);
    water.append(river3);
    d1=new Door(1,300,410,50,50,this);
    d2=new Door(2,480,410,50,50,this);
    player->setSource(QUrl::fromLocalFile("../../gangtiejinxingqu.mp3"));
    player->play();
    id=3;
}

level3::~level3()
{
    delete ui;
}
