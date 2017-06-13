#ifndef BASIC_NODES_H
#define BASIC_NODES_H

#include <universe.h>

struct RectangleNode : public DrawingNode
{
    RectangleNode(float width, float height, const glm::vec3& pos,
                  const glm::vec4& color);

protected:
    float m_width;
    float m_height;
    std::vector<glm::vec4> m_colors;

    void calculateTransform() const override;
    void draw_this(const glm::mat4x4& M) const override;
};

#endif /* BASIC_NODES_H */
