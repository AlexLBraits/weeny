#include <universe/universe.h>

///
/// \brief Universe::initialize
///
void Universe::initialize()
{
    m_window.initialize();
}
///
/// \brief Universe::resize
/// \param width
/// \param height
///
void Universe::resize(int width, int height)
{
    m_window.resize(width, height);

    width = m_window.width();
    height = m_window.height();

    for(auto& layer : *this) layer->resize(width, height);
}
///
/// \brief Universe::update
/// \param dt
///
void Universe::update(float dt)
{
    for(auto& layer : *this) layer->update(dt);
}
///
/// \brief Universe::draw
///
void Universe::draw() const
{
    m_window.draw(*this);
}
///
/// \brief Universe::push_back
/// \param layer
///
void Universe::push_back(LayerPtr layer)
{
    Layers::push_back(layer);
    layer->resize(m_window.width(), m_window.height());
}

const Window &Universe::window() const
{
    return m_window;
}
