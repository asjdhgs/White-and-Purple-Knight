#ifndef LEVEL3_H
#define LEVEL3_H

#include <QWidget>
#include"widget.h"
namespace Ui {
class level3;
}

class level3 : public Widget
{
    Q_OBJECT

public:
    explicit level3(QWidget *parent = nullptr);
    ~level3();

private:
    Ui::level3 *ui;
};

#endif // LEVEL3_H
