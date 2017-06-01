#include "application_p.h"
#include "view.h"

WApplication_p::WApplication_p(WApplication* owner, int argc, char** argv)
 : _q(owner), _app(argc, argv), _view(_q)
{
    _view.show();
}

WApplication_p::~WApplication_p()
{
}

int WApplication_p::exec()
{
    return _app.exec();
}
