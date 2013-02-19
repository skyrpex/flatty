#include "qxgraphicspolygonitem.h"
#include "qxgraphicsvertexitem.h"
#include "qxgraphicsedgeitem.h"
#include <QDebug>

QxGraphicsPolygonItem::QxGraphicsPolygonItem() :
  m_closed(false),
  m_boundaryVisible(true)
{
  this->setHandlesChildEvents(false);
}

QxGraphicsPolygonItem::QxGraphicsPolygonItem(const QPolygonF &polygon) :
  m_closed(false),
  m_boundaryVisible(true)
{
  this->setHandlesChildEvents(false);
  this->setPolygon(polygon);
}

void QxGraphicsPolygonItem::setPolygon(const QPolygonF &polygon)
{
  this->clear();
  foreach(const QPointF &point, polygon)
    this->addVertex(new QxGraphicsVertexItem(point));
  this->close();
}

bool QxGraphicsPolygonItem::splitEdge(QxGraphicsEdgeItem *edge, const QPointF &pos)
{
  if(!m_edges.contains(edge)) return false;

  QxGraphicsVertexItem *v1 = edge->v1();
  QxGraphicsVertexItem *v2 = edge->v2();

  QxGraphicsVertexItem *v = new QxGraphicsVertexItem;
  v->setVisible(m_boundaryVisible);
  v->setPos(pos);
  this->addToGroup(v);
  int i = m_boundary.indexOf(v2);
  m_boundary.insert(i, v);

  // Delete old edge
  m_edges.removeAll(edge);
  delete edge;

  // Connect v1 to v
  this->createEdge(v1, v);

  // Connect v to v2
  this->createEdge(v, v2);

  return true;
}

void QxGraphicsPolygonItem::clearEdges()
{
  qDeleteAll(m_edges);
  m_edges.clear();
}

void QxGraphicsPolygonItem::clear()
{
  this->clearEdges();
  qDeleteAll(m_boundary);
  m_boundary.clear();
  m_closed = false;
}

QPolygonF QxGraphicsPolygonItem::polygon() const
{
  QPolygonF polygon;
  foreach(QxGraphicsVertexItem *vertex, m_boundary)
  {
    polygon << vertex->pos();
  }
  return polygon;
}

bool QxGraphicsPolygonItem::isClosed() const
{
  return m_closed;
}

bool QxGraphicsPolygonItem::isEmpty() const
{
  return m_boundary.isEmpty();
}

void QxGraphicsPolygonItem::addVertex(QxGraphicsVertexItem *vertex)
{
  QxGraphicsVertexItem *lastVertex = m_boundary.isEmpty()?
    NULL :
    m_boundary.last();

  vertex->setVisible(m_boundaryVisible);
  this->addToGroup(vertex);
  m_boundary << vertex;

  if(!lastVertex) return;
  this->createEdge(lastVertex, vertex);
}

bool QxGraphicsPolygonItem::removeVertex(QxGraphicsVertexItem *vertex)
{
  if(m_boundary.contains(vertex))
  {
    // If it's actually a triangle, just clear the boundary
    if(m_boundary.count() < 4)
    {
      this->clear();
      return true;
    }

    QxGraphicsEdgeItem *e1 = this->findEdge2(vertex);
    QxGraphicsEdgeItem *e2 = this->findEdge1(vertex);
    Q_ASSERT(e1 and e2);

    QxGraphicsVertexItem *a = e1->v1();
    QxGraphicsVertexItem *c = e2->v2();

    m_edges.removeAll(e1);
    m_edges.removeAll(e2);

    m_boundary.removeAll(vertex);
    delete vertex;

    this->createEdge(a, c);

    return true;
  }
  return false;
}

void QxGraphicsPolygonItem::close()
{
  if(m_boundary.count() < 2) return;
  m_closed = true;
  this->createEdge(m_boundary.last(), m_boundary.first());
}

QList<QxGraphicsVertexItem *> QxGraphicsPolygonItem::vertices() const
{
  return m_boundary;
}


//void QxGraphicsPolygonItem::updateBoundaryEdges()
//{
//  this->clearBoundaryEdges();

//  QxGraphicsVertexItem *v1 = NULL;
//  foreach(QxGraphicsVertexItem *v2, m_boundary)
//  {
//    if(v1 != NULL)
//    {
//      this->createEdge(v1, v2);
//    }
//    v1 = v2;
//  }

//  if(m_boundary.count() >= 2)
//  {
//    this->createEdge(m_boundary.last(), m_boundary.first());
//  }
//}

void QxGraphicsPolygonItem::setBoundaryVerticesVisible(bool visible)
{
  m_boundaryVisible = visible;
  foreach(QxGraphicsVertexItem *vertex, m_boundary)
  {
    vertex->setVisible(visible);
  }
}

QxGraphicsEdgeItem *QxGraphicsPolygonItem::createEdge(QxGraphicsVertexItem *v1, QxGraphicsVertexItem *v2)
{
  QxGraphicsEdgeItem *edge = new QxGraphicsEdgeItem(v1, v2);
  edge->setZValue(-1);
  this->addToGroup(edge);
  m_edges << edge;
  return edge;
}

QxGraphicsEdgeItem *QxGraphicsPolygonItem::findEdge1(QxGraphicsVertexItem *v)
{
  foreach(QxGraphicsEdgeItem *edge, m_edges)
  {
    if(edge->v1() == v) return edge;
  }
  return NULL;
}

QxGraphicsEdgeItem *QxGraphicsPolygonItem::findEdge2(QxGraphicsVertexItem *v)
{
  foreach(QxGraphicsEdgeItem *edge, m_edges)
  {
    if(edge->v2() == v) return edge;
  }
  return NULL;
}
