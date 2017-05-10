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

int Application::exec() const
{
    return _d->exec();
}

void Application::initialize()
{
    glClearColor(1.0, 1.0, 0.0, 1.0);
}

void Application::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Application::update(float dt)
{
}

void Application::draw()
{
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
