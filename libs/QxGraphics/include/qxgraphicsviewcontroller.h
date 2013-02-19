#ifndef QXGRAPHICSVIEWCONTROLLER_H
#define QXGRAPHICSVIEWCONTROLLER_H

#include <qxgraphics_global.h>
#include <QObject>
#include <QxGraphicsView>
#include <QContextMenuEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>

class QXGRAPHICS_EXPORT QxGraphicsViewController : public QObject
{
  Q_OBJECT
public:
  QxGraphicsViewController(QObject *object = 0);

  QxGraphicsView *view() const;

  virtual void contextMenuEvent(QContextMenuEvent *event) {}
  virtual bool wheelEvent(QWheelEvent *event) {return false;}
  virtual bool mouseDoubleClickEvent(QMouseEvent *event) {return false;}
  virtual bool mousePressEvent(QMouseEvent *event) {return false;}
  virtual bool mouseMoveEvent(QMouseEvent *event) {return false;}
  virtual bool mouseReleaseEvent(QMouseEvent *event) {return false;}
  virtual bool keyPressEvent(QKeyEvent *event) {return false;}
  virtual bool keyReleaseEvent(QKeyEvent *event) {return false;}
  virtual void drawBackground(QPainter *painter, const QRectF &rect) {}
  virtual void drawForeground(QPainter *painter, const QRectF &rect) {}

protected:
  virtual bool installTo(QxGraphicsView *view) {return true;}
  virtual void uninstall() {}

private:
  friend class QxGraphicsView;

  QxGraphicsView *m_view;
};

#endif // QXGRAPHICSVIEWCONTROLLER_H
