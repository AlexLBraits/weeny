#include <WRenderer.h>
#include <graphics.h>

void WRenderer::initialize()
{
}
void WRenderer::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void WRenderer::clear(float r, float g, float b, float a)
{
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
