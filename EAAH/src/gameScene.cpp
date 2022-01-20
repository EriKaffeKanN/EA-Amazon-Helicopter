#include "gameScene.h"
#include "game.h"
#include "entity.h"
#include "playerEntity.h"
#include "bombEntity.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

GameScene::GameScene()
    : Scene (SceneManager::Scenes::GAME,
             SceneManager::getBgPath (SceneManager::Scenes::GAME))
{
    sf::Vector2<float> testPos = {20.f, 200.f};
    sf::Vector2<float> testSize = {300.f, 300.f};
    Entity* tmpPlayer = new PlayerEntity(testPos, testSize);
    this->player = (PlayerEntity*)tmpPlayer;
    spawnEntity(tmpPlayer);
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

    // Input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->player->bombCooldown <= 0)
    {
        sf::Vector2<float> bombPos = {player->pos.x + player->size.x/2.f - 32.f, player->pos.y + 164.f};
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
