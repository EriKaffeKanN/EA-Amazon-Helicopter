#include "pauseMenuScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

PauseMenuScene::PauseMenuScene ()
    : Scene (SceneManager::Scenes::PAUSE_MENU,
            SceneManager::getBgPath (SceneManager::Scenes::PAUSE_MENU)),
    menu (Menu (game.window, {
                Menu::MenuItem ("Return to game", [](){
                    if (!(SceneManager::returnToScene (SceneManager::Scenes::GAME)))
                    {
                        std::cerr << "Could not return to game because it does not exist\n";
                    }
                    }),
                Menu::MenuItem ("Return to main menu", [](){
                    if (!(SceneManager::returnToScene (SceneManager::Scenes::MAIN_MENU)))
                    {
                        std::cerr << "Could not return to main menu because it does not exist\n";
                    }
                    })}))
{

}

void PauseMenuScene::update ()
{
    game.window.draw (this->background);

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Pause menu osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);

    menu.update ();
}

void PauseMenuScene::onSwitchTo ()
{

}

void PauseMenuScene::onSwitchFrom ()
{

}
