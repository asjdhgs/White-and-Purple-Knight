#ifndef GROUND_H
#define GROUND_H

#include <QPolygonF>
#include <QLineF>
#include <QVector>
#include <QRectF>
#include <QVariant>

class Ground
{
public:
    Ground();

    // 添加平坦地面，使用 QRectF 表示
    // x, y 表示左上角的坐标
    // width, height 表示宽度和高度
    void addFlatGround(qreal x, qreal y, qreal width, qreal height) {
        groundPolygons.append(QRectF(x, y, width, height));
    }

    // 添加竖直墙面，使用 QLineF 表示
    // x 表示墙面的横坐标
    // y1 表示墙面顶部的纵坐标
    // y2 表示墙面底部的纵坐标
    void addVerticalWall(qreal x, qreal y1, qreal y2) {
        groundPolygons.append(QLineF(x, y1, x, y2));
    }


    // 添加斜坡，使用 QLineF 表示
    // x1, y1 表示起点坐标
    // x2, y2 表示终点坐标
    void addSlope(qreal x1, qreal y1, qreal x2, qreal y2) {
        groundPolygons.append(QLineF(x1, y1, x2, y2));
    }

    // 返回所有地形元素的列表
    const QVector<QVariant>& getGroundPolygons() const {
        return groundPolygons;
    }
    void updatePosition(qreal dx, qreal dy);

private:
    QVector<QVariant> groundPolygons; // 存储地形元素的列表，可以是 QRectF 或 QLineF
};

#endif // GROUND_H
