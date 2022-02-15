#include "bulldozerEntity.h"

BulldozerEntity::BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/bulldozer_moving.png", size, sf::Vector2<int>(64, 64));
}