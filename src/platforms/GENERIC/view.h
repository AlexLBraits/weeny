#ifndef PLATFORM_VIEW_H
#define PLATFORM_VIEW_H

#include <graphics.h>

class Application;

class PlatformView : public QGLWidget
{
    Q_OBJECT

public:
    PlatformView(Application* app);

protected:
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;
    bool event(QEvent* event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    qint64 _lastTime;
    Application* _q;
};

#endif // PLATFORM_VIEW_H
