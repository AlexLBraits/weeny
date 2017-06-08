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
    int exec();
    virtual void initialize();

    void resize(int width, int height);
    void update(float dt);
    void draw() const;

private:
    Application_p* _d;

protected:
    Universe m_universe;
    mutable Widget m_visualiser;
};

#endif /* APPLICATION_H */
