#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>

struct Texture;
typedef std::shared_ptr<Texture> TexturePtr;

struct Texture
{
    Texture();
    Texture(const unsigned char* src, unsigned int size);
    ~Texture();
    unsigned int id() const;

    static TexturePtr dummy();

private:
    unsigned int m_id;
    static TexturePtr m_dummy;
};

#endif /* TEXTURE_H */
