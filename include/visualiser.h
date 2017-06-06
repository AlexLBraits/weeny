#ifndef RENDERER_H
#define RENDERER_H

#include <universe.h>

class Visualiser
{
public:
    void initialize();
    void resize(int width, int height);
    void drawUniverse(const Universe& universe);
    void drawUniverseLayer(UniverseLayerPtr ulayer);
    void drawDrawingNode(DrawingNode *node);

private:
    void _clear(float r, float g, float b, float a);
    void _drawDrawingNode(DrawingNode *node);
};

#endif // RENDERER_H
