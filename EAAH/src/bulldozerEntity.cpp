#include "bulldozerEntity.h"
#include "game.h"
#include "util.h"

#include <random>
#include <iostream>
#include <cmath>

BulldozerEntity::BulldozerEntity(sf::Vector2<float> pos, sf::Vector2<float> size, std::vector<Tree*>* treesRef)
    : Entity(pos, size)
{
    this->treesRef = treesRef;
    this->spriteSheet = new SpriteSheet("../resources/textures/bulldozer.png", this->size, sf::Vector2<int>(64, 64), new int[3]{3, 13, 3}, 3, 0.3f);
    this->currentBehaviour = BulldozerEntity::Behaviour::ROAM;

    // Initialize behaviour variables
    this->behaviourTimer = 0;
    //     Roaming
    this->roamTimer = 0.f;
    this->timeUntilChangeDirection = this->timeUntilChangeDirection = (rand() % 4) + 2;
    this->timeUntilHunt = (rand() % 10) + 5.f;
    this->roamSpeed = 100.f;
    this->standStill = false;
    //     Hunting
    this->huntSpeed = 200.f;
    //     Attacking
    this->attackTimer = 0.f;
    this->timeUntilDestoryLog = 0.8f;
    this->timeUntilRoam = (rand() % 3) + 3.f;
}

BulldozerEntity::~BulldozerEntity()
{
    delete this->treesRef;
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
    this->behaviourTimer += game.ft;
    Entity::update();
}

void BulldozerEntity::onCollision(GameScene::CollisionPacket packet)
{
    // Get squashed...
}

void BulldozerEntity::changeBehaviour(Behaviour behaviour)
{
    this->behaviourTimer = 0;
    this->currentBehaviour = behaviour;
    switch(behaviour)
    {
        case Behaviour::HUNT:
            this->selectTarget();
            this->spriteSheet->currentAnimation = (int)Animations::MOVING;
            break;
        case Behaviour::ROAM:
            this->timeUntilHunt = (rand() % 10) + 5.f;
            this->standStill = false;
            this->spriteSheet->currentAnimation = (int)Animations::MOVING;
            break;
        case Behaviour::ATTACK:
            this->velocity.x = 0;
            this->timeUntilRoam = (rand() % 3) + 3.f;
            break;

    }
}

void BulldozerEntity::roam()
{
    // Check if should change behaviour
    if(this->behaviourTimer > this->timeUntilHunt)
    {
        changeBehaviour(Behaviour::HUNT);
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
                this->velocity.x = -this->roamSpeed * game.ft;
                break;
            case Direction::RIGHT:
                this->velocity.x = this->roamSpeed * game.ft;
                break;
        }
    }
    else
    {
        this->velocity.x = 0.f;
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

void BulldozerEntity::selectTarget()
{
    if(this->treesRef == nullptr)
    {
        std::cerr << "No trees to search for!\n";
        return;
    }

    // Sort all non-dead trees
    std::vector<Tree*> aliveTrees;
    for(Tree* tree: *this->treesRef)
    {
        if(tree->length > 0)
            aliveTrees.push_back(tree);
    }
    
    if(aliveTrees.size() == 0)
    {
        // No trees to kill :(
        changeBehaviour(Behaviour::ROAM);
        return;
    }

    // Select random alive tree
    int treeAmt = aliveTrees.size();
    int treeIndex = rand() % treeAmt;
    this->targetTree = aliveTrees[treeIndex];
}

void BulldozerEntity::hunt()
{
    if(this->targetTree == nullptr)
    {
        std::cerr << "Hunt began before any tree was chosen!\n";
        changeBehaviour(Behaviour::ROAM);
        return;
    }

    // Move towards tree
    if(this->pos.x > this->targetTree->pos.x - 120.f) // offset by 80 pixels (for visual purposes)
    {
        this->spriteSheet->setDirection(Direction::LEFT);
        this->velocity.x = -this->huntSpeed * game.ft;
    }
    else
    {
        this->spriteSheet->setDirection(Direction::RIGHT);
        this->velocity.x = this->huntSpeed * game.ft;
    }

    // Check if close to tree
    if(std::abs(this->pos.x - (this->targetTree->pos.x - 120.f)) < 20.f)
    {
        changeBehaviour(Behaviour::ATTACK);
    }
}

void BulldozerEntity::attack()
{
    this->spriteSheet->currentAnimation = (int)Animations::DIGGING;

    // See if should change behaviour
    if(this->behaviourTimer > this->timeUntilRoam)
    {
        changeBehaviour(Behaviour::ROAM);
    }

    // See if should break log
    if(this->attackTimer > this->timeUntilDestoryLog)
    {
        this->attackTimer = 0.f;
        if(!this->targetTree->destroyLog())
        {
            // If this part is reached, the tree is dead
            changeBehaviour(Behaviour::ROAM);
            return;
        }
    }

    this->attackTimer += game.ft;
}
