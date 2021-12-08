#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "scene.h"
#include "entity.h"

#include <memory>

class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    void update() override final;

    void onSwitchTo() override final;
    void onSwitchFrom() override final;
private:
    void spawnEntity(Entity* entity);

    std::vector<Entity*> entities;
};

#endif
