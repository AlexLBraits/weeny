#include <application.h>

std::map<std::string, std::pair<const unsigned char*, unsigned int>> resources;

int main(int argc, char** argv)
{
    Application& app = Singleton<Application>::getInstance(argc, argv);
    return app.exec();
}
