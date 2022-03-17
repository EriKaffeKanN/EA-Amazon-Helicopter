#include "gameOverScene.h"
#include "game.h"

#include <iostream>

GameOverScene::GameOverScene ()
    : Scene (SceneManager::Scenes::GAME_OVER,
             SceneManager::getBgPath (SceneManager::Scenes::GAME_OVER)),
    menu (Menu (game.window, {
                Menu::MenuItem ("Play Again", [](){
                        SceneManager::popScene ();
                        SceneManager::pushScene
                            (SceneManager::createScene (SceneManager::Scenes::GAME));
                        }),
                Menu::MenuItem ("Return to main menu", [](){
                    if (!(SceneManager::returnToScene (SceneManager::Scenes::MAIN_MENU)))
                    {
                        std::cerr << "Could not return to main menu because it does not exist\n";
                    }
                })}))
{

    game.sfx.gameOverMusic.setLoop (true);
    game.sfx.gameOverMusic.play ();
}

GameOverScene::~GameOverScene ()
{
    game.sfx.gameOverMusic.stop ();
}

void GameOverScene::update ()
{
    game.window.draw (this->background);

    menu.update ();
}

void GameOverScene::onSwitchFrom ()
{
}

void GameOverScene::onSwitchTo ()
{

}
