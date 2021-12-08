#ifndef SCENE_H
#define SCENE_H

#include "sceneManager.h"

class Scene
{
public:
    Scene (SceneManager::Scenes type);
    virtual ~Scene () { };

    virtual void update () = 0;

    // These are not for when the scenes are pushed/popped, but for when they
    // are returned to from some other scene (like from the pause menu)
    virtual void onSwitchTo () = 0;
    virtual void onSwitchFrom () = 0;

    SceneManager::Scenes getType ();

private:
    SceneManager::Scenes sceneType;
    // Entities and other stuff
};

#endif
