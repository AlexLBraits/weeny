#ifndef APPLICATION_P_H
#define APPLICATION_P_H

#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

class Application;

class Application_p
{
public:
    Application_p(Application* owner, int argc, char** argv);
    ~Application_p();
    int exec();
    
private:
    Application* _q;
    int _argc;
    char** _argv;
};

#endif // APPLICATION_P_H
