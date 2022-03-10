#include "game.h"
#include "sceneManager.h"
#include "scene.h"

#include <iostream>

static sf::SoundBuffer soundBufferFromFile (const char* filename)
{
    sf::SoundBuffer sb;
    if (!sb.loadFromFile (filename))
    {
        std::cerr << "OOOOOOOOOOOO\n";
        std::exit (2);
    }
    return sb;
}

Game::Game ()
{
    this->ft = 0;
}

void Game::init (sf::VideoMode videoMode, const char* windowTitle)
{
    this->window.create(videoMode, windowTitle);
    SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::SPLASH_SCREEN));

    this->helicopterSpin = soundBufferFromFile ("../resources/sfx/helicopterSpin.wav");
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
