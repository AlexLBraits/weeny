#include <application.h>

int main(int argc, char** argv)
{
    const Application& app = Application::getInstance(argc, argv);
    return app.exec();
}
