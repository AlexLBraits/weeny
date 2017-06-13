#include <widget.h>
#include <universe.h>
#include <graphics.h>

void Widget::initialize()
{
}
void Widget::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void Widget::draw(const Universe& universe) const
{
    glm::mat4x4 tr(1);

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);
    
    for(auto& ul : universe) ul->draw(tr);

    Program::draw();
}

int Widget::width() const
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[2];
}

int Widget::height() const
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    return viewport[3];
}
