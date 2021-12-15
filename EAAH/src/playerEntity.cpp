#include "playerEntity.h"
#include "game.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/bulldozer_moving.png", this->size, sf::Vector2<int>(64, 64), 3, 0.3f);
}

void PlayerEntity::loadSprite()
{

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
    // Do epic stuff
}