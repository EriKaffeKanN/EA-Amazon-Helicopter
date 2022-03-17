#include "gameScene.h"
#include "game.h"
#include "entity.h"
#include "playerEntity.h"
#include "bombEntity.h"
#include "tree.h"
#include "bulldozerEntity.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const float GameScene::groundLevel = 620.f;
const float GameScene::tileSize = 80.f;

GameScene::GameScene()
    : Scene (SceneManager::Scenes::GAME,
             SceneManager::getBgPath (SceneManager::Scenes::GAME))
{
    initializeWorld();

    game.sfx.gameplayMusic.setLoop (true);
    game.sfx.gameplayMusic.play ();
}

GameScene::~GameScene()
{
    for (Entity* entity : this->entities)
    {
        delete entity;
    }

    for (Tree* tree : this->trees)
    {
        delete tree;
    }
}

void GameScene::initializeWorld()
{
    // Spawn player
    sf::Vector2<float> playerPos = {20.f, 10.f};
    sf::Vector2<float> playerSize = {200.f, 110.f};
    Entity* tmpPlayer = new PlayerEntity(playerPos, playerSize);
    this->player = (PlayerEntity*)tmpPlayer; // store player in this->entities as well as this->player for easy access
    spawnEntity(tmpPlayer);

    // Spawn trees
    const int treeAmt = 16;
    int treeLengths[treeAmt]{2, 1, 2, 0, 2, 1, 1, 0, 1, 3, 2, 0, 2, 1, 3, 0};
    for(int i = 0; i < treeAmt; i++)
    {
        Tree* tmpTree = new Tree(treeLengths[i], this->tileSize);
        spawnTree(tmpTree, i);
    }

    // Spawn enemies
    for(int i = 0; i < 3; i++)
    {
        float posX = (rand() % 1000) + 30.f;
        spawnEnemy(posX);
    }
}

void GameScene::spawnEntity(Entity* entity)
{
    this->entities.push_back(entity);
    // Register as collider maybe?
    this->entities.back()->loadSprite();
}

void GameScene::spawnTree(Tree* tree, int tileX)
{
    this->trees.push_back(tree);
    this->trees.back()->spawn(tileX);
}

void GameScene::spawnEnemy(float posX)
{
    sf::Vector2<float> enemyPos = {posX, this->groundLevel - 100.f};
    sf::Vector2<float> enemySize = {256.f, 256.f};
    Entity* tmpEnemy = new BulldozerEntity(enemyPos, enemySize, this->trees);
    spawnEntity(tmpEnemy);
}

void GameScene::update()
{
    this->sweepEntities();

    // Drawing
    game.window.draw (this->background);

    for(Tree* tree: this->trees)
    {
        // Stump
        game.window.draw(tree->stump);
        // Logs
        for(sf::Sprite* log: tree->logs)
        {
            game.window.draw(*log);
        }
        // Crown
        if(tree->length > 0)
            game.window.draw(tree->crown);
        // Particles
        if(tree->growing)
        {
            game.window.draw(*tree->particles);
        }
    }

    for(Entity* entity: this->entities)
    {
        game.window.draw (*entity); // TODO: Find out why things don't always draw properly
    }

    // Game logic
    if (isGameOver ())
    {
        SceneManager::popScene ();
        SceneManager::pushScene (SceneManager::createScene (SceneManager::Scenes::GAME_OVER));
        return;
    }

    for(Tree* tree: this->trees)
    {
        tree->update();
    }
    for(Entity* entity: this->entities)
    {
        entity->update();
    }

    this->checkCollisions ();

    // Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->bombCooldown <= 0)
    {
        sf::Vector2<float> bombPos = {player->pos.x + (player->size.x/2.f) - (32.f/2.f), player->pos.y + (player->size.y/2.f)};
        sf::Vector2<float> bombSize = {32.f, 32.f};
        Entity* bomb = new BombEntity(bombPos, bombSize);
        spawnEntity(bomb);
        this->player->bombCooldown = 1.f;
    }
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Escape))
    {
        SceneManager::pushScene (
            SceneManager::createScene (SceneManager::Scenes::PAUSE_MENU));
    }

    // Spawn new bulldozer
    if(this->bulldozerTimer > this->timeUntilSpawnBulldozer)
    {
        float posX = (rand() % 2)*2000 - 30.f;
        spawnEnemy(posX);
        this->bulldozerTimer = 0.f;
    }

    this->bulldozerTimer += game.ft;
}

GameScene::CollisionPacket getEntityCollisionPacket (Entity* entity)
{
    GameScene::CollisionPacket packet;
    if (typeid (*entity) == typeid (PlayerEntity))
    {
        packet.collider = GameScene::CollisionPacket::PLAYER;
    }
    else if (typeid (*entity) == typeid (BombEntity))
    {
        packet.collider = GameScene::CollisionPacket::FERTILIZER;
    }
    else if (typeid (*entity) == typeid (BulldozerEntity))
    {
        packet.collider = GameScene::CollisionPacket::ENEMY;
    }

    return packet;
}

void GameScene::sweepEntities()
{
    for(int i = 0; i < this->entities.size(); i++)
    {
        if(this->entities[i]->dead)
        {
            delete this->entities [i];
            this->entities.erase(this->entities.begin() + i);
            i--;
        }
    }
}

void GameScene::checkCollisions ()
{
    // Entities with entities
    for (int i = 0; i < this->entities.size (); i++)
    {
        sf::FloatRect box1 (this->entities [i]->pos, this->entities [i]->size);
        for (int j = 0; j < this->entities.size (); j++)
        {
            if (i == j)
                continue;
            
            sf::FloatRect box2 (this->entities [j]->pos, this->entities [j]->size);

            if (box1.intersects (box2))
            {
                GameScene::CollisionPacket packet =
                    getEntityCollisionPacket (this->entities [j]);

                this->entities [i]->onCollision (packet);
            }
        }
    }

    // Entities with trees
    for (int i = 0; i < this->entities.size (); i++)
    {
        sf::FloatRect box1 (this->entities [i]->pos, this->entities [i]->size);
        for (int j = 0; j < this->trees.size (); j++)
        {
            float treeHeight = this->trees [j]->size * (this->trees [j]->length);
            sf::FloatRect box2 (this->trees [j]->pos.x,
                                this->trees [j]->pos.y - treeHeight,
                                this->trees [j]->size,
                                treeHeight);

            if (box1.intersects (box2))
            {
                // This redeclaration makes things prettier and disables a warning
                Entity* tmpEntity = this->entities [i];
                if (typeid (*tmpEntity) == typeid (BombEntity))
                {
                    this->trees[j]->onCollision({GameScene::CollisionPacket::FERTILIZER});
                    GameScene::CollisionPacket packet = {GameScene::CollisionPacket::TREE};
                    this->entities[i]->onCollision(packet);
                }
            }
        }
    }
}

bool GameScene::isGameOver ()
{
    bool treesExist = false;
    for (Tree* tree : this->trees)
    {
        if (tree->length > 0)
        {
            treesExist = true;
            break;
        }
    }

    if (treesExist && !player->dead)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void GameScene::onSwitchTo()
{
    game.sfx.gameplayMusic.play ();
}

void GameScene::onSwitchFrom()
{
    game.sfx.gameplayMusic.pause ();
    game.sfx.gameplayMusic.pause ();
}
