#ifndef RENDERER_H
#define RENDERER_H

class WRenderer
{
public:
    void initialize();
    void resize(int width, int height);
    void clear(float r, float g, float b, float a);
};

#endif // RENDERER_H
