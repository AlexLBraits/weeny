#include <application.h>

#if defined( BUILD_ANDROID )
#include <platforms/ANDROID/application_p.h>
#elif defined( BUILD_GENERIC )
#include <platforms/GENERIC/application_p.h>
#elif defined( BUILD_IOS )
#include <platforms/IOS/application_p.h>
#endif

#include <chrono>

Application* Application::_app = 0;

Application::Application()
    : _d(0), _lastUpdateTime(0)
{
    _app = this;
}

Application::Application(int argc, char** argv)
    : Application()
{
    _d = new Application_p(this, argc, argv);
}

Application::~Application()
{
    if(_d) delete _d;
}

Application *Application::app()
{
    return _app;
}

int Application::exec()
{
    return _d->exec();
}

void Application::initialize()
{
    m_universe.initialize();
}

void Application::resize(int width, int height)
{
    m_universe.resize(width, height);
}

void Application::update()
{
    long long t = std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
    float dt = (t - _lastUpdateTime) / 1000.0f;
    if(dt > 5.0f) dt = 1.0f / 60.0f;
    _lastUpdateTime = t;

    m_universe.update(dt);
}

void Application::draw() const
{
    m_universe.draw();
}

Universe &Application::universe()
{
    return m_universe;
}
