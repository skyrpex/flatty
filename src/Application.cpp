#include "Application.h"
#include <QStyleFactory>
#include <QPalette>

Application::Application(int argc, char **argv) :
    QApplication(argc, argv),
    m_undoStack(new QUndoStack(this))
{
    setOrganizationName("VGAFIB");
    setApplicationName("Flatty");
    setApplicationVersion("0.0");

    setStyle(QStyleFactory::create("fusion"));

//    QPalette palette;
//    palette.setColor(QPalette::Window, QColor(53,53,53));
//    palette.setColor(QPalette::WindowText, Qt::white);
//    palette.setColor(QPalette::Base, QColor(15,15,15));
//    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
//    palette.setColor(QPalette::ToolTipBase, Qt::white);
//    palette.setColor(QPalette::ToolTipText, Qt::white);
//    palette.setColor(QPalette::Text, Qt::white);
//    palette.setColor(QPalette::Button, QColor(53,53,53));
//    palette.setColor(QPalette::ButtonText, Qt::white);
//    palette.setColor(QPalette::BrightText, Qt::red);

//    palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
//    palette.setColor(QPalette::HighlightedText, Qt::black);
//    setPalette(palette);
}

QUndoStack *Application::undoStack()
{
    return m_undoStack;
}
