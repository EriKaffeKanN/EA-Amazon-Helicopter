#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "scene.h"

#include <SFML/Audio.hpp>

class Entity;
class PlayerEntity;
class Tree;

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void update() override final;

    void onSwitchTo() override final;
    void onSwitchFrom() override final;

    static const float groundLevel;
    static const float tileSize;

    struct CollisionPacket
    {
        enum
        {
            ENEMY,
            PLAYER,
            FERTILIZER,
            TREE
        } collider;
    };

    void checkCollisions ();
private:
    void spawnEntity(Entity* entity);
    void spawnEnemy(float posX);
    void spawnTree(Tree* tree, int tileX);
    void initializeWorld();
    void sweepEntities();
    bool isGameOver ();

    PlayerEntity* player;
    std::vector<Entity*> entities;
    std::vector<Tree*> trees;

    float bulldozerTimer = 0;
    float timeUntilSpawnBulldozer = 15.f;
};

#endif
