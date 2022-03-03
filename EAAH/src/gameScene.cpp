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

const float GameScene::groundLevel = 560.f;
const float GameScene::tileSize = 80.f;

GameScene::GameScene()
    : Scene (SceneManager::Scenes::GAME,
             SceneManager::getBgPath (SceneManager::Scenes::GAME))
{
    initializeWorld();
}

GameScene::~GameScene()
{
    for(int i = this->entities.size()-1; i >= 0; i--)
    {
        delete this->entities[i];
        this->entities.pop_back();
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
    sf::Vector2<float> enemy1Pos = {20.f, this->groundLevel - 100.f};
    sf::Vector2<float> enemy1Size = {256.f, 256.f};
    Entity* tmpEnemy1 = new BulldozerEntity(enemy1Pos, enemy1Size, &this->trees);
    spawnEntity(tmpEnemy1);

    sf::Vector2<float> enemy2Pos = {140.f, this->groundLevel - 100.f};
    sf::Vector2<float> enemy2Size = {256.f, 256.f};
    Entity* tmpEnemy2 = new BulldozerEntity(enemy2Pos, enemy2Size, &this->trees);
    spawnEntity(tmpEnemy2);

    sf::Vector2<float> enemy3Pos = {240.f, this->groundLevel - 100.f};
    sf::Vector2<float> enemy3Size = {256.f, 256.f};
    Entity* tmpEnemy3 = new BulldozerEntity(enemy3Pos, enemy3Size, &this->trees);
    spawnEntity(tmpEnemy3);
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

void GameScene::update()
{
    this->sweepEntities();
    // Game logic
    for(Entity* entity: this->entities)
    {
        entity->update();
    }

    // Drawing
    game.window.draw (this->background);

    sf::Font font;
    font.loadFromFile ("../resources/fonts/LiberationSans-Regular.ttf");

    sf::Text text;
    text.setFont (font);
    text.setString ("Game screen osv");
    text.setCharacterSize (24);
    text.setFillColor (sf::Color::White);
    text.setStyle (sf::Text::Bold);

    game.window.draw (text);
    for(Tree* tree: this->trees)
    {
        game.window.draw(tree->stump);
        for(sf::Sprite* log: tree->logs)
        {
            game.window.draw(*log);
        }
        if(tree->length > 0)
            game.window.draw(tree->crown);
    }
    for(Entity* entity: this->entities)
    {
        game.window.draw (*entity);
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
    else if (typeid (*entity) == typeid (Tree))
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
            this->entities.erase(this->entities.begin() + i);
            i++;
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
            sf::FloatRect box2 (this->trees [j]->pos,
                    sf::Vector2f (this->trees [j]->size,
                        this->trees [j]->size * (this->trees [j]->length + 1))); // added + 1 to also account for the tree stump

            if (box1.intersects (box2))
            {
                if(typeid(*this->entities[i]) == typeid(BombEntity))
                {
                    this->trees[j]->onCollision({GameScene::CollisionPacket::FERTILIZER});
                    GameScene::CollisionPacket packet = {GameScene::CollisionPacket::TREE};
                    this->entities[i]->onCollision(packet);
                }
            }
        }
    }
}

void GameScene::onSwitchTo()
{

}

void GameScene::onSwitchFrom()
{

}
