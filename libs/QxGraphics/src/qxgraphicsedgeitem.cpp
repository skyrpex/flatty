#include "qxgraphicsedgeitem.h"

QxGraphicsEdgeItem::QxGraphicsEdgeItem(QxGraphicsVertexItem *v1, QxGraphicsVertexItem *v2) :
  m_v1(v1),
  m_v2(v2)
{
  Q_ASSERT(m_v1 and m_v2);
  connect(m_v1, SIGNAL(posChanged()), this, SLOT(updateLine()));
  connect(m_v2, SIGNAL(posChanged()), this, SLOT(updateLine()));
  connect(m_v1, SIGNAL(destroyed()), this, SLOT(deleteLater()));
  connect(m_v2, SIGNAL(destroyed()), this, SLOT(deleteLater()));
  this->updateLine();
  this->setZValue(-1);
}

QxGraphicsVertexItem *QxGraphicsEdgeItem::v1() const
{
  return m_v1;
}

QxGraphicsVertexItem *QxGraphicsEdgeItem::v2() const
{
  return m_v2;
}

void QxGraphicsEdgeItem::updateLine()
{
  this->setLine(QLineF(m_v1->pos(), m_v2->pos()));
}
