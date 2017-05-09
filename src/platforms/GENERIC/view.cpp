#include "view.h"
#include <application.h>

PlatformView::PlatformView(Application* app)
    : QGLWidget(), _q(app)
{
    startTimer(16);
    setWindowTitle(PROJECT_NAME);
}

void PlatformView::initializeGL()
{
    _q->initialize();
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
    updateGL();
}
