#include <QApplication>
#include <QxGraphicsView>
#include <QxGraphicsViewController>
#include <QxGraphicsPolygonItem>

class Controller : public QxGraphicsViewController
{
public:
//  void drawForeground(QGraphicsView *view, QPainter *painter, const QRectF &rect)
//  {
//    painter->setOpacity(0.5);
//    painter->fillRect(rect, Qt::red);
//  }
};

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QxGraphicsView view;
  QGraphicsScene scene;
  QxGraphicsPolygonItem item;

  view.setRenderHint(QPainter::Antialiasing);
  view.installController(new Controller);
  view.setScene(&scene);
  view.setSceneRect(-320, -240, 640, 480);

  scene.addItem(&item);

  QPolygonF polygon;
  polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(50, 100);
  item.setPolygon(polygon);

  view.show();
  return app.exec();
}
