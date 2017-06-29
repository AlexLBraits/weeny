#include <widget.h>
#include <universe/universe.h>
#include <graphics.h>

void Window::initialize()
{
}
void Window::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void Window::draw(const Universe& universe) const
{
    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glDepthMask(true);

//    glDisable(GL_BLEND);

    for(auto& ul : universe) ul->draw();

    Program::drawBuffers();
}

int Window::width() const
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[2];
}

int Window::height() const
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[3];
}
