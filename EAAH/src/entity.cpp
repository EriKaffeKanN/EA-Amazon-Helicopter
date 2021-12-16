#include "entity.h"
#include "game.h"

#include <cmath>

Entity::Entity(sf::Vector2<float> pos, sf::Vector2<float> size)
{
    this->pos = pos;
    this->size = size;
    this->velocity = {0.f, 0.f};
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

void Entity::onCollision(Entity* other)
{

}

void Entity::loadSprite()
{
    spriteSheet->loadSprite();
}
