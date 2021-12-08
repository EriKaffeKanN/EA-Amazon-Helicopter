#include "mainMenuScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

MainMenuScene::MainMenuScene ()
    : Scene (SceneManager::Scenes::MAIN_MENU)
{

}

void MainMenuScene::update ()
{
    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Main menu osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);
}

void MainMenuScene::onSwitchTo ()
{

}


void MainMenuScene::onSwitchFrom ()
{

}
