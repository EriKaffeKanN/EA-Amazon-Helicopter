#include "gameScene.h"
#include "game.h"
#include "entity.h"
#include "playerEntity.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

GameScene::GameScene()
    : Scene (SceneManager::Scenes::GAME)
{
    sf::Vector2<float> testPos = {20.f, 20.f};
    sf::Vector2<float> testSize = {90.f, 90.f};
    Entity* player = new PlayerEntity(testPos, testSize);
    spawnEntity(player, "../resources/textures/test.png");
}

GameScene::~GameScene()
{
    for(int i = this->entities.size()-1; i >= 0; i++)
    {
        delete this->entities[i];
        this->entities.pop_back();
    }
}

void GameScene::spawnEntity(Entity* entity, const char* texturePath)
{
    this->entities.push_back(entity);
    // Register as collider maybe?
    this->entities.back()->LoadSprite(texturePath);
}

void GameScene::update()
{
    // Game logic
    for(Entity* entity: this->entities)
    {
        entity->update();
    }

    // Drawing
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
        entity->draw();
    }
}

void GameScene::onSwitchTo()
{

}

void GameScene::onSwitchFrom()
{

}
