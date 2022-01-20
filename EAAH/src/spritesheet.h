#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "util.h"

class SpriteSheet
{
public:
    SpriteSheet(const char* texturePath, sf::Vector2<float> size, sf::Vector2<int> frameSize, int animationSize, float animationLength);
    void loadSprite();
    void update(sf::Vector2<float>& pos);
    void setDirection(Direction dir);

    sf::Texture texture;
    sf::Sprite sprite;

    int currentFrame;
    int animationSize;
    float offsetX; // This exists because I can't set the origin properly.
    float animationLength; // The length of the animation in seconds
    float animationCounter; // How far along the animation has played
    sf::Vector2<float> size; // The size of the visible sprite
    sf::Vector2<int> frameSize; // The size of each frame in the texture
    const char* texturePath;
};

#endif