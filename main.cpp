#include "widget.h"
#include"start.h"
#include"dead.h"
#include"choose.h"
#include <QApplication>
#include"win.h"
#include"stop.h"
stop* sp;
start* st;
choose* ch;
win* w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    st=new start;
    ch=new choose;
    w=new win;
    st->show();
    return a.exec();
}
