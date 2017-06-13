#include <universe.h>
#include <cache.h>
#include <singleton.h>

#include <graphics.h>

////////////////////////////////////////////////////////////////////////////////
///
/// UniverseNode class implementation
///

///
/// \brief UniverseNode::update
/// \param dt
///
void UniverseNode::update(float dt)
{
    update_this(dt);
    for(UniverseNode& node : *this) node.update(dt);
}
///
/// \brief UniverseNode::_update
/// \param dt
///
void UniverseNode::update_this(float dt)
{
}
///
/// \brief UniverseNode::_calculateTransform
///
void UniverseNode::calculateTransform() const
{
}
////////////////////////////////////////////////////////////////////////////////
///
/// DrawingNode class implementation
///

///
/// \brief DrawingNode::draw
/// \param parenttr
///
void DrawingNode::draw(const glm::mat4x4 &parenttr) const
{
    glm::mat4x4 modeltr = parenttr * u_transform;
    draw_this(modeltr);
    for(const auto& dnode : *this) ((const DrawingNode&)dnode).draw(modeltr);
}
///
/// \brief DrawingNode::resize
/// \param width
/// \param height
///
void DrawingNode::resize(int width, int height)
{
    resize_this(width, height);
    for(const auto& dnode : *this) ((DrawingNode&)dnode).resize(width, height);
}
///
/// \brief DrawingNode::_draw
/// \param M
///
void DrawingNode::draw_this(const glm::mat4x4& M) const
{
}
///
/// \brief DrawingNode::_resize
/// \param width
/// \param height
///
void DrawingNode::resize_this(int width, int height)
{
}
///
/// \brief DrawingNode::position
/// \return
///
glm::vec3 DrawingNode::position() const
{
    return m_position;
}
///
/// \brief DrawingNode::setPosition
/// \param position
///
void DrawingNode::setPosition(const glm::vec3 &position)
{
    if(m_position != position)
    {
        m_position = position;
        calculateTransform();
    }
}
///
/// \brief DrawingNode::program
/// \return
///
ProgramPtr DrawingNode::program() const
{
    if(!m_program)
    {
        DrawingNode* node = static_cast<DrawingNode*>(parentNode());
        while(node && !(m_program = node->m_program))
        {
            node = static_cast<DrawingNode*>(node->parentNode());
        }
        if(!m_program)
        {
            m_program = Singleton<ResourceCache<ProgramPtr>>::getInstance().get("dummy");
        }
    }
    return m_program;
}

////////////////////////////////////////////////////////////////////////////////
///
/// Spectator class implementation
///

///
/// \brief Spectator::Spectator
/// \param camera
///
Spectator::Spectator(const CameraPtr& camera)
    : m_target(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_camera(camera)
{
    setPosition(glm::vec3(0.0f, 0.0f, 100.0f));
    calculateTransform();
}
///
/// \brief Spectator::_calculateTransform
///
void Spectator::calculateTransform() const
{
    u_transform = glm::lookAt(m_position, m_target, m_up);
}
///
/// \brief Spectator::getViewMatrix
/// \return
///
glm::mat4x4& Spectator::getViewMatrix() const
{
    return u_transform;
}
///
/// \brief Spectator::getCamera
/// \return
///
CameraPtr Spectator::camera() const
{
    return m_camera;
}
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
/// \brief Camera::getProjectionMatrix
/// \return
///
glm::mat4x4 &Camera::getProjectionMatrix() const
{
    return u_transform;
}
///
/// \brief Camera::getFov
/// \return
///
float Camera::getFov() const
{
    return m_fov;
}
///
/// \brief Camera::getWidth
/// \return
///
float Camera::getWidth() const
{
    return m_width;
}
///
/// \brief Camera::getHeight
/// \return
///
float Camera::getHeight() const
{
    return m_height;
}
///
/// \brief Camera::getNear
/// \return
///
float Camera::getNear() const
{
    return m_near;
}
///
/// \brief Camera::getFar
/// \return
///
float Camera::getFar() const
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
        calculateTransform();
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
        calculateTransform();
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
        calculateTransform();
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
        calculateTransform();
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
        calculateTransform();
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
    calculateTransform();
}
///
/// \brief OrthoCamera::_calculateTransform
///
void OrthoCamera::calculateTransform() const
{
    u_transform = glm::ortho(
                      0.0f, m_width,
                      0.0f, m_height,
                      m_near, m_far
                  );
}
////////////////////////////////////////////////////////////////////////////////
///
/// UniverseLayer class implementation
///

///
/// \brief UniverseLayer::UniverseLayer
///
UniverseLayer::UniverseLayer()
{
    CameraPtr camera = CameraPtr(new OrthoCamera());
    m_spectator = SpectatorPtr(new Spectator(camera));
}
///
/// \brief UniverseLayer::draw
/// \param parenttr
///
void UniverseLayer::draw(const glm::mat4x4&) const
{
    calculateTransform();
    glm::mat4x4 M;
    draw_this(M);
    for(const auto& dnode : *this) ((const DrawingNode&)dnode).draw(M);
}
///
/// \brief UniverseLayer::getProjectViewMatrix
/// \return
///
glm::mat4x4 &UniverseLayer::getProjectViewMatrix() const
{
    return u_transform;
}
///
/// \brief UniverseLayer::spectator
/// \return
///
SpectatorPtr UniverseLayer::spectator() const
{
    return m_spectator;
}
///
/// \brief UniverseLayer::calculateTransform
///
void UniverseLayer::calculateTransform() const
{
    const glm::mat4x4& V = spectator()->getViewMatrix();
    const glm::mat4x4& P = spectator()->camera()->getProjectionMatrix();

    u_transform = P * V;
}
///
/// \brief UniverseLayer::_draw
///
void UniverseLayer::draw_this(const glm::mat4x4 &) const
{
}
///
/// \brief UniverseLayer::resize
/// \param width
/// \param height
///
void UniverseLayer::resize_this(int width, int height)
{
    spectator()->camera()->setWidth(width);
    spectator()->camera()->setHeight(height);
}

////////////////////////////////////////////////////////////////////////////////
///
///  Universe class implementation
///

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
void Universe::push_back(UniverseLayerPtr layer)
{
    Layers::push_back(layer);
    layer->resize(m_window.width(), m_window.height());
}
