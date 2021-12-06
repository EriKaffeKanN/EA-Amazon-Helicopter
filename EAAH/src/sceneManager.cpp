#include "sceneManager.h"
#include "splashScreenScene.h"
#include "mainMenuScene.h"

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
    }
    // Should never reach
    return nullptr;
}
