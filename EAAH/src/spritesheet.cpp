#include "spritesheet.h"
#include "game.h"

#include <iostream>

SpriteSheet::SpriteSheet(const char* texturePath, sf::Vector2<float> size, sf::Vector2<int> frameSize, int animationSize, float animationLength)
{
    this->size = size;
    this->texturePath = texturePath;
    this->frameSize = frameSize;
    this->animationSize = animationSize;
    this->animationLength = animationLength;
    this->animationCounter = 0;
    this->currentFrame = 0;
}

void SpriteSheet::loadSprite()
{
    if(!this->texture.loadFromFile(this->texturePath))
    {
        std::cerr << "Failed to retrieve " << this->texturePath << std::endl;
    }

    this->animationSize = this->animationSize;
    this->frameSize = this->frameSize;
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(
        0, 0, // Start at frame zero
        this->frameSize.x, this->frameSize.y
    ));
    float textureSizeX = this->texture.getSize().x;
    float textureSizeY = this->texture.getSize().y;
    this->sprite.setScale(
        animationSize * (size.x/textureSizeX), // Scale to fit specified dimensions
        size.y/textureSizeY
    );
    std::cout << this->sprite.getTexture() << std::endl;
}

void SpriteSheet::update(sf::Vector2<float>& pos)
{
    currentFrame %= animationSize; // Loop back to the first frame if you reach the end of the animation
    sf::IntRect framePosition(0, 0, frameSize.x, frameSize.y);
    framePosition.left = frameSize.x * currentFrame;
    this->sprite.setTextureRect(framePosition);
    this->sprite.setPosition(pos.x, pos.y);

    animationCounter += game.ft;
    if(animationCounter > animationLength)
    {
        animationCounter = 0.f;
    }
    // Scary math that makes the animation run at constant speed and repeat itself after every "animationLength" seconds
    currentFrame = std::floor(animationCounter * animationSize/animationLength);

    std::cout << &texture << std::endl;
}