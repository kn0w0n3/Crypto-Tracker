#ifndef ANIMATEDBACKGROUND_H
#define ANIMATEDBACKGROUND_H


#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>


class AnimatedBackground : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum { Type = UserType + 1};
    AnimatedBackground(QGraphicsItem *parent = 0);

    //void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    QTimer *timer;

public slots:
     void nextFrame();

private:

    int mCurrentFrame7;
    QPixmap mPixmap7;
    //QTimer *timer;

};

#endif // ANIMATEDBACKGROUND_H
