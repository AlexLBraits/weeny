#include <basicnodes.h>

////////////////////////////////////////////////////////////////////////////////
///
/// RectangleNode class implementation
///

///
/// \brief RectangleNode::RectangleNode
///
RectangleNode::RectangleNode(float width, float height, const glm::vec3 &pos,
                             const glm::vec4 &color)
    : m_width(width),
      m_height(height)
{
    m_colors = std::vector<glm::vec4>(6, color);
    setPosition(pos);
}
///
/// \brief RectangleNode::_calculateTransform
///
void RectangleNode::calculateTransform() const
{
    u_transform = glm::translate(u_transform, m_position);

    m_vertices.resize(6);
    m_vertices[0] = u_transform * glm::vec4(0.0f,0.0f,0.0f,1.0f);
    m_vertices[1] = u_transform * glm::vec4(m_width,0,0,1.0f);
    m_vertices[2] = u_transform * glm::vec4(m_width,m_height,0.0f,1.0f);
    m_vertices[3] = m_vertices[0];
    m_vertices[4] = m_vertices[2];
    m_vertices[5] = u_transform * glm::vec4(0.0f,m_height,0.0f,1.0f);
}
///
/// \brief RectangleNode::_draw
/// \param M
///
void RectangleNode::draw_this(const glm::mat4x4 &M) const
{
    ProgramPtr program = this->program();
    program->bind();
    program->setUniformValue("transform", ((UniverseLayer*)root())->getProjectViewMatrix());
    program->setAttribValues("colors", m_colors);
    program->setAttribValues("coords", m_vertices);
}
