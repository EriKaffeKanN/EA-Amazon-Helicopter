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
    BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size, std::vector<Tree*>& trees);
    // ~BulldozerEntity() override final;

    void update() override final;
    void onCollision(GameScene::CollisionPacket packet) override final;

    enum class Behaviour
    {
        ROAM,
        HUNT,
        ATTACK,
        FLEE
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
    void flee();

    void changeBehaviour(Behaviour behaviour);

    void selectTarget();
    std::vector<Tree*>& treesRef; // so each bulldozer knows where each tree is
    Tree* targetTree;

    float behaviourTimer;

    // Roaming variables
    float roamTimer; // timer
    float timeUntilChangeDirection; // decides when to change direction or stop while roaming
    float timeUntilHunt; // decides when to start hunting trees
    float roamSpeed; // How many pixels / second the bulldozer moves each frame
    bool standStill;

    // Hunting variables
    float huntSpeed;

    // Attacking variables
    float attackTimer; // timer for destorying logs
    float timeUntilDestoryLog;
    float timeUntilRoam;

    // Fleeing variables
    float fleeSpeed;


    Behaviour currentBehaviour;
};

#endif
