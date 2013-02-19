#include <QApplication>
#include <QSplitter>
#include <QScrollBar>
#include <QxGraphicsView>
#include <QxGraphicsPolygonItem>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QGraphicsScene scene;

  QxGraphicsPolygonItem item;
  scene.addItem(&item);
  QPolygonF polygon;
  polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(50, 100);
  item.setPolygon(polygon);

  QxGraphicsView *view[2] = {
    new QxGraphicsView(&scene),
    new QxGraphicsView(&scene)
  };
  view[0]->setRenderHint(QPainter::Antialiasing);
  view[0]->setSceneRect(-320, -240, 640, 480);
  view[1]->setRenderHint(QPainter::Antialiasing);
  view[1]->setSceneRect(-320, -240, 640, 480);
  QObject::connect(view[0]->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                   view[1]->horizontalScrollBar(), SLOT(setValue(int)));
  QObject::connect(view[1]->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                   view[0]->horizontalScrollBar(), SLOT(setValue(int)));
  QObject::connect(view[0]->verticalScrollBar(), SIGNAL(valueChanged(int)),
                   view[1]->verticalScrollBar(), SLOT(setValue(int)));
  QObject::connect(view[1]->verticalScrollBar(), SIGNAL(valueChanged(int)),
                   view[0]->verticalScrollBar(), SLOT(setValue(int)));
  QObject::connect(view[0], SIGNAL(scaleChanged(qreal)),
                   view[1], SLOT(setScale(qreal)));
  QObject::connect(view[1], SIGNAL(scaleChanged(qreal)),
                   view[0], SLOT(setScale(qreal)));

  QSplitter splitter;
  splitter.addWidget(view[0]);
  splitter.addWidget(view[1]);

  splitter.show();
  return app.exec();
}
