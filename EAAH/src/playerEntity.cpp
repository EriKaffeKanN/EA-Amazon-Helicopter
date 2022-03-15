#include "playerEntity.h"
#include "game.h"

PlayerEntity::PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/helicopter.png", size, sf::Vector2<int>(40, 22), new int[1]{7}, 1, 0.3f);

    this->spinSound.setBuffer (game.sfx.helicopterSpinSound);
    this->spinSound.setLoop (true);
    this->spinSound.play ();
}

void PlayerEntity::update()
{

    this->velocity.x = 0;
    // Handle input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->velocity.x = this->moveSpeed * game.ft;
        this->spriteSheet->setDirection(Direction::RIGHT);

    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->velocity.x = -this->moveSpeed * game.ft;
        this->spriteSheet->setDirection(Direction::LEFT);
    }

    if(bombCooldown > 0)
    {
        bombCooldown -= game.ft;
    }

    Entity::update();
}
void PlayerEntity::loadSprite ()
{
    this->spriteSheet->loadSprite (this->pos, Direction::RIGHT);
}

void PlayerEntity::updateAnimation()
{
    // Do epic stuff
}
