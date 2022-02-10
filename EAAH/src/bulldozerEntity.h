#ifndef BULLDOZERENTITY_H_
#define BULLDOZERENTITY_H_

#include <SFML/System.hpp>

#include "entity.h"

class BulldozerEntity : public Entity
{
public:
    BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size);

    void update() override final;
};

#endif