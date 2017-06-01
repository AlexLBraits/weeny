#ifndef APPLICATION_P_H
#define APPLICATION_P_H

#include <QApplication>
#include "view.h"

class WApplication;

class WApplication_p
{
public:
    WApplication_p(WApplication* owner, int argc, char** argv);
    ~WApplication_p();
    int exec();
    
private:
    WApplication* _q;
    QApplication _app;
    PlatformView _view;
};

#endif // APPLICATION_P_H
