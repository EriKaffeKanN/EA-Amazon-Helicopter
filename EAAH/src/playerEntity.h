#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class PlayerEntity: public Entity
{
public:
    PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> velocity);

    void updateAnimation();

    void loadSprite() override final;
    void update() override final;
};

#endif
