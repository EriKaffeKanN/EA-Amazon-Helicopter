#include "game.h"

#include <SFML/Graphics.hpp>

Game game;

int main()
{
    game.init (sf::VideoMode (1280, 720), "EA Amazon Helicopter");
    game.loop ();

    return 0;
}
