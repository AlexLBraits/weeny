#include <universe/camera.h>

////////////////////////////////////////////////////////////////////////////////
///
///  Camera class implementation
///

///
/// \brief Camera::Camera
///
Camera::Camera()
    : m_fov(60),
      m_width(0),
      m_height(0),
      m_near(10),
      m_far(1000)
{
}
///
/// \brief Camera::getFov
/// \return
///
float Camera::fov() const
{
    return m_fov;
}
///
/// \brief Camera::getWidth
/// \return
///
float Camera::width() const
{
    return m_width;
}
///
/// \brief Camera::getHeight
/// \return
///
float Camera::height() const
{
    return m_height;
}
///
/// \brief Camera::getNear
/// \return
///
float Camera::near() const
{
    return m_near;
}
///
/// \brief Camera::getFar
/// \return
///
float Camera::far() const
{
    return m_far;
}
///
/// \brief Camera::setFov
/// \param fov
///
void Camera::setFov(float fov)
{
    if(m_fov != fov)
    {
        m_fov = fov;
        ++u_dirty_transform;
    }
}
///
/// \brief Camera::setWidth
/// \param width
///
void Camera::setWidth(float width)
{
    if(m_width != width)
    {
        m_width = width;
        ++u_dirty_transform;
    }
}
///
/// \brief Camera::setHeight
/// \param height
///
void Camera::setHeight(float height)
{
    if(m_height != height)
    {
        m_height = height;
        ++u_dirty_transform;
    }
}
///
/// \brief Camera::setNear
/// \param near
///
void Camera::setNear(float near)
{
    if(m_near != near)
    {
        m_near = near;
        ++u_dirty_transform;
    }
}
///
/// \brief Camera::setFar
/// \param far
///
void Camera::setFar(float far)
{
    if(m_far != far)
    {
        m_far = far;
        ++u_dirty_transform;
    }
}
////////////////////////////////////////////////////////////////////////////////
///
///   OrthoCamera class implementation
///

///
/// \brief OrthoCamera::calculateTransform
///
OrthoCamera::OrthoCamera()
    : Camera()
{
}
///
/// \brief OrthoCamera::_calculateTransform
///
void OrthoCamera::calculateTransform() const
{
    u_transform = glm::ortho(0.0f, m_width, 0.0f, m_height, m_near, m_far);
    u_dirty_transform = 0;
}
////////////////////////////////////////////////////////////////////////////////
///
///   PerspectiveCamera class implementation
///

///
/// \brief PerspectiveCamera::PerspectiveCamera
///
PerspectiveCamera::PerspectiveCamera()
    : Camera()
{
}
///
/// \brief PerspectiveCamera::calculateTransform
///
void PerspectiveCamera::calculateTransform() const
{
    float aspect = m_width ? m_height / m_width : 1;
    u_transform = glm::perspective(m_fov, aspect, m_near, m_far);
    u_dirty_transform = 0;
}
