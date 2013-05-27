#ifndef ANIM_H
#define ANIM_H

#include <QString>
#include <QMetaType>
#include <QMap>

class AnimModel;
class Anim;
class KeyFrames;
class Joint;

class Anim
{
public:
    Anim(const QString &name, int frameCount, int fps);
    ~Anim();

    QString name() const;
    void setName(const QString &name);

    int frameCount() const;
    void setFrameCount(int frameCount);

    int fps() const;
    void setFps(int fps);

private:
    friend class AnimModel;
    friend class JointModel;

    AnimModel *m_model;
    QString m_name;
    int m_frameCount;
    int m_fps;
    QMap<Joint *, KeyFrames *> m_keyFrames;
};

Q_DECLARE_METATYPE(Anim*)

#endif // ANIM_H
