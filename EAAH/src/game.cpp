#include "game.h"
#include "sceneManager.h"

Game::Game ()
{
    this->dt = 0;
}

void Game::init (sf::VideoMode videoMode, const char* windowTitle)
{
    this->window.create(videoMode, windowTitle);
    SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::SPLASH_SCREEN));
}

void Game::loop ()
{
    sf::Clock clock;
    this->dt = clock.restart ().asSeconds ();

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

        this->dt = clock.restart ().asSeconds ();
    }
}

void Game::update ()
{
    this->window.clear (sf::Color::Blue);
    SceneManager::sceneQueue.back ()->update ();
    this->window.display ();
}
