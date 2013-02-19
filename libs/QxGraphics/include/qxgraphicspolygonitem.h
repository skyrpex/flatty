#ifndef QXGRAPHICSPOLYGONITEM_H
#define QXGRAPHICSPOLYGONITEM_H

#include <qxgraphics_global.h>
#include <QGraphicsItemGroup>
#include <QPolygonF>
#include <QObject>
#include <QxGraphicsVertexItem>
#include <QxGraphicsEdgeItem>

class QXGRAPHICS_EXPORT QxGraphicsPolygonItem : public QObject, public QGraphicsItemGroup
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
public:
  QxGraphicsPolygonItem();
  QxGraphicsPolygonItem(const QPolygonF &polygon);

  void setPolygon(const QPolygonF &polygon);

  bool splitEdge(QxGraphicsEdgeItem *edge, const QPointF &pos);

  QPolygonF polygon() const;
  bool isClosed() const;
  bool isEmpty() const;

  void addVertex(QxGraphicsVertexItem *vertex);
  bool removeVertex(QxGraphicsVertexItem *vertex);
  void close();

//  void updateBoundaryEdges();

  QList<QxGraphicsVertexItem*> vertices() const;

public slots:
  void setBoundaryVerticesVisible(bool visible);

private:
  void clear();
  void clearEdges();

  QxGraphicsEdgeItem *createEdge(QxGraphicsVertexItem *v1, QxGraphicsVertexItem *v2);
  QxGraphicsEdgeItem *findEdge1(QxGraphicsVertexItem *v);
  QxGraphicsEdgeItem *findEdge2(QxGraphicsVertexItem *v);

  QList<QxGraphicsVertexItem*> m_boundary;
  QList<QxGraphicsEdgeItem*> m_edges;
  bool m_closed;
  bool m_boundaryVisible;
};

#endif // QXGRAPHICSPOLYGONITEM_H
