#include "spritesheet.h"
#include "game.h"
#include "util.h"

#include <iostream>

// I apologize to anyone reading this file

SpriteSheet::SpriteSheet(const char* texturePath, sf::Vector2<float> size, sf::Vector2<int> frameSize, int* animationSizes, int numberOfAnimations, float animationLength)
{
    this->size = size;
    this->texturePath = texturePath;
    this->frameSize = frameSize;
    this->animationSizes = animationSizes;
    this->animationLength = animationLength;
    this->animationCounter = 0;
    this->currentFrame = 0;
    this->currentAnimation = 0;
    this->numberOfAnimations = numberOfAnimations;
}

SpriteSheet::~SpriteSheet()
{
    delete[] this->animationSizes;
}

void SpriteSheet::loadSprite(const sf::Vector2<float>& pos)
{
    if(!this->texture.loadFromFile(this->texturePath))
    {
        std::cerr << "Failed to retrieve " << this->texturePath << std::endl;
    }

    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect(sf::IntRect(
        0, 0, // Start at frame zero
        this->frameSize.x, this->frameSize.y
    ));
    float textureSizeX = this->texture.getSize().x;
    float textureSizeY = this->texture.getSize().y;
    int longestTexture = UtilFunctions::getMaxValue(animationSizes, numberOfAnimations); // used to determine the size of the scaled texture since the longest texture decoes the width of the image
    float scaledTextureX = longestTexture * (size.x/textureSizeX);
    float scaledTextureY = numberOfAnimations * (size.y/textureSizeY);
    this->sprite.setScale(
        scaledTextureX, // Scale to fit specified dimensions
        scaledTextureY
    );

    this->sprite.setPosition(pos.x + this->offsetX, pos.y);
}

void SpriteSheet::update(sf::Vector2<float>& pos)
{
    currentFrame %= animationSizes[currentAnimation]; // Loop back to the first frame if you reach the end of the animation
    sf::IntRect framePosition(0, 0, frameSize.x, frameSize.y);
    framePosition.left = frameSize.x * currentFrame;
    framePosition.top = frameSize.y * currentAnimation;
    this->sprite.setTextureRect(framePosition);
    this->sprite.setPosition(pos.x + this->offsetX, pos.y);

    animationCounter += game.ft;
    if(animationCounter > animationLength)
    {
        animationCounter = 0.f;
    }
    // Scary math that makes the animation run at constant speed and repeat itself after every "animationLength" seconds
    currentFrame = std::floor(animationCounter * animationSizes[currentAnimation]/animationLength);
}

void SpriteSheet::setDirection(Direction dir)
{
    switch (dir)
    {
    case Direction::LEFT:
        this->sprite.setScale(
            std::abs(this->sprite.getScale().x),
            this->sprite.getScale().y
            );
        this->offsetX = 0;
        break;
    case Direction::RIGHT:
        this->sprite.setScale(
            -std::abs(this->sprite.getScale().x),
            this->sprite.getScale().y
            );
        this->offsetX = this->size.x;
        break;
    }
}

Direction SpriteSheet::getDirection()
{
    if(this->sprite.getScale().x > 0)
    {
        return Direction::LEFT;
    }
    else
    {
        return Direction::RIGHT;
    }
}

void SpriteSheet::switchDirection()
{
    if(this->getDirection() == Direction::LEFT)
        this->setDirection(Direction::RIGHT);
    this->setDirection(Direction::LEFT);
}
