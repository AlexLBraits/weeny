#ifndef UNIVERSE_NODE_H
#define UNIVERSE_NODE_H

#include <base/hierarchy.h>
#include <types.h>      // glm

////////////////////////////////////////////////////////////////////////////////
/// \brief The UniverseNode struct
///
class Node : public Hierarchy<Node>
{
public:
    Node();

    virtual void update(float dt);

    glm::vec3 translation() const;
    void setTranslation(const glm::vec3 &translation);
    glm::vec3 rotation() const;
    void setRotation(const glm::vec3 &rotation);
    glm::vec3 scale() const;
    void setScale(const glm::vec3 &scale);

    glm::mat4x4 transform() const;

protected:
    virtual void update_this(float dt);
    virtual void calculateTransform() const;

    glm::vec3 m_translation;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

    mutable int u_dirty_transform;
    mutable glm::mat4x4 u_transform;
};


#endif /* UNIVERSE_NODE_H */
