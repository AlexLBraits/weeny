#include <universe/node.h>

////////////////////////////////////////////////////////////////////////////////
///
/// Node class implementation
///

///
/// \brief Node::update
/// \param dt
///
Node::Node()
    : m_translation(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
      m_scale(glm::vec3(1.0f, 1.0f, 1.0f)),
      u_dirty_transform(1)
{
}
///
/// \brief Node::update
/// \param dt
///
void Node::update(float dt)
{
    update_this(dt);
    for(Node& node : *this) node.update(dt);
}
///
/// \brief Node::update_this
/// \param dt
///
void Node::update_this(float dt)
{
}
///
/// \brief Node::calculateTransform
///
void Node::calculateTransform() const
{
    u_transform = glm::translate(glm::mat4x4(1), m_translation);
    u_transform = glm::rotate(u_transform, m_rotation.x, glm::vec3(1,0,0));
    u_transform = glm::rotate(u_transform, m_rotation.y, glm::vec3(0,1,0));
    u_transform = glm::rotate(u_transform, m_rotation.z, glm::vec3(0,0,1));
    u_transform = glm::scale(u_transform, m_scale);

    u_dirty_transform = 0;
}
///
/// \brief Node::transform
/// \return
///
glm::mat4x4 Node::transform() const
{
    if(u_dirty_transform) calculateTransform();
    return u_transform;
}
///
/// \brief Node::scale
/// \return
///
glm::vec3 Node::scale() const
{
    return m_scale;
}
///
/// \brief Node::rotation
/// \return
///
glm::vec3 Node::rotation() const
{
    return m_rotation;
}
///
/// \brief Node::translation
/// \return
///
glm::vec3 Node::translation() const
{
    return m_translation;
}
///
/// \brief Node::setScale
/// \param scale
///
void Node::setScale(const glm::vec3 &scale)
{
    if(m_scale != scale)
    {
        m_scale = scale;
        ++u_dirty_transform;
    }
}
///
/// \brief Node::setRotation
/// \param rotation
///
void Node::setRotation(const glm::vec3& rotation)
{
    if(m_rotation != rotation)
    {
        m_rotation = rotation;
        ++u_dirty_transform;
    }
}
///
/// \brief Node::setTranslation
/// \param translation
///
void Node::setTranslation(const glm::vec3 &translation)
{
    if(m_translation != translation)
    {
        m_translation = translation;
        ++u_dirty_transform;
    }
}
