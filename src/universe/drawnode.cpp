#include <universe/drawnode.h>
#include <base/singleton.h>
#include <base/cache.h>

///
/// \brief DrawingNode::draw
/// \param parenttr
///
DrawNode::DrawNode()
{
}
///
/// \brief DrawingNode::draw
/// \param parenttr
///
void DrawNode::draw(const glm::mat4x4& PV) const
{
    draw_this(PV);
    for(const auto& dnode : *this) ((const DrawNode&)dnode).draw(PV);
}
///
/// \brief DrawingNode::_draw
/// \param M
///
void DrawNode::draw_this(const glm::mat4x4& M) const
{
}
///
/// \brief DrawingNode::texture
/// \return
///
TexturePtr DrawNode::texture() const
{
    if(!m_texture)
    {
        m_texture = Singleton<ResourceCache<TexturePtr>>::getInstance().get("dummy");
    }
    return m_texture;
}

void DrawNode::setTexture(const TexturePtr &ptr)
{
     m_texture = ptr;
}
///
/// \brief DrawingNode::program
/// \return
///
ProgramPtr DrawNode::program() const
{
    if(!m_program)
    {
        DrawNode* node = dynamic_cast<DrawNode*>(parentNode());
        while(node && !(m_program = node->m_program))
        {
            node = dynamic_cast<DrawNode*>(node->parentNode());
        }
        if(!m_program)
        {
            m_program = Singleton<ResourceCache<ProgramPtr>>::getInstance().get("dummy");
        }
    }
    return m_program;
}
