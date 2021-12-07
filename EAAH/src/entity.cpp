#include "entity.h"
#include "game.h"

Entity::Entity(sf::Vector2<float> pos, sf::Vector2<float> size)
{
    this->pos = pos;
    this->size = size;
    this->velocity = {0.f, 0.f};
}

void Entity::draw()
{
    game.window.draw(this->sprite);
}

void Entity::update()
{
    this->pos += this->velocity;
    this->sprite.setPosition(pos.x, pos.y);
}

void Entity::onCollision()
{

}

// Textures are not loaded in the constructor because
// they have to be loaded after being spawned (otherwise we get memory issues)
void Entity::LoadSprite(const char* texturePath)
{
    if(!texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to retrieve " << texturePath << std::endl;
    }

    this->sprite.setTexture(texture);
    float textureSizeX = this->texture.getSize().x;
    float textureSizeY = this->texture.getSize().y;
    this->sprite.setScale(
        size.x/textureSizeX, // Scale to fit specified dimensions
        size.y/textureSizeY
    );
}