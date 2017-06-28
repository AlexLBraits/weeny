#ifndef BASIC_NODES_H
#define BASIC_NODES_H

#include <universe/universe.h>

struct RectangleNode : public DrawNode
{
public:
    RectangleNode(float width, float height, const glm::vec3& pos,
                  const glm::vec4& color);
    void update(float dt) override;

protected:
    void draw_this(const glm::mat4x4& M) const override;
};

#endif /* BASIC_NODES_H */
