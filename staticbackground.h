#ifndef STATICBACKGROUND_H
#define STATICBACKGROUND_H

#include <QGraphicsPixmapItem>

class StaticBackground : public QGraphicsPixmapItem
{
public:
    explicit StaticBackground(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};

#endif // STATICBACKGROUND_H
