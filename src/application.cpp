#include <application.h>

#if defined( BUILD_ANDROID )
#include <platforms/ANDROID/application_p.h>
#elif defined( BUILD_GENERIC )
#include <platforms/GENERIC/application_p.h>
#elif defined( BUILD_IOS )
#include <platforms/IOS/application_p.h>
#endif

Application* Application::_app = 0;

Application::Application()
    : _d(0)
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

void Application::update(float dt)
{
    m_universe.update(dt);
}

void Application::draw() const
{
    m_universe.draw();
}
