#ifndef START_H
#define START_H

#include <QWidget>
#include<QPainter>
#include<QPaintEvent>
#include"widget.h"
namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(QWidget *parent = nullptr);
    ~start();
    void paintEvent(QPaintEvent* event);
    void ifshow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::start *ui;
signals:
    void ifstart();
};

#endif // START_H
