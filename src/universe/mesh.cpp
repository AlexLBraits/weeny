#include <universe/mesh.h>

RectangleMesh::RectangleMesh(float width, float height, const glm::vec4 &color)
    : m_width(width),
      m_height(height),
      m_color(color)
{
    m_colors = std::vector<glm::vec4>(6, color);
    m_uvs.resize(6);
    m_vertices.resize(6);
}

void RectangleMesh::calculateGeometry(const glm::mat4x4 &tr)
{
    float aspect = m_width ? m_height / m_width : 1;

    m_uvs[0] = glm::vec2(0.0f,0.0f);
    m_uvs[1] = glm::vec2(10.0f,0.0f);
    m_uvs[2] = glm::vec2(10.0f,10.0f*aspect);
    m_uvs[3] = m_uvs[0];
    m_uvs[4] = m_uvs[2];
    m_uvs[5] = glm::vec2(0.0f,10.0f*aspect);

    m_vertices[0] = tr * glm::vec4(0.0f,0.0f,0.0f,1.0f);
    m_vertices[1] = tr * glm::vec4(m_width,0,0,1.0f);
    m_vertices[2] = tr * glm::vec4(m_width,m_height,0.0f,1.0f);
    m_vertices[3] = m_vertices[0];
    m_vertices[4] = m_vertices[2];
    m_vertices[5] = tr * glm::vec4(0.0f,m_height,0.0f,1.0f);
}
