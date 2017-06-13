#ifndef APPLICATION_H
#define APPLICATION_H

#include <singleton.h>
#include <universe.h>
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
    void update(float dt);
    void draw() const;

private:
    static Application* _app;
    Application_p* _d;

protected:
    Universe m_universe;
};

#endif /* APPLICATION_H */
