#include "level2.h"
#include "ui_level2.h"
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
level2::level2(QWidget *parent)
    : Widget(parent)
    , ui(new Ui::level2)
{
    ui->setupUi(this);
    ground.addFlatGround(290,540,220,20);
    pe=new people(1,p,this,QVector2D{315,490});
    pl=new people(2,p,this,QVector2D{435,490});
    ground.addFlatGround(0,700,140,20);
    ground.addFlatGround(660,700,140,20);
    ground.addFlatGround(220,700,140,20);
    ground.addFlatGround(440,700,140,20);
    ground.addFlatGround(390,0,20,540);
    ground.addSlope(200,450,290,540);
    ground.addSlope(510,540,600,450);
    ground.addFlatGround(180,230,20,220);
    ground.addFlatGround(620,230,20,220);
    ground.addSlope(180,230,270,140);
    ground.addSlope(520,105,610,195);
    ground.addFlatGround(310,420,80,20);
    ground.addFlatGround(410,420,80,20);
    QRect q1(410,370,50,50),q(1000,500,50,50);
    triggerAreas.append(q1);
    triggerAreas.append(q);
    Mechanism* m1=new Mechanism(1,200,340,50,20,triggerAreas,200,280);
    triggerAreas.clear();
    ground.addFlatGround(330,220,60,20);
    ground.addFlatGround(410,220,60,20);
    QRect q2(340,170,50,50);
    triggerAreas.append(q2);
    triggerAreas.append(q);
    Mechanism* m2=new Mechanism(2,570,340,50,20,triggerAreas,570,280);
    ground.addFlatGround(0,270,50,20);
    ground.addFlatGround(120,360,60,20);
    ground.addFlatGround(0,440,60,20);
    ground.addFlatGround(120,520,60,20);
    ground.addFlatGround(0,600,60,20);
    ground.addFlatGround(80,640,20,20);


    ground.addFlatGround(750,270,50,20);
    ground.addFlatGround(680,360,60,20);
    ground.addFlatGround(750,440,60,20);
    ground.addFlatGround(680,520,60,20);
    ground.addFlatGround(750,600,60,20);
    ground.addFlatGround(720,640,20,20);



    mechanisms.append(m1);
    mechanisms.append(m2);
    peopleList.append(pe);
    peopleList.append(pl);
    d1=new Door(1,435,490,50,50,this);
    d2=new Door(2,315,490,50,50,this);
    DeadWater river3(3,0,780,800,20,this);
    water.append(river3);
    player->setSource(QUrl::fromLocalFile("../../chicken.mp3"));
    player->play();
    id=2;
}

level2::~level2()
{
    delete ui;
}
