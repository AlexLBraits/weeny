#ifndef APPLICATION_P_H
#define APPLICATION_P_H

class Application;

class Application_p
{
public:
    Application_p(Application* owner, int argc, char** argv);
    ~Application_p();
    int exec();
    
private:
    Application* _q;
};

#endif // APPLICATION_P_H
