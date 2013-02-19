#ifndef QXGRAPHICSLINEITEM_H
#define QXGRAPHICSLINEITEM_H

#include <qxgraphics_global.h>
#include <QGraphicsLineItem>

class QXGRAPHICS_EXPORT QxGraphicsLineItem : public QGraphicsLineItem
{
public:
  QxGraphicsLineItem(QGraphicsItem *parent = 0);
  QxGraphicsLineItem(const QLineF &line, QGraphicsItem *parent = 0);
  QxGraphicsLineItem(qreal x1, qreal y1,
                     qreal x2, qreal y2,
                     QGraphicsItem *parent = 0);

  QRectF  boundingRect() const;
  bool    collidesWithPath(const QPainterPath &path, Qt::ItemSelectionMode mode) const;
  bool    contains(const QPointF &point) const;
  QPointF nearestPoint(const QPointF &point) const;
  qreal   distanceTo(const QPointF &point) const;
};

#endif // QXGRAPHICSLINEITEM_H
