#ifndef TREE_H_
#define TREE_H_

#include "gameScene.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>

class Tree
{
public:
    Tree(int length, int size);
    ~Tree();
    
    void spawn(int tileX);
    void grow();
    void fall();
    void onCollision(GameScene::CollisionPacket packet);

    int size;

    int length;
    sf::Vector2<float> pos;
    sf::Sprite stump;
    sf::Sprite crown;
    std::vector<sf::Sprite*> logs;
private:
    sf::Texture stumpTexture;
    sf::Texture crownTexture;
    sf::Texture logTexture;
    const char* stumpTexturePath = "../resources/textures/stump.png";
    const char* crownTexturePath = "../resources/textures/crown.png";
    const char* logTexturePath = "../resources/textures/log.png";

};

#endif
