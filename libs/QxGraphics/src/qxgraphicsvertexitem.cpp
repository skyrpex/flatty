#include "qxgraphicsvertexitem.h"
#include <QBrush>
#include <QPen>
#include <QDebug>

static const qreal VertexWidth = 5;

QxGraphicsVertexItem::QxGraphicsVertexItem() :
  QGraphicsRectItem(-VertexWidth/2, -VertexWidth/2, VertexWidth, VertexWidth)
{
  this->setFlags(ItemIsMovable |
                 ItemIgnoresTransformations |
                 ItemSendsScenePositionChanges);
  this->setCacheMode(DeviceCoordinateCache);
  this->setPen(Qt::NoPen);
  this->setBrush(Qt::black);
}

QxGraphicsVertexItem::QxGraphicsVertexItem(const QPointF &pos) :
  QGraphicsRectItem(-VertexWidth/2, -VertexWidth/2, VertexWidth, VertexWidth)
{
  this->setFlags(ItemIsMovable |
                 ItemIgnoresTransformations |
                 ItemSendsScenePositionChanges);
  this->setCacheMode(DeviceCoordinateCache);
  this->setPen(Qt::NoPen);
  this->setBrush(Qt::black);
  this->setPos(pos);
}

QVariant QxGraphicsVertexItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
  switch(change)
  {
  case ItemPositionHasChanged:
    emit posChanged();
    break;

  default:
    break;
  }

  return QGraphicsRectItem::itemChange(change, value);
}
