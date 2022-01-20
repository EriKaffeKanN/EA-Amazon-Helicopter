#include "gameScene.h"
#include "game.h"
#include "entity.h"
#include "playerEntity.h"
#include "bombEntity.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const float GameScene::groundLevel = 0.f;

GameScene::GameScene()
    : Scene (SceneManager::Scenes::GAME,
             SceneManager::getBgPath (SceneManager::Scenes::GAME))
{
    sf::Vector2<float> testPos = {20.f, 10.f};
    sf::Vector2<float> testSize = {300.f, 300.f};
    Entity* tmpPlayer = new PlayerEntity(testPos, testSize);
    this->player = (PlayerEntity*)tmpPlayer;
    spawnEntity(tmpPlayer);

    Tree* tmpTree = new Tree(2, this->tileSize);
    spawnTree(tmpTree, 0);
}

GameScene::~GameScene()
{
    for(int i = this->entities.size()-1; i >= 0; i--)
    {
        delete this->entities[i];
        this->entities.pop_back();
    }
    delete this->player;
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
    for(Entity* entity: this->entities)
    {
        game.window.draw (*entity);
    }
    for(Tree* tree: this->trees)
    {
        game.window.draw(tree->stump);
        for(sf::Sprite* log: tree->logs)
        {
            game.window.draw(*log);
        }
    }

    // Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->bombCooldown <= 0)
    {
        sf::Vector2<float> bombPos = {player->pos.x + player->size.x/2.f - 32.f, player->pos.y + 200.f};
        sf::Vector2<float> bombSize = {64.f, 64.f};
        Entity* bomb = new BombEntity(bombPos, bombSize);
        spawnEntity(bomb);
        this->player->bombCooldown = 1.f;
    }
}

void GameScene::onSwitchTo()
{

}

void GameScene::onSwitchFrom()
{

}
