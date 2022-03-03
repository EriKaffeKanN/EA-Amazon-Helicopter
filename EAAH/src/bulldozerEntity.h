#ifndef BULLDOZERENTITY_H_
#define BULLDOZERENTITY_H_

#include <SFML/System.hpp>
#include <memory>

#include "entity.h"
#include "tree.h"
#include "gameScene.h"

class BulldozerEntity : public Entity
{
public:
    BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size, std::vector<Tree*>* trees);
    ~BulldozerEntity() override final;

    void update() override final;
    void onCollision(GameScene::CollisionPacket packet) override final;

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

    void changeBehaviour(Behaviour behaviour);

    void selectTarget();
    std::vector<Tree*>* treesRef; // so each bulldozer knows where each tree is
    Tree* targetTree;

    float behaviourTimer = 0.f;

    // Roaming variables
    float roamTimer = 0.f; // timer
    float timeUntilChangeDirection = 2.f; // decides when to change direction or stop while roaming
    float timeUntilHunt = 7.f; // decides when to start hunting trees
    float roamSpeed = 0.2f; // How many pixels / second the bulldozer moves each frame
    bool standStill = false;

    // Hunting variables
    float huntSpeed = 0.5f;

    // Attacking variables
    float attackTimer = 0.f; // timer for destorying logs
    float timeUntilDestoryLog = 0.8f;
    float timeUntilRoam = 3.f;


    Behaviour currentBehaviour;
};

#endif