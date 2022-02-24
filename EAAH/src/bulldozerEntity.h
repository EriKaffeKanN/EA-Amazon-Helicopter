#ifndef BULLDOZERENTITY_H_
#define BULLDOZERENTITY_H_

#include <SFML/System.hpp>

#include "entity.h"

class BulldozerEntity : public Entity
{
public:
    BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size);

    void update() override final;

    enum class Behaviour
    {
        ROAM,
        HUNT,
        ATTACK
    };
    enum class Animations
    {
        MOVING,
        DIGGING,
        IDLE
    };
private:
    void roam();
    void hunt();
    void attack();

    // Roaming variables
    float roamTimer = 0.f; // timer
    float timeUntilChangeDirection = 2.f; // decides when to change direction or stop while roaming
    float timeUntilHunt = 15.f; // decides when to start hunting trees
    float roamSpeed = 0.2f; // How many pixels / second the bulldozer moves each frame

    bool standStill = false;

    Behaviour currentBehaviour;
};

#endif