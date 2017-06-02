#include <visualiser.h>
#include <universe.h>
#include <graphics.h>
///
/// Только здесь должны использоваться команды OpenGL
/// Только здесь должны быть видны типы OpenGL
///
void Visualiser::initialize()
{
}
void Visualiser::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}
void Visualiser::drawUniverse(const Universe& universe)
{
    for(auto& ul : universe) drawUniverseLayer(ul);
}
void Visualiser::drawUniverseLayer(const UniverseLayer& ulayer)
{
    _clear(0, 1, 0, 1);
}
void Visualiser::_clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
