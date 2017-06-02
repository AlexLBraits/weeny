#include "application_p.h"
#include "view.h"

Application_p::Application_p(Application* owner, int argc, char** argv)
    : _q(owner), _app(argc, argv), _view(_q)
{
    _view.show();
}

Application_p::~Application_p()
{
}

int Application_p::exec()
{
    return _app.exec();
}
