#ifndef APPLICATION_P_H
#define APPLICATION_P_H

#include <QApplication>
#include "view.h"

class Application;

class Application_p
{
public:
    Application_p(Application* owner, int argc, char** argv);
    ~Application_p();
    int exec();
    
private:
    Application* _q;
    QApplication _app;
    PlatformView _view;
};

#endif // APPLICATION_P_H
