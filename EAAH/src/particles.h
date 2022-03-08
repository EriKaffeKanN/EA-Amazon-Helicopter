#ifndef PARTICLES_H_
#define PARTICLES_H_

#include <SFML/System.hpp>

#include "entity.h"

class Particles : public Entity
{
public:
    Particles(sf::Vector2<float> pos, sf::Vector2<float> size);
};

#endif
