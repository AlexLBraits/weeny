#include <universe/spectator.h>

///
/// \brief Spectator::Spectator
/// \param camera
///
Spectator::Spectator(const CameraPtr& camera)
    : m_target(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_camera(camera)
{
    setTranslation(glm::vec3(0.0f, 0.0f, 100.0f));
}
///
/// \brief Spectator::calculateTransform
///
void Spectator::calculateTransform() const
{
    u_transform = glm::lookAt(m_translation, m_target, m_up);
    u_dirty_transform = 0;
}
///
/// \brief Spectator::setCamera
/// \param camera
///
void Spectator::setCamera(const CameraPtr& camera)
{
    if(m_camera != camera)
    {
        m_camera = camera;
        ++u_dirty_transform;
    }
}
///
/// \brief Spectator::getCamera
/// \return
///
CameraPtr Spectator::camera() const
{
    return m_camera;
}
