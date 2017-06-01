#include "view.h"
#include <WApplication.h>
#include <QDateTime>

PlatformView::PlatformView(WApplication* app)
    : QGLWidget(), _q(app)
{
    _lastTime = QDateTime::currentMSecsSinceEpoch();
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
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    float dt = (t - _lastTime) / 1000.0f;
    _q->update(dt);
    _lastTime = t;
        
    updateGL();
}
