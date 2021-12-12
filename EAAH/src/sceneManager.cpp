#include "sceneManager.h"
#include "splashScreenScene.h"
#include "mainMenuScene.h"
#include "gameScene.h"

#include <iostream>

std::deque<Scene*> SceneManager::sceneQueue {};

void SceneManager::pushScene (Scene* scene)
{
    sceneQueue.push_back (scene);
}

void SceneManager::popScene ()
{
    delete sceneQueue.back ();
    sceneQueue.pop_back ();
    if (!sceneQueue.empty ())
    {
        sceneQueue.back ()->onSwitchTo ();
    }
}

bool SceneManager::returnToScene (SceneManager::Scenes scene)
{
    for (auto it = sceneQueue.begin (); it != sceneQueue.end (); it++)
    {
        if ((*it)->getType () == scene)
        {
            while (it != sceneQueue.end ())
            {
                delete sceneQueue.back ();
                sceneQueue.pop_back ();
            }

            sceneQueue.back ()->onSwitchTo ();
            return true;
        }
    }

    return false;
}

Scene* SceneManager::createScene (SceneManager::Scenes scene)
{
    switch (scene)
    {
        case SceneManager::Scenes::SPLASH_SCREEN:
            return new SplashScreenScene ();
            break;
        case SceneManager::Scenes::MAIN_MENU:
            return new MainMenuScene ();
            break;
        case SceneManager::Scenes::GAME:
            return new GameScene ();
            break;
    }
    // Should never reach
    return nullptr;
}

Scene* SceneManager::currScene ()
{
    if (!sceneQueue.empty ())
    {
        return sceneQueue.back ();
    }
    return nullptr;
}
}
