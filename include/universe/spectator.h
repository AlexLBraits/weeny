#ifndef UNIVERSE_SPECTATOR_H
#define UNIVERSE_SPECTATOR_H

#include <universe/node.h>
#include <universe/camera.h>

class Spectator : public Node
{
public:
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

#endif /* UNIVERSE_SPECTATOR_H */
