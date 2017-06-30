#ifndef UNIVERSE_DRAW_NODE_H
#define UNIVERSE_DRAW_NODE_H

#include <universe/node.h>
#include <universe/mesh.h>
#include <texture.h>
#include <program.h>
#include <vector>

class DrawNode : public Node
{
public:
    DrawNode();
    void draw(const glm::mat4x4& PV = glm::mat4x4(1)) const;
    TexturePtr texture() const;
    void setTexture(const TexturePtr& ptr);
    ProgramPtr program() const;

protected:
    virtual void draw_this(const glm::mat4x4& M) const;

    MeshPtr m_mesh;

    mutable TexturePtr m_texture;
    mutable ProgramPtr m_program;
};

#endif /* UNIVERSE_DRAW_NODE_H */
