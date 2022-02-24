#include "playerEntity.h"
#include "game.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/helicopter.png", size, sf::Vector2<int>(40, 22), 7, 0.3f);
}

void PlayerEntity::update()
{
    this->velocity.x = 0;
    // Handle input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->velocity.x = 0.3f;
        this->spriteSheet->setDirection(Direction::RIGHT);

    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->velocity.x = -0.3f;
        this->spriteSheet->setDirection(Direction::LEFT);
    }

    if(bombCooldown > 0)
    {
        bombCooldown -= game.ft;
    }

    Entity::update();
}

void PlayerEntity::updateAnimation()
{
    // Do epic stuff
}