#ifndef PAUSE_MENU_SCENE_H
#define PAUSE_MENU_SCENE_H

#include "scene.h"
#include "menu.h"

class PauseMenuScene : public Scene
{
public:
    PauseMenuScene ();

    void update () override final;

    void onSwitchTo () override final;
    void onSwitchFrom () override final;
private:
    Menu menu;
};

#endif
