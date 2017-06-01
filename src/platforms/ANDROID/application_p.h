#ifndef APPLICATION_P_H
#define APPLICATION_P_H

class WApplication;

class WApplication_p
{
public:
    WApplication_p(WApplication* owner, int argc, char** argv);
    ~WApplication_p();
    int exec();
    
private:
    WApplication* _q;
};

#endif // APPLICATION_P_H
