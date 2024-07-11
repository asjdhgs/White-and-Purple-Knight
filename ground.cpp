#include "ground.h"

Ground::Ground() {}

void Ground::updatePosition(qreal dx, qreal dy)
{
    for (int i = 0; i < groundPolygons.size(); ++i)
    {
        if (groundPolygons[i].canConvert<QRectF>())
        {
            QRectF rect = groundPolygons[i].toRectF();
            rect.translate(dx, dy);
            groundPolygons[i] = rect;
        }
        else if (groundPolygons[i].canConvert<QLineF>())
        {
            QLineF line = groundPolygons[i].toLineF();
            line.translate(dx, dy);
            groundPolygons[i] = line;
        }
    }
}
