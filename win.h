#ifndef WIN_H
#define WIN_H

#include <QWidget>
#include<QPainter>
namespace Ui {
class win;
}

class win : public QWidget
{
    Q_OBJECT

public:
    explicit win(QWidget *parent = nullptr);
    ~win();
    QMovie* mov;
    void paintEvent(QPaintEvent* event);
    QPixmap picture;
private slots:
    void on_return_2_clicked();

private:
    Ui::win *ui;
};

#endif // WIN_H
