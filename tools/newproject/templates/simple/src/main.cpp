#include <WApplication.h>

int main(int argc, char** argv)
{
    const WApplication& app = WApplication::getInstance(argc, argv);
    return app.exec();
}
