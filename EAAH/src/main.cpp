#include "game.h"

#include <SFML/Graphics.hpp>

#include <iostream>

Game game;

int main()
{
    game.init (sf::VideoMode (1280, 720), "EA Amazon Helicopter");

    sf::SoundBuffer sb;
    if (!sb.loadFromFile ("../resources/sfx/helicopterSpin.wav"))
    {
        std::cerr << "JFKJFKJFKJKFJK";
        std::exit (2);
    }

    game.loop ();

    return 0;
}
