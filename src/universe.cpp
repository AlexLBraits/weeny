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
UniverseNode::UniverseNode()
    : m_translation(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
      u_dirty_transform(0)
{
}

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
    u_transform = glm::translate(glm::mat4x4(1), m_translation);
    u_transform = glm::rotate(u_transform, m_rotation.x, glm::vec3(1,0,0));
    u_transform = glm::rotate(u_transform, m_rotation.y, glm::vec3(0,1,0));
    u_transform = glm::rotate(u_transform, m_rotation.z, glm::vec3(0,0,1));
    u_transform = glm::scale(u_transform, m_scale);

    u_dirty_transform = 0;
}
///
/// \brief UniverseNode::setTransform
/// \param value
///
void UniverseNode::setTransform(const glm::mat4x4 &value) const
{
    u_transform = value;
    u_dirty_transform = 0;
}
///
/// \brief UniverseNode::getTransform
/// \return
///
glm::mat4x4 UniverseNode::transform() const
{
    if(u_dirty_transform) calculateTransform();
    return u_transform;
}
///
/// \brief UniverseNode::scale
/// \return
///
glm::vec3 UniverseNode::scale() const
{
    return m_scale;
}
///
/// \brief UniverseNode::rotation
/// \return
///
glm::vec3 UniverseNode::rotation() const
{
    return m_rotation;
}
///
/// \brief UniverseNode::translation
/// \return
///
glm::vec3 UniverseNode::translation() const
{
    return m_translation;
}
///
/// \brief UniverseNode::setScale
/// \param scale
///
void UniverseNode::setScale(const glm::vec3 &scale)
{
    if(m_scale != scale)
    {
        m_scale = scale;
        ++u_dirty_transform;
    }
}
///
/// \brief UniverseNode::setRotation
/// \param rotation
///
void UniverseNode::setRotation(const glm::vec3& rotation)
{
    if(m_rotation != rotation)
    {
        m_rotation = rotation;
        ++u_dirty_transform;
    }
}
///
/// \brief UniverseNode::setTranslation
/// \param translation
///
void UniverseNode::setTranslation(const glm::vec3 &translation)
{
    if(m_translation != translation)
    {
        m_translation = translation;
        ++u_dirty_transform;
    }
}
////////////////////////////////////////////////////////////////////////////////
///
/// DrawingNode class implementation
///

///
/// \brief DrawingNode::draw
/// \param parenttr
///
DrawingNode::DrawingNode()
    : m_dimensions(0,0,0)
{
    m_vertices.resize(6);
    m_uvs.resize(6);
    m_colors = std::vector<glm::vec4>(6, glm::vec4(1,1,1,1));
}
///
/// \brief DrawingNode::draw
/// \param parenttr
///
void DrawingNode::draw(const glm::mat4x4 &parenttr) const
{
    glm::mat4x4 modeltr = parenttr * transform();
    draw_this(modeltr);
    for(const auto& dnode : *this)
    {
        ((const DrawingNode&)dnode).draw(modeltr);
    }
}
///
/// \brief DrawingNode::resize
/// \param width
/// \param height
///
void DrawingNode::resize(int width, int height)
{
    resize_this(width, height);
    for(const auto& dnode : *this)
    {
        ((DrawingNode&)dnode).resize(width, height);
    }
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
/// \brief DrawingNode::dimensions
/// \return
///
glm::vec3 DrawingNode::dimensions() const
{
    return m_dimensions;
}
///
/// \brief DrawingNode::setDimensions
/// \param dimensions
///
void DrawingNode::setDimensions(const glm::vec3 &dimensions)
{
    if(m_dimensions != dimensions)
    {
        m_dimensions = dimensions;
        calculateTransform();
    }
}
///
/// \brief DrawingNode::texture
/// \return
///
TexturePtr DrawingNode::texture() const
{
    if(!m_texture)
    {
        m_texture = Singleton<ResourceCache<TexturePtr>>::getInstance().get("dummy");
    }
    return m_texture;
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
    setTranslation(glm::vec3(0.0f, 0.0f, 100.0f));
    calculateTransform();
}
///
/// \brief Spectator::_calculateTransform
///
void Spectator::calculateTransform() const
{
    setTransform(glm::lookAt(m_translation, m_target, m_up));
}

void Spectator::setCamera(const CameraPtr &camera)
{
    m_camera = camera;
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
    setTransform(
        glm::ortho(
            0.0f, m_width,
            0.0f, m_height,
            m_near, m_far
        )
    );
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
    calculateTransform();
}
///
/// \brief PerspectiveCamera::calculateTransform
///
void PerspectiveCamera::calculateTransform() const
{
    float aspect = m_width ? m_height / m_width : 1;
    setTransform(
        glm::perspective(m_fov, aspect, m_near, m_far)
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
    m_translation = glm::vec3(0,0,0);
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
    for(const auto& dnode : *this)
    {
        ((const DrawingNode&)dnode).draw(M);
    }
}
///
/// \brief UniverseLayer::getProjectViewMatrix
/// \return
///
glm::mat4x4 UniverseLayer::getProjectViewMatrix() const
{
    return transform();
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
    const glm::mat4x4& V = spectator()->transform();
    const glm::mat4x4& P = spectator()->camera()->transform();

    setTransform(P * V);
}
///
/// \brief UniverseLayer::_draw
///
void UniverseLayer::draw_this(const glm::mat4x4& m) const
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

    setDimensions(glm::vec3(width, height, 0));
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

const Window &Universe::window() const
{
    return m_window;
}
