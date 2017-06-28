#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <universe/layer.h>
#include <list>
#include <widget.h>

typedef std::list<LayerPtr> Layers;

class Universe : protected Layers
{
public:
    void initialize();
    void resize(int width, int height);
    void update(float dt);
    void draw() const;

    Layers::iterator begin() {return Layers::begin(); }
    Layers::iterator end() {return Layers::end(); }
    Layers::const_iterator begin() const {return Layers::cbegin(); }
    Layers::const_iterator end() const {return Layers::cend(); }
    void push_back(LayerPtr layer);

    const Window& window() const;

protected:
    mutable Window m_window;
};

#endif /*  UNIVERSE_H */
