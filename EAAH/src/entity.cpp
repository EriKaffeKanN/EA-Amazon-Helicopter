#include "entity.h"
#include "game.h"

#include <cmath>

Entity::Entity(sf::Vector2<float> pos, sf::Vector2<float> size, const char* texturePath, sf::Vector2<int> frameSize, int animationSize)
{
    this->pos = pos;
    this->size = size;
    this->texturePath = texturePath;
    this->animationFrameSize = frameSize;
    this->animationSize = animationSize;
    this->animationFrame = 0;
    this->velocity = {0.f, 0.f};
}

void Entity::draw()
{
    game.window.draw(this->sprite);
}

void Entity::update()
{
    this->pos += this->velocity;
    
    animationFrame %= animationSize; // Loop back to the first frame if you reach the end of the animation
    sf::IntRect framePosition(0, 0, animationFrameSize.x, animationFrameSize.y);
    framePosition.left = animationFrameSize.x * animationFrame;
    this->sprite.setTextureRect(framePosition);
    this->sprite.setPosition(pos.x, pos.y);
    this->updateAnimation();
}

void Entity::updateAnimation()
{
    animationCounter += game.ft;
    if(animationCounter > animationLength)
    {
        animationCounter = 0.f;
    }
    // Scary math that makes the animation run at constant speed and repeat itself after every "animationLength" seconds
    animationFrame = std::floor(animationCounter * animationSize/animationLength);
}

void Entity::onCollision(Entity* other)
{

}

void Entity::LoadSpriteSheet()
{
    if(!this->texture.loadFromFile(this->texturePath))
    {
        std::cerr << "Failed to retrieve " << this->texturePath << std::endl;
    }

    this->animationSize = this->animationSize;
    this->animationFrameSize = this->animationFrameSize;
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(
        0, 0, // Start at frame zero
        this->animationFrameSize.x, this->animationFrameSize.y
    ));
    float textureSizeX = this->texture.getSize().x;
    float textureSizeY = this->texture.getSize().y;
    this->sprite.setScale(
        animationSize * (size.x/textureSizeX), // Scale to fit specified dimensions
        size.y/textureSizeY
    );
}
