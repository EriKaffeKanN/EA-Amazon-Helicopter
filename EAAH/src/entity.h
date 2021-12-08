#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity
{
public:
    Entity(sf::Vector2<float> pos, sf::Vector2<float> velocity);
    
    void LoadSprite(const char* texturePath);
    void draw();

    virtual void update();
    virtual void onCollision(Entity* other);

    sf::Vector2<float> pos;
    sf::Vector2<float> velocity;
    sf::Vector2<float> size;
private:
    sf::Texture texture;
    sf::Sprite sprite;
};
#endif
