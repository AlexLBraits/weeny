#include <application.h>

#if defined( BUILD_ANDROID )
#include <platforms/ANDROID/application_p.h>
#elif defined( BUILD_GENERIC )
#include <platforms/GENERIC/application_p.h>
#elif defined( BUILD_IOS )
#include <platforms/IOS/application_p.h>
#endif

Application::Application()
    : _d(0)
{
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

int Application::exec()
{
    return _d->exec();
}

void Application::initialize()
{
    m_visualiser.initialize();
}

void Application::resize(int width, int height)
{
    m_visualiser.resize(width, height);
}

void Application::update(float dt)
{
    m_universe.update(dt);
}

void Application::draw() const
{
    m_visualiser.draw(m_universe);
}
