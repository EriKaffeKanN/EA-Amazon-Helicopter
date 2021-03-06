#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <unordered_map>

class Game
{
public:
    Game ();
    void init (sf::VideoMode videoMode, const char* windowTitle);

    void loop ();
    void update ();

    sf::RenderWindow window;
    // Frame time
    float ft;

    struct
    {
        sf::SoundBuffer helicopterSpinSound;
        sf::Music gameplayMusic;
        sf::Music gameOverMusic;
    } sfx;
};

// Defined in main.cpp
extern Game game;

#endif // GAME_H
