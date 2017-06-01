#include <WApplication.h>

#if defined( BUILD_ANDROID )
#include <platforms/ANDROID/application_p.h>
#elif defined( BUILD_GENERIC )
#include <platforms/GENERIC/application_p.h>
#elif defined( BUILD_IOS )
#include <platforms/IOS/application_p.h>
#endif

WApplication::WApplication()
  : _d(0)
{
}

WApplication::WApplication(int argc, char** argv)
  : WApplication()
{
    _d = new WApplication_p(this, argc, argv);
}

WApplication::~WApplication()
{
    if(_d) delete _d;
}

int WApplication::exec() const
{
    return _d->exec();
}

void WApplication::initialize()
{
    _renderer.initialize();
}

void WApplication::resize(int width, int height)
{
    _renderer.resize(width, height);
}

void WApplication::update(float dt)
{
    
}

void WApplication::draw() const
{
    _renderer.clear(1.0, 1.0, 0.0, 1.0);
}
