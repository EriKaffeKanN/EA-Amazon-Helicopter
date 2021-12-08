#include "playerEntity.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> velocity) : Entity(pos, velocity)
{
    // do stuff lol
}

void PlayerEntity::update()
{
    this->velocity.x += 0.01f;
    Entity::update();
}
