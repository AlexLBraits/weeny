#ifndef CACHE_H
#define CACHE_H

#include <texture.h>
#include <program.h>

#include <map>
#include <string>

extern
std::map<std::string, std::pair<const unsigned char*, unsigned int>> resources;

template <typename T>
struct ResourceCache : private std::map<std::string, T>
{
    T get(const std::string& key)
    {
        return T(0);
    }
    void drop(const std::string& key)
    {
        this->erase(key);
    }
};

template <>
struct ResourceCache<TexturePtr> : private std::map<std::string, TexturePtr>
{
    TexturePtr get(const std::string& key)
    {
        auto it = find(key);
        if(it != end())
        {
            return it->second;
        }

        auto rit = resources.find(key);
        if(rit != resources.end())
        {
            return (*this)[key] = TexturePtr(
                                      new Texture(
                                          rit->second.first, rit->second.second
                                      )
                                  );
        }

        return Texture::dummy();
    }
    void drop(const std::string& key)
    {
        erase(key);
    }
};

template <>
struct ResourceCache<ProgramPtr> : private std::map<std::string, ProgramPtr>
{
    ProgramPtr get(const std::string& key)
    {
        auto it = find(key);
        if(it != end())
        {
            return it->second;
        }

        auto vrit = resources.find("v" + key + ".glsl");
        auto frit = resources.find("f" + key + ".glsl");
        if(vrit != resources.end() && frit != resources.end())
        {
            return (*this)[key] = ProgramPtr(
                                      new Program(
                                          vrit->second.first, vrit->second.second,
                                          frit->second.first, frit->second.second
                                      )
                                  );
        }

        return Program::dummy();
    }
    void drop(const std::string& key)
    {
        erase(key);
    }
};

#endif /* CACHE_H */
