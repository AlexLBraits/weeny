#include "view.h"
#include <application.h>
#include <QDateTime>

PlatformView::PlatformView(Application* app)
    : QGLWidget(), _q(app)
{
    startTimer(16);
    setWindowTitle(PROJECT_NAME);
}

void PlatformView::initializeGL()
{
}

void PlatformView::resizeGL(int width, int height)
{
    _q->resize(width, height);
}

void PlatformView::paintGL()
{
    _q->draw();
}

bool PlatformView::event(QEvent* event)
{
    return QGLWidget::event(event);
}

void PlatformView::timerEvent(QTimerEvent *event)
{
    _q->update();
    updateGL();
}
