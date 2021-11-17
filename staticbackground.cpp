#include "staticbackground.h"

StaticBackground::StaticBackground(const QPixmap &pixmap, QGraphicsItem * parent): QGraphicsPixmapItem(pixmap, parent){
}

QPainterPath StaticBackground::shape() const
{
    return QPainterPath();
}
