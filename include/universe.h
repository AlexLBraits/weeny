#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <list>
#include <vector>
#include <hierarchy.h>
#include <types.h>
#include <program.h>
#include <texture.h>
#include <widget.h>

////////////////////////////////////////////////////////////////////////////////
/// \brief The UniverseNode struct
///
struct UniverseNode : public Hierarchy<UniverseNode>
{
    virtual void update(float dt);

protected:
    virtual void update_this(float dt);
    virtual void calculateTransform() const;

    mutable glm::mat4x4 u_transform;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The Camera struct
///
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
    float m_fov;
    float m_width;
    float m_height;
    float m_near;
    float m_far;
};
typedef std::shared_ptr<Camera> CameraPtr;
////////////////////////////////////////////////////////////////////////////////
/// \brief The OrthoCamera struct
///
struct OrthoCamera : public Camera
{
    OrthoCamera();
protected:
    void calculateTransform() const override;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The DrawingNode struct
///
struct DrawingNode : public UniverseNode
{
    virtual void draw(const glm::mat4x4& parenttr) const;
    virtual void resize(int width, int height);
    ProgramPtr program() const;

    glm::vec3 position() const;
    void setPosition(const glm::vec3 &position);

protected:
    virtual void draw_this(const glm::mat4x4& M) const;
    virtual void resize_this(int width, int height);

    mutable std::vector<glm::vec3> m_vertices;
    glm::vec3 m_position;

    mutable ProgramPtr m_program;
    TexturePtr m_texture;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The Spectator struct
///
struct Spectator : public DrawingNode
{
    Spectator(const CameraPtr& camera);
    glm::mat4x4& getViewMatrix() const;
    CameraPtr camera() const;

protected:
    void calculateTransform() const override;

    glm::vec3 m_target;
    glm::vec3 m_up;
    CameraPtr m_camera;
};
typedef std::shared_ptr<Spectator> SpectatorPtr;
////////////////////////////////////////////////////////////////////////////////
/// \brief The UniverseLayer struct
///
struct UniverseLayer : public DrawingNode
{
    UniverseLayer();
    void draw(const glm::mat4x4&) const override;
    glm::mat4x4& getProjectViewMatrix() const;
    SpectatorPtr spectator() const;

protected:
    void calculateTransform() const override;
    void draw_this(const glm::mat4x4&) const override;;
    void resize_this(int width, int height) override;

    SpectatorPtr m_spectator;
};
typedef std::shared_ptr<UniverseLayer> UniverseLayerPtr;
////////////////////////////////////////////////////////////////////////////////
/// \brief The Universe struct
///
typedef std::list<UniverseLayerPtr> Layers;
struct Universe : protected Layers
{
    void initialize();
    void resize(int width, int height);
    void update(float dt);
    void draw() const;

    Layers::iterator begin() {return Layers::begin(); }
    Layers::iterator end() {return Layers::end(); }
    Layers::const_iterator begin() const {return Layers::cbegin(); }
    Layers::const_iterator end() const {return Layers::cend(); }
    void push_back(UniverseLayerPtr layer);

protected:
    mutable Widget m_window;
};

#endif /*  UNIVERSE_H */
