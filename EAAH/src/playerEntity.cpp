#include "playerEntity.h"
#include "game.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size, "../resources/textures/bulldozer_moving.png", sf::Vector2<int>(64, 64), 3)
{
    // do stuff lol
}

void PlayerEntity::update()
{
    // Handle input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->velocity.x = 0.03f;
    }
    Entity::update();
}

void PlayerEntity::updateAnimation()
{
    Entity::updateAnimation();
}