#ifndef RENDERER_H
#define RENDERER_H

struct Universe;
struct UniverseLayer;

class Visualiser
{
public:
    void initialize();
    void resize(int width, int height);
    void drawUniverse(const Universe& universe);
    void drawUniverseLayer(const UniverseLayer& ulayer);

private:
    void _clear(float r, float g, float b, float a);
};

#endif // RENDERER_H
