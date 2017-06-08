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

    for(auto& ul : universe) ul->draw(tr);
}
