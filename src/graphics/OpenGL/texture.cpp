#include <texture.h>
#include <graphics.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint create_texture(const unsigned char* pixels, int width, int height)
{
    GLuint id;
    glGenTextures(1, &id);

    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return id;
}

TexturePtr Texture::m_dummy;

Texture::Texture()
    : m_id(0), m_used_unit(-1)
{
}

Texture::Texture(const unsigned char *src, unsigned int size)
    : Texture()
{
    int width, height, channels_in_file;
    unsigned char* pixels = stbi_load_from_memory(
                src,
                size,
                &width,
                &height,
                &channels_in_file,
                4
                );

    m_id = create_texture(pixels, width, height);

    stbi_image_free(pixels);
}

Texture::~Texture()
{
    GLuint id = m_id;
    if(glIsTexture(id)) glDeleteTextures(1, &id);
}

TexturePtr Texture::dummy()
{
    if(!m_dummy)
    {
        static unsigned char pixels[] =
        {
            0x00, 0x00, 0x00, 0x7f,   0xff, 0xff, 0xff, 0x7f,
            0xff, 0xff, 0xff, 0x7f,   0x00, 0x00, 0x00, 0x7f
        };

        m_dummy = TexturePtr(new Texture());
        m_dummy->m_id = create_texture(pixels, 2, 2);
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

