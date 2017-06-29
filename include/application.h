#ifndef APPLICATION_H
#define APPLICATION_H

#include <base/singleton.h>
#include <universe/universe.h>
#include <widget.h>

class Application_p;

class Application
{
    friend class Singleton<Application>;

protected:
    Application();
    Application(int argc, char** argv);
    virtual ~Application();

public:
    static Application* app();
    int exec();
    virtual void initialize();

    void resize(int width, int height);
    void update();
    void draw() const;

    Universe& universe();

private:
    static Application* _app;
    Application_p* _d;
    long long _lastUpdateTime;

protected:
    Universe m_universe;
};

#endif /* APPLICATION_H */
