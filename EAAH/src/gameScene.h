#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "scene.h"
#include "entity.h"
#include "playerEntity.h"
#include "tree.h"

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void update() override final;

    void onSwitchTo() override final;
    void onSwitchFrom() override final;

    static const float groundLevel;
private:
    void spawnEntity(Entity* entity);
    void spawnTree(Tree* tree, int tileX);

    PlayerEntity* player;
    std::vector<Entity*> entities;
    std::vector<Tree*> trees;

    const float tileSize = 720.f;
};

#endif
