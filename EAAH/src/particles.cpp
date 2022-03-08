#include "particles.h"

Particles::Particles(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(sf::Vector2<float>(30.f, 30.f), sf::Vector2<float>(300.f, 300.f))
{
    this->spriteSheet = new SpriteSheet("../resources/textures/test.png", this->size, sf::Vector2<int>(32, 32), new int[1]{5}, 1, 0.4f);
}