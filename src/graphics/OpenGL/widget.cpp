#include <widget.h>
#include <universe.h>
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
    glm::mat4x4 tr(1);

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glDisable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
    for(auto& ul : universe)
    {
        ul->draw(tr);
    }

    Program::draw();
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
