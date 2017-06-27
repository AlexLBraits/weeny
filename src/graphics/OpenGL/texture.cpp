#include <texture.h>
#include <graphics.h>

TexturePtr Texture::m_dummy;

Texture::Texture()
    : m_id(0), m_used_unit(-1)
{
}

Texture::Texture(const unsigned char *src, unsigned int size)
    : Texture()
{
}

Texture::~Texture()
{
    GLuint id = m_dummy->m_id;
    if(glIsTexture(id)) glDeleteTextures(1, &id);
}

TexturePtr Texture::dummy()
{
    if(!m_dummy)
    {
        m_dummy = TexturePtr(new Texture());

        GLuint id;
        glGenTextures(1, &id);
        m_dummy->m_id = id;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        glGenerateMipmap(GL_TEXTURE_2D);

        // Black/white checkerboard
        float pixels[] =
        {
            0.0f, 0.0f, 0.0f, 0.5f,   1.0f, 1.0f, 1.0f, 0.5f,
            1.0f, 1.0f, 1.0f, 0.5f,   0.0f, 0.0f, 0.0f, 0.5f
        };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_FLOAT, pixels);
    }
    return m_dummy;
}

unsigned int Texture::id() const
{
    return m_id;
}

void Texture::bind(int texture_unit) const
{
    if(m_used_unit != texture_unit)
    {
        m_used_unit = texture_unit;
        glActiveTexture(GL_TEXTURE0 + m_used_unit);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
}

void Texture::unbind() const
{
    m_used_unit = -1;
}

