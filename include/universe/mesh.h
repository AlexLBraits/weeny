#ifndef UNIVERSE_MESH_H
#define UNIVERSE_MESH_H

#include <types.h>
#include <vector>
#include <memory>

struct Mesh
{
    mutable std::vector<glm::vec3> m_vertices;
    mutable std::vector<glm::vec2> m_uvs;
    mutable std::vector<glm::vec4> m_colors;

    virtual ~Mesh() {}
    virtual void calculateGeometry(const glm::mat4x4& tr) = 0;
};

typedef std::shared_ptr<Mesh> MeshPtr;

struct RectangleMesh : public Mesh
{
    RectangleMesh(float width, float height, const glm::vec4& color);
    void calculateGeometry(const glm::mat4x4& tr) override;

private:
    float m_width;
    float m_height;
    glm::vec4 m_color;
};


#endif /* UNIVERSE_MESH_H */
