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
{
    m_mesh = MeshPtr(new RectangleMesh(width, height, color));
    setTranslation(pos);
}
///
/// \brief RectangleNode::update
/// \param dt
///
void RectangleNode::update(float dt)
{
}
///
/// \brief RectangleNode::draw_this
/// \param M
///
void RectangleNode::draw_this(const glm::mat4x4& M) const
{
    ProgramPtr program = this->program();
    program->bind();
    program->setUniformValue("transform", M * transform());
    
    TexturePtr texture = this->texture();
    int texture_unit = 0;
    program->setUniformValue("texture", texture_unit);
    texture->bind(texture_unit);
    
    program->setAttribValues("colors", m_mesh->m_colors);
    program->setAttribValues("coords", m_mesh->m_vertices);
    program->setAttribValues("uvs", m_mesh->m_uvs);
}
