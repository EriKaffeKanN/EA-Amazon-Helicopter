#include "game.h"
#include "sceneManager.h"
#include "scene.h"

Game::Game ()
{
    this->ft = 0;
}

void Game::init (sf::VideoMode videoMode, const char* windowTitle)
{
    this->window.create(videoMode, windowTitle);
    SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::SPLASH_SCREEN));
}

void Game::loop ()
{
    sf::Clock clock;
    this->ft = clock.restart ().asSeconds ();

    while (this->window.isOpen())
    {
        sf::Event event;
        while (this->window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    this->window.close ();
                    break;
                default:
                    break;
            }
        }

        this->update ();

        this->ft = clock.restart ().asSeconds ();
    }

    while (SceneManager::currScene () != nullptr)
    {
        SceneManager::popScene ();
    }
}

void Game::update ()
{
    this->window.clear (sf::Color::Blue);
    SceneManager::currScene ()->update ();
    this->window.display ();
}
