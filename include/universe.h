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
    UniverseNode();

    virtual void update(float dt);

    glm::vec3 translation() const;
    void setTranslation(const glm::vec3 &translation);
    glm::vec3 rotation() const;
    void setRotation(const glm::vec3 &rotation);
    glm::vec3 scale() const;
    void setScale(const glm::vec3 &scale);

    glm::mat4x4 transform() const;
    void setTransform(const glm::mat4x4 &value) const;

protected:
    virtual void update_this(float dt);
    virtual void calculateTransform() const;

    glm::vec3 m_translation;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;

private:
    mutable int u_dirty_transform;
    mutable glm::mat4x4 u_transform;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The Camera struct
///
struct Camera : public UniverseNode
{
    Camera();

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
/// \brief The PerspectiveCamera struct
///
struct PerspectiveCamera : public Camera
{
    PerspectiveCamera();
protected:
    void calculateTransform() const override;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The DrawingNode struct
///
struct DrawingNode : public UniverseNode
{
    DrawingNode();
    virtual void draw(const glm::mat4x4& parenttr) const;
    virtual void resize(int width, int height);
    TexturePtr texture() const;
    ProgramPtr program() const;

    glm::vec3 dimensions() const;
    void setDimensions(const glm::vec3 &dimensions);

protected:
    virtual void draw_this(const glm::mat4x4& M) const;
    virtual void resize_this(int width, int height);

    glm::vec3 m_dimensions;

    mutable std::vector<glm::vec3> m_vertices;
    mutable std::vector<glm::vec2> m_uvs;
    mutable std::vector<glm::vec4> m_colors;

    mutable TexturePtr m_texture;
    mutable ProgramPtr m_program;
};
////////////////////////////////////////////////////////////////////////////////
/// \brief The Spectator struct
///
struct Spectator : public DrawingNode
{
    Spectator(const CameraPtr& camera);

    CameraPtr camera() const;
    void setCamera(const CameraPtr &camera);

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
    glm::mat4x4 getProjectViewMatrix() const;
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

    const Window& window() const;

protected:
    mutable Window m_window;
};

#endif /*  UNIVERSE_H */
