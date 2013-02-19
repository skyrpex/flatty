#ifndef QXGRAPHICSVIEW_H
#define QXGRAPHICSVIEW_H

#include <qxgraphics_global.h>
#include <QGraphicsView>

class QxGraphicsViewController;

/**
  * @class GraphicsEnhancedView
  * @brief Enhanced graphics view
  *
  * It is able to do nice things
  */
class QXGRAPHICS_EXPORT QxGraphicsView : public QGraphicsView
{
  Q_OBJECT
public:
  /**
    * @brief Default constructor
    * @param parent QWidget
    */
  explicit QxGraphicsView(QWidget *parent = 0);

  /**
    * @brief Constructor that takes a QGraphicsScene
    * @param scene  QGraphicsScene
    * @param parent QWidget
    */
  explicit QxGraphicsView(QGraphicsScene *scene, QWidget *parent = 0);

  /**
    */
  void installController(QxGraphicsViewController *controller);

  /**
    */
  void uninstallController();

  /**
    * @brief Fits the view into the current scene rect keeping the aspect ratio
    */
  void fitView();

  /**
    * @brief This property holds the view scale ratio
    * @return The view scale ratio
    */
  qreal scale() const;

  /**
    * @brief Tell wether or not the hand drag is enabled
    * @return True if hand drag is enabled, false otherwise
    */
  bool handDragEnabled() const;

  /**
    * @brief Tell wether or not the zooming is enabled
    * @return True if zooming is enabled, false otherwise
    */
  bool zoomingEnabled() const;

public slots:
  /**
    * @brief Sets the scale of the view
    * @param scale The scale ratio to be applied to the view
    */
  void setScale(qreal scale);

  /**
    * @brief Sets whether hand drag should be enabled or not.
    *
    * If hand drag is enabled, the user can move the view with the mouse.
    *
    * @param enable Enables or disables the hand drag
    */
  void setHandDragEnabled(bool enable);

  /**
    * @brief Sets whether zooming should be enabled or not.
    *
    * If zooming is enabled, the user can zoom in/out with the mouse wheel.
    *
    * @param enable Enables or disables the zooming
    */
  void setZoomingEnabled(bool enable);

  /**
    * @brief Sets the shadow color.
    * @param color Color of the shadow
    */
  void setShadowColor(const QColor &color);

  /**
    * @brief Sets the scene brush.
    * @param QBrush Brush that will be used to draw the scene rect
    */
  void setSceneBrush(const QBrush &brush);

  /**
    */
  QBrush sceneBrush() const;

  /**
    * @brief Sets the current scene rect to fit the items bounding box and applies a margin
    * @param margin Margin to be applied to the items bouding box
    */
  void updateSceneRect(int margin = 0);

signals:
  /**
    * @brief This property holds the scale of the view
    */
  void scaleChanged(qreal scale);

protected:
  /**
    * @brief Reimplemented from QGraphicsView::contextMenuEvent()
    */
  virtual void contextMenuEvent(QContextMenuEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::mouseDoubleClickEvent()
    */
  virtual void mouseDoubleClickEvent(QMouseEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::mousePressEvent()
    */
  virtual void mousePressEvent(QMouseEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::mouseMoveEvent()
    */
  virtual void mouseMoveEvent(QMouseEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::mouseReleaseEvent()
    */
  virtual void mouseReleaseEvent(QMouseEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::wheelEvent()
    */
  virtual void wheelEvent(QWheelEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::keyPressEvent()
    */
  virtual void keyPressEvent(QKeyEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::keyReleaseEvent()
    */
  virtual void keyReleaseEvent(QKeyEvent *event);

  /**
    * @brief Reimplemented from QGraphicsView::drawBackground()
    */
  virtual void drawBackground(QPainter *painter, const QRectF &rect);

  /**
    * @brief Reimplemented from QGraphicsView::drawForeground()
    */
  virtual void drawForeground(QPainter *painter, const QRectF &rect);

private:
  /**
    * @brief Draws a smooth shadow around a rect
    * @param painter  Paint device to draw the shadow on
    * @param rect     Rect that will be wrapped by the shadow
    */
  void drawBackgroundShadow(QPainter *painter, const QRectF &rect);

  bool m_handDragEnabled;         ///< Is hand drag enabled?
  bool m_zoomingEnabled;          ///< Is zooming enabled?
  Qt::Key m_handDragKey;          ///< Hand drag activation key (Key_Alt by default)
  DragMode m_previousDragMode;    ///< Holds the previous drag mode
  bool m_previousInteractiveMode; ///< Is the previous interactive mode enabled?

  QColor m_shadowColor;           ///< Holds the shadow color
  QBrush m_sceneBrush;            ///< Holds the scene brush

  qreal m_scale;                  ///< Holds the view scale

  QxGraphicsViewController *m_controller; ///< Current installed controller
};

#endif // QXGRAPHICSVIEW_H
