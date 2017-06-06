#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <memory>
#include <list>
#include <hierarchy.h>
#include <program.h>
#include <texture.h>

struct UniverseNode : public Hierarchy<UniverseNode>
{
    mutable glm::mat4x4 u_transform;
    void update(float dt);
};
typedef std::shared_ptr<UniverseNode> UniverseNodePtr;

class Visualiser;
struct UniverseLayer;

struct DrawingNode : public UniverseNode
{
    DrawingNode();

    ProgramPtr m_program;
    TexturePtr m_texture;
};
typedef std::shared_ptr<DrawingNode> DrawingNodePtr;

struct UniverseLayer
{
    /// корень визуальной иерархии
    DrawingNodePtr m_root;
    void update(float dt);
};

typedef std::shared_ptr<UniverseLayer> UniverseLayerPtr;

struct Universe : public std::list<UniverseLayerPtr>
{
    void update(float dt);
};

#endif /*  UNIVERSE_H */
