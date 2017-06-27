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
    void bind(int texture_unit = 0) const;
    void unbind() const;

    static TexturePtr dummy();

private:
    unsigned int m_id;
    mutable int m_used_unit;
    static TexturePtr m_dummy;
};

#endif /* TEXTURE_H */
