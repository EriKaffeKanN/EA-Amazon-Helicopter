#include "splashScreenScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

SplashScreenScene::SplashScreenScene ()
    : Scene (SceneManager::Scenes::SPLASH_SCREEN)
{
    this->elapsedTime = 0;
}

void SplashScreenScene::update ()
{
    elapsedTime += game.ft;
    if (elapsedTime >= 1)
    {
        SceneManager::popScene ();
        SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::GAME)); // REMINDER TO CHANGE BACK TO Scenes::MAIN_MENU
        return;
    }

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Splash screen osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);
}

void SplashScreenScene::onSwitchTo ()
{

}


void SplashScreenScene::onSwitchFrom ()
{

}
