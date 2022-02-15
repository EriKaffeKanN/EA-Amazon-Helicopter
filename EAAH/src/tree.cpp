#include "tree.h"
#include "gameScene.h"

#include <iostream>

Tree::Tree(int length, int size)
{
    this->length = length;
    this->size = size;
}

Tree::~Tree()
{
    for(int i = this->logs.size()-1; i >= 0; i--)
    {
        delete this->logs[i];
        this->logs.pop_back();
    }
}

void Tree::spawn(int tileX)
{
    // Snap position to tile
    // this->pos.y refers to the y-position of the stump
    this->pos.x = this->size * tileX;
    this->pos.y = GameScene::groundLevel;

    if(!this->stumpTexture.loadFromFile(this->stumpTexturePath))
    {
        std::cerr << "Failed to retrieve " << this->stumpTexturePath << std::endl;
    }
    if(!this->crownTexture.loadFromFile(this->crownTexturePath))
    {
        std::cerr << "Failed to retrieve " << this->crownTexturePath << std::endl;
    }
    if(!this->logTexture.loadFromFile(this->logTexturePath))
    {
        std::cerr << "Failed to retrieve " << this->logTexturePath << std::endl;
    }

    // Stump
    this->stump.setTexture(this->stumpTexture);
    this->stump.setScale(
        this->size / this->stumpTexture.getSize().x,
        this->size / this->stumpTexture.getSize().y
    );
    this->stump.setPosition(this->pos);

    // Logs
    for(int i = 1; i <= this->length; i++)
    {
        sf::Sprite* log = new sf::Sprite;
        log->setTexture(this->logTexture);
        log->setScale(
            this->size / this->logTexture.getSize().x,
            this->size / this->logTexture.getSize().y
        );
        log->setPosition(this->pos.x, this->pos.y - i*this->size);
        this->logs.push_back(log);
    }

    // Crown
    this->crown.setTexture(this->crownTexture);
    this->crown.setScale(
        this->size / this->stumpTexture.getSize().x,
        this->size / this->stumpTexture.getSize().y
    );
    this->crown.setPosition(this->pos.x - (this->size/2), this->pos.y - (this->length+2)*this->size);
}

void Tree::grow()
{
    this->length += 1;
    // Spawn new log
    sf::Sprite* log = new sf::Sprite;
    log->setTexture(this->logTexture);
    log->setScale(
        this->size / this->logTexture.getSize().x,
        this->size / this->logTexture.getSize().y
    );
    log->setPosition(this->pos.x, this->pos.y - this->length*this->size);
    this->logs.push_back(log);

    // Raise tree crown
    this->crown.setPosition(this->pos.x - (this->size/2), this->pos.y - (this->length+2)*this->size);
}

void Tree::onCollision(GameScene::CollisionPacket packet)
{
    if(packet.collider == GameScene::CollisionPacket::FERTILIZER){
        this->grow();
    }
}

void Tree::fall()
{
    // TODO: delete all logs
}
