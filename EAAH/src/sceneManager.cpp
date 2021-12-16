#include "sceneManager.h"
#include "splashScreenScene.h"
#include "mainMenuScene.h"
#include "gameScene.h"

#include <iostream>

std::deque<Scene*> SceneManager::sceneQueue {};

// TODO: Can these initializations be moved somewhere to make it clearer
// where they are located?
std::unordered_map<SceneManager::Scenes, SceneManager::SceneSettings> SceneManager::defaultSceneSettings = {
    {SceneManager::Scenes::SPLASH_SCREEN,
     SceneManager::SceneSettings {"../resources/backgrounds/splashScreenBg.png"}},
    {SceneManager::Scenes::MAIN_MENU,
     SceneManager::SceneSettings {"../resources/backgrounds/mainMenuBg.png"}},
    {SceneManager::Scenes::GAME,
     SceneManager::SceneSettings {"../resources/backgrounds/gameBg.png"}}
};

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

const char* SceneManager::getBgPath (SceneManager::Scenes scene)
{
    return defaultSceneSettings [scene].bgImagePath.c_str ();
}

void SceneManager::setBgPath (Scenes scene, std::string path)
{
    defaultSceneSettings [scene].bgImagePath = path;
}
