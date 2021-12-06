#include "splashScreenScene.h"
#include "game.h"
#include "sceneManager.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

SplashScreenScene::SplashScreenScene ()
{
    this->elapsedTime = 0;
}

void SplashScreenScene::update ()
{
    elapsedTime += game.dt;
    if (elapsedTime >= 5)
    {
        SceneManager::popScene ();
        // Oh what have I done??
        SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::MAIN_MENU));
        return;
    }

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Splash screen osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::Blue);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);
}

void SplashScreenScene::onSwitchTo ()
{

}


void SplashScreenScene::onSwitchFrom ()
{

}
