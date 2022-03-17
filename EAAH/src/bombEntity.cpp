#include "bombEntity.h"
#include "game.h"

BombEntity::BombEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    this->spriteSheet = new SpriteSheet("../resources/textures/fertilizer.png", this->size, sf::Vector2<int>(74, 74), new int[1]{1}, 1, 0.3f);
}

void BombEntity::update()
{
    this->velocity.y += this->acceleration * game.ft;
    if(this->velocity.y > 2.f)
    {
        this->velocity.y = 2.f;
    }
    Entity::update();
}

void BombEntity::onCollision(GameScene::CollisionPacket packet)
{
    if(packet.collider == GameScene::CollisionPacket::TREE ||
       packet.collider == GameScene::CollisionPacket::ENEMY)
    {
        this->dead = true;
    }
}
