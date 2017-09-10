#ifndef RenderWidget_h__
#define RenderWidget_h__

#include <QOpenGLWidget>
#include <QMutex>
#include "VideoFrame.h"

class CRenderWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    CRenderWidget(QWidget *parent = 0);
    void Render(const CVideoFrame &frame);
    CVideoFrame currentFrame();

private:
    virtual void paintEvent(QPaintEvent *ev);

private:
    CVideoFrame m_currentFrame;
    QMutex m_frameMutex;
};
#endif // RenderWidget_h__