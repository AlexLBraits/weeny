#include <universe.h>
#include <visualiser.h>
#include <cache.h>
#include <singleton.h>

void UniverseNode::update(float dt)
{

}

void Universe::update(float dt)
{
    for(auto& ul : *this) ul->update(dt);
}

void UniverseLayer::update(float dt)
{
    m_root->update(dt);
}

DrawingNode::DrawingNode()
{
    m_program = Singleton<ResourceCache<ProgramPtr>>::getInstance().get("dummy");
    m_texture = Singleton<ResourceCache<TexturePtr>>::getInstance().get("dummy");
}
