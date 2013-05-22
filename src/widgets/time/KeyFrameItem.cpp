#include "KeyFrameItem.h"
#include "KeyFrameMime.h"
#include "Constants.h"
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QWidget>
#include <QDebug>

KeyFrameItem::KeyFrameItem(qreal x)
{
    setPixmap(QPixmap(KeyFramePixmap));
    setCacheMode(DeviceCoordinateCache);
    setAcceptedMouseButtons(Qt::LeftButton);
    setPos(x, 0);
}

void KeyFrameItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);
    QDrag *drag = new QDrag(event->widget());
    drag->setMimeData(new KeyFrameMime(this));
    drag->exec();
}
