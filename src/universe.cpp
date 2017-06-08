#include <universe.h>
#include <cache.h>
#include <singleton.h>

#include <graphics.h>

void UniverseNode::update(float dt)
{
    _update(dt);
    for(UniverseNode& node : *this) node.update(dt);
}

void UniverseNode::_update(float dt)
{
}

void DrawingNode::draw(const glm::mat4x4 &parenttr) const
{
    glm::mat4x4 modeltr = parenttr * u_transform;
    _draw(modeltr);
    for(const auto& dnode : *this) ((const DrawingNode&)dnode).draw(modeltr);
}

void DrawingNode::_draw(const glm::mat4x4& M) const
{
    glm::mat4x4 V;
    glm::mat4x4 P;

    UniverseLayer* ul = dynamic_cast<UniverseLayer*>(root());
    if(ul)
    {
        V = ul->spectator()->getViewMatrix();
        P = ul->spectator()->getCamera()->getProjectionMatrix();
    }

    ProgramPtr program = this->program();
    program->bind();
    program->setUniformValue("color", {1.0f, 0.0f, 1.0f, 1.0f});
    program->setUniformValue("transform", P * V * M);

    glm::vec3 vertices[] = {{0,0,0},{100,0,0},{100,100,0}};
    program->drawTriangles("coord", vertices, 3);
}

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

void Universe::update(float dt)
{
    for(auto& layer : *this) layer->update(dt);
}

Spectator::Spectator(const CameraPtr& camera)
    : m_position(glm::vec3(0.0f, 0.0f, 100.0f)),
      m_target(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
      m_camera(camera)
{
    u_transform = glm::lookAt(m_position, m_target, m_up);
}

glm::mat4x4& Spectator::getViewMatrix() const
{
    return u_transform;
}

const CameraPtr& Spectator::getCamera() const
{
    return m_camera;
}

UniverseLayer::UniverseLayer()
{
    CameraPtr camera = CameraPtr(new OrthoCamera());
    m_spectator = SpectatorPtr(new Spectator(camera));
}

SpectatorPtr UniverseLayer::spectator() const
{
    return m_spectator;
}
////////////////////////////////////////////////////////////////////////////////
///
///
/// \brief Camera::Camera
///
Camera::Camera()
    : m_fov(60),
      m_width(640),
      m_height(480),
      m_near(10),
      m_far(1000)
{
}

glm::mat4x4 &Camera::getProjectionMatrix() const
{
    return u_transform;
}

float Camera::getFov() const
{
    return m_fov;
}

float Camera::getWidth() const
{
    return m_width;
}

float Camera::getHeight() const
{
    return m_height;
}

float Camera::getNear() const
{
    return m_near;
}

float Camera::getFar() const
{
    return m_far;
}

void Camera::setFov(float fov)
{
    if(m_fov != fov)
    {
        m_fov = fov;
        calculateTransform();
    }
}

void Camera::setWidth(float width)
{
    if(m_width != width)
    {
        m_width = width;
        calculateTransform();
    }
}

void Camera::setHeight(float height)
{
    if(m_height != height)
    {
        m_height = height;
        calculateTransform();
    }
}

void Camera::setNear(float near)
{
    if(m_near != near)
    {
        m_near = near;
        calculateTransform();
    }
}

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
///
/// \brief OrthoCamera::calculateTransform
///
OrthoCamera::OrthoCamera()
    : Camera()
{
    calculateTransform();
}

void OrthoCamera::calculateTransform() const
{
    u_transform = glm::ortho(
                      0.0f, m_width,
                      0.0f, m_height,
                      m_near, m_far
                  );
}
