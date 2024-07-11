#ifndef STOP_H
#define STOP_H

#include <QWidget>
class Widget;
namespace Ui {
class stop;
}

class stop : public QWidget
{
    Q_OBJECT

public:
    explicit stop(Widget*p,QWidget *parent = nullptr);
    ~stop();
    Widget* w;
    void paintEvent(QPaintEvent* event);
    QPixmap picture;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::stop *ui;
};

#endif // STOP_H
