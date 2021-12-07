#include "playerEntity.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> velocity) : Entity(pos, velocity)
{
    // do stuff lol
}

// This is never called. I should fix that.
void PlayerEntity::update()
{
    this->velocity.x += 1;
    Entity::update();
}