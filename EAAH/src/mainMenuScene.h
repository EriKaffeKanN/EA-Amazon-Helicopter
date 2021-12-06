#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "scene.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene ();

    void update () override final;

    void onSwitchTo () override final;
    void onSwitchFrom () override final;
private:
};

#endif
