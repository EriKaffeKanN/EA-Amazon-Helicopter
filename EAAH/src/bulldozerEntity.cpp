#include "bulldozerEntity.h"
#include "game.h"
#include "util.h"

#include <random>

BulldozerEntity::BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size)
    : Entity(pos, size)
{
    spriteSheet = new SpriteSheet("../resources/textures/bulldozer.png", this->size, sf::Vector2<int>(64, 64), new int[3]{3, 13, 3}, 3, 0.3f);
    currentBehaviour = BulldozerEntity::Behaviour::ROAM;
}

void BulldozerEntity::update()
{
    switch(currentBehaviour)
    {
        case BulldozerEntity::Behaviour::ROAM:
            this->roam();
            break;
        case BulldozerEntity::Behaviour::HUNT:
            this->hunt();
            break;
        case BulldozerEntity::Behaviour::ATTACK:
            this->attack();
            break;

    }
    Entity::update();
}

void BulldozerEntity::roam()
{
    // Check if should change behaviour
    if(this->behaviourTimer > this->timeUntilHunt)
    {
        this->currentBehaviour = Behaviour::ATTACK;
        this->behaviourTimer = 0;
        return;
    }

    // Check if should change roam behaviour
    if(this->roamTimer > this->timeUntilChangeDirection)
    {
        this->roamTimer = 0;

        bool stop = (rand() % 2) && !standStill; // stop randomly only if not already standing still
        if(stop)
        {
            this->standStill = true;
            this->spriteSheet->currentAnimation = (int)Animations::IDLE;
            this->timeUntilChangeDirection = (rand() % 4) + 2; // dont wait for too long
        }
        else
        {
            this->standStill = false;
            this->spriteSheet->currentAnimation = (int)Animations::MOVING;
            this->spriteSheet->switchDirection();
            this->timeUntilChangeDirection = (rand() % 8) + 2;
        }
    }

    // Move
    if(!standStill)
    {
        switch(this->spriteSheet->getDirection())
        {
            case Direction::LEFT:
                this->pos.x -= this->roamSpeed;
                break;
            case Direction::RIGHT:
                this->pos.x += this->roamSpeed;
                break;
        }
    }

    // Check if hit the edges of the map
    if(this->pos.x < 0 && this->spriteSheet->getDirection() == Direction::LEFT)
    {
        this->spriteSheet->setDirection(Direction::RIGHT);
    }
    else if(this->pos.x > 1280 && this->spriteSheet->getDirection() == Direction::RIGHT)
    {
        this->spriteSheet->setDirection(Direction::LEFT);
    }
    this->roamTimer += game.ft;
}

void BulldozerEntity::hunt()
{

}

void BulldozerEntity::attack()
{

}