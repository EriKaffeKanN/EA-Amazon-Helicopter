#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game ();
    void init (sf::VideoMode videoMode, const char* windowTitle);

    void loop ();
    void update ();

    sf::RenderWindow window;
    float dt;
};

// Defined in main.cpp
extern Game game;

#endif // GAME_H
