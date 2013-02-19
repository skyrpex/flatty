#include <QxGraphicsViewController>

QxGraphicsViewController::QxGraphicsViewController(QObject *object)
  : QObject(object),
    m_view(NULL)
{
}

QxGraphicsView *QxGraphicsViewController::view() const
{
  return m_view;
}
