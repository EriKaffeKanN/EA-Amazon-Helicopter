#include "splashScreenScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

SplashScreenScene::SplashScreenScene ()
    : Scene (SceneManager::Scenes::SPLASH_SCREEN,
            SceneManager::getBgPath (SceneManager::Scenes::SPLASH_SCREEN))
{
    this->elapsedTime = 0;
}

void SplashScreenScene::update ()
{
    elapsedTime += game.ft;
    if (elapsedTime >= 1)
    {
        SceneManager::popScene ();
        SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::MAIN_MENU));
        return;
    }

    game.window.draw (this->background);
    
}

void SplashScreenScene::onSwitchTo ()
{

}


void SplashScreenScene::onSwitchFrom ()
{

}
