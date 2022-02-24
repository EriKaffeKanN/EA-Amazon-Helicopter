#ifndef BOMBENTITY_H_
#define BOMBENTITY_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "entity.h"

class BombEntity : public Entity
{
public:
    BombEntity(sf::Vector2<float> pos, sf::Vector2<float> size);

    void update() override final;
    void onCollision(GameScene::CollisionPacket packet) override final;
};

#endif
