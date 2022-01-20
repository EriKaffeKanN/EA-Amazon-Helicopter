#include "tree.h"
#include "gameScene.h"

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
    this->pos.x = this->size * tileX;
    this->pos.y = GameScene::groundLevel;

    if(!this->stumpTexture.loadFromFile(this->stumpTexturePath))
    {
        std::cerr << "Failed to retrieve " << this->stumpTexturePath << std::endl;
    }
    if(!this->logTexture.loadFromFile(this->logTexturePath))
    {
        std::cerr << "Failed to retrieve " << this->logTexturePath << std::endl;
    }

    this->stump.setTexture(this->stumpTexture);
    this->stump.setScale(
        this->size / this->stumpTexture.getSize().x,
        this->size / this->stumpTexture.getSize().y
    );
    this->stump.setPosition(this->pos);

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
}

void Tree::grow()
{

}

void Tree::fall()
{
    // TODO: delete all logs
}