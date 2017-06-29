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
    m_mesh->calculateGeometry(transform());
}
///
/// \brief RectangleNode::draw_this
/// \param M
///
void RectangleNode::draw_this(const glm::mat4x4& PV) const
{
    ProgramPtr program = this->program();
    program->bind();
    program->setUniformValue("transform", PV);

    TexturePtr texture = this->texture();
    int texture_unit = 0;
    program->setUniformValue("texture", texture_unit);
    texture->bind(texture_unit);

    program->setAttribValues("colors", 4, m_mesh->m_colors.size(), (float*)m_mesh->m_colors.data());
    program->setAttribValues("coords", 3, m_mesh->m_vertices.size(), (float*)m_mesh->m_vertices.data());
    program->setAttribValues("uvs", 2, m_mesh->m_uvs.size(), (float*)m_mesh->m_uvs.data());
}
