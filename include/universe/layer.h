#ifndef UNIVERSE_LAYER_H
#define UNIVERSE_LAYER_H

#include <universe/drawnode.h>
#include <universe/spectator.h>

class Layer : public Node
{
public:
    Layer();
    void draw() const;
    void resize(int width, int height);
    SpectatorPtr spectator() const;

protected:
    void calculateTransform() const override;

    SpectatorPtr m_spectator;
};

typedef std::shared_ptr<Layer> LayerPtr;

#endif /* UNIVERSE_LAYER_H */
