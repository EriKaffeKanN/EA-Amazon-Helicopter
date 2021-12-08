#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
public:
    Entity(sf::Vector2<float> pos, sf::Vector2<float> size, const char* texturePath, sf::Vector2<int> frameSize, int animationSize);
    
    void LoadSpriteSheet();
    void draw();

    virtual void update();
    virtual void onCollision(Entity* other);
    virtual void updateAnimation();

    sf::Vector2<float> pos;
    sf::Vector2<float> velocity;
    sf::Vector2<float> size;
protected:
    float animationLength = 0.3f;
    float animationCounter = 0.f;
    int animationFrame;
    int animationSize;
private:
    const char* texturePath;
    sf::Vector2<int> animationFrameSize;
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif
