#include "mainMenuScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

MainMenuScene::MainMenuScene ()
    : Scene (SceneManager::Scenes::MAIN_MENU,
             SceneManager::getBgPath (SceneManager::Scenes::MAIN_MENU)),
    menu (Menu (game.window, {
                Menu::MenuItem ("Play", [](){
                    SceneManager::pushScene
                        (SceneManager::createScene (SceneManager::Scenes::GAME));
                    }),
                Menu::MenuItem ("Restart or something", []() {
                    SceneManager::popScene ();
                    SceneManager::pushScene
                        (SceneManager::createScene (SceneManager::Scenes::SPLASH_SCREEN));
                    }),
                Menu::MenuItem ("Exit", [](){
                    game.window.close ();
                    })}))
{

}

void MainMenuScene::update ()
{
    game.window.draw (this->background);

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Main menu osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);

    menu.update ();
}

void MainMenuScene::onSwitchTo ()
{

}


void MainMenuScene::onSwitchFrom ()
{

}
