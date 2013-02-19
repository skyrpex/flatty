#include "qxgraphicslineitem.h"
#include <QBrush>
#include <QGraphicsSceneContextMenuEvent>
#include <QPainter>
#include <QMenu>
#include <QCursor>
#include <QDebug>

////////////////////////////////////////////////////////////////////////////////////////////////////
static const qreal MinSplitDistance = 4.0;

////////////////////////////////////////////////////////////////////////////////////////////////////
QxGraphicsLineItem::QxGraphicsLineItem(QGraphicsItem *parent) :
  QGraphicsLineItem(parent)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
QxGraphicsLineItem::QxGraphicsLineItem(const QLineF &line,
                                       QGraphicsItem *parent) :
  QGraphicsLineItem(line, parent)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
QxGraphicsLineItem::QxGraphicsLineItem(qreal x1, qreal y1,
                                       qreal x2, qreal y2,
                                       QGraphicsItem *parent) :
  QGraphicsLineItem(x1, y1, x2, y2, parent)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
QRectF QxGraphicsLineItem::boundingRect() const
{
  return QRectF(this->line().p1(), this->line().p2())
      .normalized()
      .adjusted(-MinSplitDistance, -MinSplitDistance,
                MinSplitDistance, MinSplitDistance);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool QxGraphicsLineItem::collidesWithPath(const QPainterPath &path,
                                        Qt::ItemSelectionMode mode) const
{
  return this->contains(path.currentPosition());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool QxGraphicsLineItem::contains(const QPointF &point) const
{
  return this->distanceTo(point) < MinSplitDistance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
QPointF QxGraphicsLineItem::nearestPoint(const QPointF &point) const
{
  if(this->line().isNull()) return this->line().p1();

  qreal x1 = this->line().p1().x();
  qreal x2 = this->line().p2().x();
  qreal x3 = point.x();
  qreal y1 = this->line().p1().y();
  qreal y2 = this->line().p2().y();
  qreal y3 = point.y();

  qreal x31 = x3 - x1;
  qreal x21 = x2 - x1;
  qreal y31 = y3 - y1;
  qreal y21 = y2 - y1;
  qreal len = this->line().length();
  qreal u = (x31*x21 + y31*y21) / (len*len);

  return this->line().pointAt(qMax(qMin(u, 1.0), 0.0));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
qreal QxGraphicsLineItem::distanceTo(const QPointF &point) const
{
  return QLineF(point, this->nearestPoint(point)).length();
}
