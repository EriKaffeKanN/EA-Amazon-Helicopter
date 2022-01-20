#include "bombEntity.h"

BombEntity::BombEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/fertilizer.png", this->size, sf::Vector2<int>(74, 74), 1, 0.3f);
}

void BombEntity::update()
{
    this->velocity.y += 0.1f;
    if(this->velocity.y > 5.f)
    {
        this->velocity.y = 5.f;
    }
    Entity::update();
}