#ifndef QXGRAPHICSVERTEXITEM_H
#define QXGRAPHICSVERTEXITEM_H

#include <qxgraphics_global.h>
#include <QObject>
#include <QGraphicsRectItem>

class QXGRAPHICS_EXPORT QxGraphicsVertexItem : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  QxGraphicsVertexItem();
  QxGraphicsVertexItem(const QPointF &pos);

  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

signals:
  void posChanged();
};

#endif // QXGRAPHICSVERTEXITEM_H
