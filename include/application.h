#ifndef APPLICATION_H
#define APPLICATION_H

#include <singleton.h>

class Application_p;

class Application : public Singleton<Application>
{
friend class Singleton<Application>;

protected:
  Application();
  Application(int argc, char** argv);
  ~Application();

public:
  int exec() const;

  virtual void initialize();
  virtual void resize(int width, int height);
  virtual void update(float dt);
  virtual void draw();

private:
  Application_p* _d;
};

#endif // APPLICATION_H
