#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>
#include"widget.h"
class Widget;
namespace Ui {
class level1;
}

class level1 : public Widget
{
    Q_OBJECT

public:
    explicit level1(QWidget *parent = nullptr);
    ~level1();

private:
    Ui::level1 *ui;
};

#endif // LEVEL1_H
