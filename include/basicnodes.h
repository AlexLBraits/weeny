#ifndef BASIC_NODES_H
#define BASIC_NODES_H

#include <universe.h>

struct RectangleNode : public DrawingNode
{
public:
    RectangleNode(float width, float height, const glm::vec3& pos,
                  const glm::vec4& color);    

    float width() const;
    void setWidth(float width);

    float height() const;
    void setHeight(float height);

protected:
    float m_width;
    float m_height;

    void calculateTransform() const override;
    void draw_this(const glm::mat4x4& M) const override;
};

#endif /* BASIC_NODES_H */
