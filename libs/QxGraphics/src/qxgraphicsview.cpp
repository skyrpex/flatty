#include "qxgraphicsview.h"
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>
#include <cmath>
#include <math.h>
#include <QMessageBox>
#include <QxGraphicsViewController>


////////////////////////////////////////////////////////////////////////////////////////////////////
QxGraphicsView::QxGraphicsView(QWidget *parent) :
  QGraphicsView(parent),
  m_handDragEnabled(true),
  m_zoomingEnabled(true),
  m_handDragKey(Qt::Key_Alt),
  m_shadowColor(QColor(50, 50, 50)),
  m_sceneBrush(Qt::lightGray),
  m_scale(1.0),
  m_controller(NULL)
{
  this->setTransformationAnchor(AnchorUnderMouse);
  this->setBackgroundBrush(Qt::darkGray);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
QxGraphicsView::QxGraphicsView(QGraphicsScene *scene, QWidget *parent) :
  QGraphicsView(scene, parent),
//  Delegating constructors need C++0x
//  GraphicsView(parent),
  m_handDragEnabled(true),
  m_zoomingEnabled(true),
  m_handDragKey(Qt::Key_Alt),
  m_shadowColor(QColor(50, 50, 50)),
  m_sceneBrush(Qt::lightGray),
  m_scale(1.0),
  m_controller(NULL)
{
  this->setTransformationAnchor(AnchorUnderMouse);
  this->setBackgroundBrush(Qt::darkGray);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::installController(QxGraphicsViewController *controller)
{
  if(m_controller)
  {
    m_controller->uninstall();
    m_controller->m_view = NULL;
  }
  m_controller = controller;
  if(m_controller)
  {
    if(m_controller->installTo(this))
      m_controller->m_view = this;
    else
      qDebug() << "Error installing" << m_controller;
  }
  this->viewport()->update();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::uninstallController()
{
  if(m_controller)
  {
    m_controller->uninstall();
    m_controller->m_view = NULL;
  }
  this->viewport()->update();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::updateSceneRect(int margin)
{
  Q_ASSERT(this->scene());

  QRectF rect = this->scene()->itemsBoundingRect();
  rect.adjust(-margin, -margin, margin, margin);
  this->setSceneRect(rect);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::fitView()
{
  Q_ASSERT(this->scene());
  this->fitInView(this->sceneRect(), Qt::KeepAspectRatio);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
qreal QxGraphicsView::scale() const
{
  return this->matrix().m22();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool QxGraphicsView::handDragEnabled() const
{
  return m_handDragEnabled;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool QxGraphicsView::zoomingEnabled() const
{
  return m_zoomingEnabled;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::setScale(qreal scale)
{
  if(m_scale == scale)
    return;

  m_scale = scale;

  QMatrix matrix;
  matrix.scale(m_scale, m_scale);
  this->setMatrix(matrix);

  emit scaleChanged(m_scale);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::setHandDragEnabled(bool enable)
{
  m_handDragEnabled = enable;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::setZoomingEnabled(bool enable)
{
  m_zoomingEnabled = enable;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::setShadowColor(const QColor &color)
{
  m_shadowColor = color;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::setSceneBrush(const QBrush &brush)
{
  m_sceneBrush = brush;
}

QBrush QxGraphicsView::sceneBrush() const
{
  return m_sceneBrush;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::contextMenuEvent(QContextMenuEvent *event)
{
  if(m_controller)
    m_controller->contextMenuEvent(event);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::wheelEvent(QWheelEvent *event)
{
  if(m_controller && m_controller->wheelEvent(event))
    return;

  if(!m_zoomingEnabled)
    return;

  qreal scaleFactor = pow(2.0, event->delta() / 240.0);
  this->setScale(this->scale()*scaleFactor);

  event->accept();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
  if(m_controller && m_controller->mouseDoubleClickEvent(event))
    return;

  QGraphicsView::mouseDoubleClickEvent(event);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::mousePressEvent(QMouseEvent *event)
{
  if(m_controller && m_controller->mousePressEvent(event))
    return;

  QGraphicsView::mousePressEvent(event);
  if(event->isAccepted()) return;
  if(this->dragMode() == QGraphicsView::ScrollHandDrag)
    event->accept();
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
  if(m_controller && m_controller->mouseMoveEvent(event))
    return;
  QGraphicsView::mouseMoveEvent(event);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
  if(m_controller && m_controller->mouseReleaseEvent(event))
    return;
  QGraphicsView::mouseReleaseEvent(event);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::keyPressEvent(QKeyEvent *event)
{
  if(m_controller && m_controller->keyPressEvent(event))
    return;

  if(m_handDragEnabled && event->key() == m_handDragKey)
  {
    m_previousDragMode = this->dragMode();
    m_previousInteractiveMode = this->isInteractive();
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setInteractive(false);
    event->accept();
  }
  else
  {
    QGraphicsView::keyPressEvent(event);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
  if(m_controller && m_controller->keyReleaseEvent(event))
    return;

  if(event->key() == m_handDragKey)
  {
    this->setDragMode(m_previousDragMode);
    this->setInteractive(m_previousInteractiveMode);
    event->accept();
  }
  else
  {
    QGraphicsView::keyPressEvent(event);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::drawBackground(QPainter *painter, const QRectF &rect)
{
  QGraphicsView::drawBackground(painter, rect);

  // Set no pen
  painter->setPen(Qt::NoPen);

  // Usable scene rect
//  QRectF sceneRect = this->sceneRect().united(this->scene()->itemsBoundingRect());
  QRectF sceneRect = this->sceneRect();

  // Draw scene shadow
  this->drawBackgroundShadow(painter, sceneRect);

  // Draw scene rect
  painter->setBrush(m_sceneBrush);
  painter->drawRect(sceneRect);

  // Draw the controller
  if(m_controller)
    m_controller->drawBackground(painter, rect);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
  QGraphicsView::drawForeground(painter, rect);
  if(m_controller)
    m_controller->drawForeground(painter, rect);
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void QxGraphicsView::drawBackgroundShadow(QPainter *painter, const QRectF &rect)
{
  static const qreal ShadowRadius = 5.5;
  qreal scaledRadius = ShadowRadius/m_scale;
  QRectF shadowRect = rect.adjusted(-scaledRadius, -scaledRadius,
                                    scaledRadius, scaledRadius);

  // Top-left
  {
    QRectF r(shadowRect.topLeft(), rect.topLeft());
    QRadialGradient gradient(r.bottomRight(), scaledRadius);
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Bottom-left
  {
    QRectF r(rect.bottomLeft(), shadowRect.bottomLeft());
    r = r.normalized();
    QRadialGradient gradient(r.topRight(), scaledRadius);
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Top-right
  {
    QRectF r(rect.topRight(), shadowRect.topRight());
    r = r.normalized();
    QRadialGradient gradient(r.bottomLeft(), scaledRadius);
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Bottom-right
  {
    QRectF r(rect.bottomRight(), shadowRect.bottomRight());
    QRadialGradient gradient(r.topLeft(), scaledRadius);
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Top
  {
    QRectF r(rect.topLeft()+QPointF(0, -scaledRadius),
             rect.topRight());
    QLinearGradient gradient(r.bottomLeft(), r.topLeft());
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Right
  {
    QRectF r(rect.topRight(),
             rect.bottomRight()+QPointF(scaledRadius, 0));
    QLinearGradient gradient(r.topLeft(), r.topRight());
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Bottom
  {
    QRectF r(rect.bottomLeft(),
             rect.bottomRight()+QPointF(0, scaledRadius));
    QLinearGradient gradient(r.topLeft(), r.bottomLeft());
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }

  // Left
  {
    QRectF r(rect.topLeft()+QPointF(-scaledRadius, 0),
             rect.bottomLeft());
    QLinearGradient gradient(r.topRight(), r.topLeft());
    gradient.setColorAt(0, m_shadowColor);
    gradient.setColorAt(1, Qt::transparent);
    painter->setBrush(gradient);
    painter->drawRect(r);
  }
}



