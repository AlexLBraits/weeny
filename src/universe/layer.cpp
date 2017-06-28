#include <universe/layer.h>

///
/// \brief Layer::Layer
///
Layer::Layer()
{
    m_translation = glm::vec3(0,0,0);
    CameraPtr camera = CameraPtr(new OrthoCamera());
    m_spectator = SpectatorPtr(new Spectator(camera));
}
///
/// \brief Layer::draw
///
void Layer::draw() const
{
    glm::mat4x4 tr = transform();
    for(const auto& dnode : *this)
    {
        ((const DrawNode&)dnode).draw(tr);
    }
}
///
/// \brief Layer::spectator
/// \return
///
SpectatorPtr Layer::spectator() const
{
    return m_spectator;
}
///
/// \brief Layer::calculateTransform
///
void Layer::calculateTransform() const
{
    const glm::mat4x4& V = spectator()->transform();
    const glm::mat4x4& P = spectator()->camera()->transform();

    u_transform = P * V;
    u_dirty_transform = 0;
}
///
/// \brief Layer::resize
/// \param width
/// \param height
///
void Layer::resize(int width, int height)
{
    spectator()->camera()->setWidth(width);
    spectator()->camera()->setHeight(height);
    ++u_dirty_transform;
}
