#include "bombEntity.h"

BombEntity::BombEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/fertilizer.png", this->size, sf::Vector2<int>(74, 74), 1, 0.3f);
}

void BombEntity::update()
{
    this->pos.y += 1.f;
    Entity::update();
}