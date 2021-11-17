#include "animatedbackground.h"
#include <QPainter>

AnimatedBackground::AnimatedBackground(QGraphicsItem *parent): QGraphicsItem(parent) ,mCurrentFrame7() {

    setFlag(ItemClipsToShape);
    mPixmap7 = QPixmap(":images/dna-sprite2.png");
    //QTimer *timer = new QTimer(this);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));

    timer->start(100);
}

void AnimatedBackground::nextFrame(){
    mCurrentFrame7 += 110;
    if (mCurrentFrame7 >= 2310 ) {
        mCurrentFrame7 = 0;

    }
}

QRectF AnimatedBackground::boundingRect() const {

    return QRectF(0,0,130,165);
}

void AnimatedBackground::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap7, mCurrentFrame7, 0,105, 40);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int AnimatedBackground::type() const {

    return Type;
}

