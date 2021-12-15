#ifndef ENTITY_H_
#define ENTITY_H_

#include "spritesheet.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
public:
    Entity(sf::Vector2<float> pos, sf::Vector2<float> size);
    ~Entity();
    
    void draw();
    
    virtual void loadSprite();
    virtual void update();
    virtual void onCollision(Entity* other);

    sf::Vector2<float> pos;
    sf::Vector2<float> velocity;
    sf::Vector2<float> size;
protected:
    SpriteSheet* spriteSheet;
};
#endif
