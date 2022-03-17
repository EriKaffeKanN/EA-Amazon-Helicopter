#ifndef PLAYER_H_
#define PLAYER_H_

#include "entity.h"
#include "gameScene.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class PlayerEntity: public Entity
{
public:
    PlayerEntity(sf::Vector2<float> pos, sf::Vector2<float> velocity);

    void update() override final;
    void onCollision(GameScene::CollisionPacket packet) override final;

    float bombCooldown = 0;

    sf::Sound spinSound;

private:
    float moveSpeed = 160.f;
};

#endif
