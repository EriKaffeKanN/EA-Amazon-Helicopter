#ifndef ENTITY_H_
#define ENTITY_H_

#include "spritesheet.h"
#include "gameScene.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Entity : public sf::Drawable
{
public:
    Entity(sf::Vector2<float> pos, sf::Vector2<float> size);
    virtual ~Entity();

    void loadSprite();
    virtual void update();
    virtual void onCollision(GameScene::CollisionPacket packet);

    virtual int getTilePos();

    sf::Vector2<float> pos;
    sf::Vector2<float> velocity;
    sf::Vector2<float> size;

    bool dead;

protected:
    SpriteSheet* spriteSheet;

private:
    void draw (sf::RenderTarget&, sf::RenderStates states) const override;
};
#endif
