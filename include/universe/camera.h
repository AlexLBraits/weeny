#ifndef UNIVERSE_CAMERA_H
#define UNIVERSE_CAMERA_H

#include <universe/node.h>
#include <memory>

////////////////////////////////////////////////////////////////////////////////
/// \brief The Camera struct
///
class Camera : public Node
{
public:
    Camera();

    float fov() const;
    void setFov(float fov);

    float width() const;
    void setWidth(float width);

    float height() const;
    void setHeight(float height);

    float near() const;
    void setNear(float near);

    float far() const;
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
class OrthoCamera : public Camera
{
public:
    OrthoCamera();

protected:
    void calculateTransform() const override;
};

////////////////////////////////////////////////////////////////////////////////
/// \brief The PerspectiveCamera struct
///
class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera();

protected:
    void calculateTransform() const override;
};

#endif /* UNIVERSE_CAMERA_H */
