#ifndef CHOOSE_H
#define CHOOSE_H

#include <QWidget>
class Widget;
namespace Ui {
class choose;
}

class choose : public QWidget
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();
    void paintEvent(QPaintEvent* event);
    Widget*w=nullptr;

private slots:
    void on_first_clicked();

    void on_second_clicked();

    void on_third_clicked();

    void on_return_2_clicked();

private:
    Ui::choose *ui;
};

#endif // CHOOSE_H
