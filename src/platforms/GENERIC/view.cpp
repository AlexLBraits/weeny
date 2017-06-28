#include "view.h"
#include <application.h>
#include <QDateTime>

PlatformView::PlatformView(Application* app)
    : QGLWidget(), _q(app)
{
    _lastTime = QDateTime::currentMSecsSinceEpoch();
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
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    float dt = (t - _lastTime) / 1000.0f;
    if(dt > 5.0f) dt = 1.0f / 60.0f;
    _q->update(dt);
    _lastTime = t;

    updateGL();
}
