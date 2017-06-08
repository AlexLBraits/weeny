#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <list>

#include <hierarchy.h>
#include <types.h>
#include <program.h>
#include <texture.h>

struct UniverseNode : public Hierarchy<UniverseNode>
{
    void update(float dt);

protected:
    mutable glm::mat4x4 u_transform;
    virtual void _update(float dt);
};

struct Camera : public UniverseNode
{
    Camera();
    glm::mat4x4& getProjectionMatrix() const;

    float getFov() const;
    void setFov(float fov);

    float getWidth() const;
    void setWidth(float width);

    float getHeight() const;
    void setHeight(float height);

    float getNear() const;
    void setNear(float near);

    float getFar() const;
    void setFar(float far);

protected:
    virtual void calculateTransform() const = 0;

    float m_fov;
    float m_width;
    float m_height;
    float m_near;
    float m_far;
};
typedef std::shared_ptr<Camera> CameraPtr;

struct OrthoCamera : public Camera
{
    OrthoCamera();
protected:
    void calculateTransform() const override;
};

struct Spectator : public UniverseNode
{
   Spectator(const CameraPtr& camera);
   glm::mat4x4& getViewMatrix() const;
   const CameraPtr& getCamera() const;

protected:
   glm::vec3 m_position;
   glm::vec3 m_target;
    glm::vec3 m_up;
    CameraPtr m_camera;
};
typedef std::shared_ptr<Spectator> SpectatorPtr;

struct DrawingNode : public UniverseNode
{
    void draw(const glm::mat4x4& parenttr) const;
    ProgramPtr program() const;

protected:
    virtual void _draw(const glm::mat4x4& M) const;

    mutable ProgramPtr m_program;
    TexturePtr m_texture;
};

struct UniverseLayer : public DrawingNode
{
    UniverseLayer();
    SpectatorPtr spectator() const;

protected:
    void _draw(const glm::mat4x4&) const override {};

    SpectatorPtr m_spectator;
};
typedef std::shared_ptr<UniverseLayer> UniverseLayerPtr;

struct Universe : public std::list<UniverseLayerPtr>
{
    void update(float dt);
};

#endif /*  UNIVERSE_H */
