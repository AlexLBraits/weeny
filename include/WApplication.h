#ifndef W_APPLICATION_H
#define W_APPLICATION_H

#include <WSingleton.h>
#include <WRenderer.h>

class WApplication_p;

class WApplication : public WSingleton<WApplication>
{
friend class WSingleton<WApplication>;

protected:
  WApplication();
  WApplication(int argc, char** argv);
  ~WApplication();

public:
  int exec() const;

  virtual void initialize();
  virtual void resize(int width, int height);
  virtual void update(float dt);
  virtual void draw() const;

private:
  WApplication_p* _d;
  mutable WRenderer _renderer;
};

#endif /* W_APPLICATION_H */
