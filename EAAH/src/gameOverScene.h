#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "scene.h"
#include "menu.h"

class GameOverScene : public Scene
{
public:
    GameOverScene ();
    ~GameOverScene ();

    void update () override final;

    void onSwitchTo () override final;
    void onSwitchFrom () override final;

private:
    Menu menu;
};

#endif
