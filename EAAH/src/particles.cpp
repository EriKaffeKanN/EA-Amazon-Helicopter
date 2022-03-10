#include "particles.h"

Particles::Particles(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    this->spriteSheet = new SpriteSheet("../resources/textures/particles.png", this->size, sf::Vector2<int>(32, 32), new int[1]{5}, 1, 0.4f);
}