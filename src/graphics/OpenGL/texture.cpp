#include <texture.h>
#include <graphics.h>

TexturePtr Texture::m_dummy;

Texture::Texture()
    : m_id(0)
{
}

Texture::Texture(const unsigned char* src, unsigned int size)
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
        glGenerateMipmap(GL_TEXTURE_2D);

        // Black/white checkerboard
        float pixels[] =
        {
            0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
        };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
    }
    return m_dummy;
}

unsigned int Texture::id() const
{
    return m_id;
}
