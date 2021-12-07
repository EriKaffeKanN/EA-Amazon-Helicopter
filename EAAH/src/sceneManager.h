#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "scene.h"

#include <deque>

class SceneManager
{
public:
    enum class Scenes
    {
        SPLASH_SCREEN,
        MAIN_MENU,
        GAME
    };

    static void pushScene (Scene* scene);
    static void popScene ();
    static bool returnToScene (Scenes scene);
    static Scene* createScene (Scenes scene);

    static std::deque<Scene*> sceneQueue;
};

#endif // SCENEMANAGER_H
