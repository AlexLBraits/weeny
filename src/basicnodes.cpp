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

    setTranslation(pos);
    calculateTransform();
}

float RectangleNode::width() const
{
    return m_width;
}

void RectangleNode::setWidth(float width)
{
    m_width = width;
    calculateTransform();
}

float RectangleNode::height() const
{
    return m_height;
}

void RectangleNode::setHeight(float height)
{
    m_height = height;
    calculateTransform();
}
///
/// \brief RectangleNode::_calculateTransform
///
void RectangleNode::calculateTransform() const
{
    DrawingNode::calculateTransform();

    float aspect = m_height/m_width;
    m_uvs[0] = glm::vec2(0.0f,0.0f);
    m_uvs[1] = glm::vec2(1.0f,0.0f);
    m_uvs[2] = glm::vec2(1.0f,aspect);
    m_uvs[3] = m_uvs[0];
    m_uvs[4] = m_uvs[2];
    m_uvs[5] = glm::vec2(0.0f,aspect);

    glm::mat4x4 tr = transform();
    m_vertices[0] = tr * glm::vec4(0.0f,0.0f,0.0f,1.0f);
    m_vertices[1] = tr * glm::vec4(m_width,0,0,1.0f);
    m_vertices[2] = tr * glm::vec4(m_width,m_height,0.0f,1.0f);
    m_vertices[3] = m_vertices[0];
    m_vertices[4] = m_vertices[2];
    m_vertices[5] = tr * glm::vec4(0.0f,m_height,0.0f,1.0f);
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
    
    TexturePtr texture = this->texture();
    int texture_unit = 0;
    program->setUniformValue("texture", texture_unit);
    texture->bind(texture_unit);
    
    program->setAttribValues("colors", m_colors);
    program->setAttribValues("coords", m_vertices);
    program->setAttribValues("uvs", m_uvs);
}
