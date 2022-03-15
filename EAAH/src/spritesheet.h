#ifndef SPRITESHEET_H_
#define SPRITESHEET_H_

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "util.h"

class SpriteSheet
{
public:
    SpriteSheet(const char* texturePath, sf::Vector2<float> size, sf::Vector2<int> frameSize, int* animationSizes, int numberOfAnimations, float animationLength);
    ~SpriteSheet();
    void loadSprite(const sf::Vector2<float>& pos, Direction direction = Direction::LEFT);
    void update(sf::Vector2<float>& pos);
    void setDirection(Direction dir);
    void switchDirection();
    Direction getDirection();

    sf::Texture texture;
    sf::Sprite sprite;

    int currentFrame;
    int currentAnimation;
    int numberOfAnimations; // The amount of animations in the spritesheet
    int* animationSizes; // The amount of frames in each animation in the spritesheet
    float offsetX; // This exists because I can't set the origin properly.
    float animationLength; // The length of the animation in seconds
    float animationCounter; // How far along the animation has played
    sf::Vector2<float> size; // The size of the visible sprite
    sf::Vector2<int> frameSize; // The size of each frame in the texture
    const char* texturePath;
};

#endif
