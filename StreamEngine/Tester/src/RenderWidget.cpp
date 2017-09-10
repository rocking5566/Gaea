#include "RenderWidget.h"

#include <QPainter>
#include <QPaintEvent>

CRenderWidget::CRenderWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{}

void CRenderWidget::Render(const CImageAdaptor &frame)
{
    QMutexLocker lock(&m_frameMutex);
    m_currentFrame = frame;
    update();
}

void CRenderWidget::paintEvent(QPaintEvent *ev)
{
    QOpenGLWidget::paintEvent(ev);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    QRect targetRect(0, 0, width(), height());

    QMutexLocker lock(&m_frameMutex);

    QRect srcRect(0, 0, m_currentFrame.Width(), m_currentFrame.Height());
    painter.drawImage(targetRect, m_currentFrame.ToQImage(), srcRect);
}
