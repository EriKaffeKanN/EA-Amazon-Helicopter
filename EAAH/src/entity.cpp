#include "entity.h"
#include "game.h"

#include <cmath>

Entity::Entity(sf::Vector2<float> pos, sf::Vector2<float> size)
{
    this->pos = pos;
    this->size = size;
    this->velocity = {0.f, 0.f};
    this->dead = false;
}

Entity::~Entity()
{
    delete spriteSheet;
}

void Entity::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (this->spriteSheet->sprite);
}

void Entity::update()
{
    this->pos += this->velocity;
    spriteSheet->update(pos);
}

int Entity::getTilePos()
{
    return std::floor(pos.x / GameScene::tileSize);
}

void Entity::onCollision(GameScene::CollisionPacket packet)
{

}

void Entity::loadSprite()
{
    spriteSheet->loadSprite();
}
