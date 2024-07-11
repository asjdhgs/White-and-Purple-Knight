#ifndef DEAD_H
#define DEAD_H

#include <QWidget>
#include<QPainter>
#include<QPaintEvent>
class Widget;
namespace Ui {
class dead;
}

class dead : public QWidget
{
    Q_OBJECT

public:
    explicit dead(QWidget *parent = nullptr);
    ~dead();
    void paintEvent(QPaintEvent* event);
    int id=0;
    Widget*p=nullptr;
private slots:
    void on_onceagain_clicked();

    void on_return_2_clicked();

private:
    Ui::dead *ui;
};

#endif // DEAD_H
