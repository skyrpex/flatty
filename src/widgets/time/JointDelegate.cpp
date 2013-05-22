#include "JointDelegate.h"
#include "model/Anim.h"
#include "model/JointModel.h"
#include "model/KeyFrames.h"
#include "KeyFramesEditor.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPainter>

static const QSize MinimumSizeHint(0, 20);
static const QPen LinePeN(QColor(250, 0, 0), 1);
static const int LineOffset = 3;

JointDelegate::JointDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    m_currentFrame(0)
{
}

QWidget *JointDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<KeyFrames *>())
    {
        KeyFramesEditor *editor = new KeyFramesEditor(parent);
        connect(editor, SIGNAL(currentFrameChanged(int)), SLOT(setCurrentFrame(int)));
        connect(this, SIGNAL(currentFrameChanged(int)), editor, SLOT(setCurrentFrame(int)));
        return editor;
    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void JointDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().canConvert<KeyFrames *>())
    {
        Anim *anim = index.data(JointModel::AnimRole).value<Anim *>();
        KeyFrames *keyFrames = index.data().value<KeyFrames *>();
        KeyFramesEditor *keyFramesEditor = qobject_cast<KeyFramesEditor *>(editor);
        Q_ASSERT(anim);
        Q_ASSERT(keyFramesEditor);
        Q_ASSERT(keyFrames);
        keyFramesEditor->setData(keyFrames->data, anim->frameCount(), m_currentFrame);
    }
    else
        QStyledItemDelegate::setEditorData(editor, index);
}

void JointDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.data().canConvert<KeyFrames *>()) {
        Anim *anim = index.data(JointModel::AnimRole).value<Anim *>();
        KeyFrames *keyFrames = index.data().value<KeyFrames *>();
        KeyFramesEditor editor;
        editor.setData(keyFrames->data, anim->frameCount(), m_currentFrame);

        QRectF target = option.rect;
        QRect source = option.rect.translated( -option.rect.topLeft() );
        editor.render(painter, target, source);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

QSize JointDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size(8, 20) /*= AnimEditor::frameSize()*/;
    if(index.data().canConvert<KeyFrames *>())
    {
        Anim *anim = index.data(JointModel::AnimRole).value<Anim *>();
        if(anim)
            size.rwidth() *= anim->frameCount();
    }

    return QStyledItemDelegate::sizeHint(option, index).expandedTo(size);
}

void JointDelegate::setCurrentFrame(int frame)
{
    if(m_currentFrame != frame)
    {
        m_currentFrame = frame;
        emit currentFrameChanged(frame);
    }
}
