#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <list>

struct UniverseLayer
{

};

struct Universe : public std::list<UniverseLayer>
{
    void update(float dt);
};

#endif /*  UNIVERSE_H */
