#include "scene.h"
#include "game.h"

Scene::Scene (SceneManager::Scenes type, const char* bgPath)
    : background (game.window, bgPath), sceneType (type) {  }

SceneManager::Scenes Scene::getType ()
{
    return this->sceneType;
}

#include <iostream>
// TODO: Replace window with sf::RenderTarget to make it more generic for
// use in for example menu buttons
Scene::BgImage::BgImage (sf::RenderTarget& target, const char* imgPath)
{
    sf::Vector2f targetSize = target.getView ().getSize ();
    std::cerr << targetSize.x << ' ' << targetSize.y << '\n';
    this->verticies.setPrimitiveType (sf::Quads);
    this->verticies.resize (4);
    this->image.loadFromFile (imgPath);
    sf::Vector2u imgSize = image.getSize ();
    std::cerr << imgSize.x << ' ' << imgSize.y << '\n';

    this->verticies [0].position = sf::Vector2f (0, 0);
    this->verticies [1].position = sf::Vector2f (targetSize.x - 1, 0);
    this->verticies [2].position = sf::Vector2f (targetSize.x - 1, targetSize.y - 1);
    this->verticies [3].position = sf::Vector2f (0, targetSize.y - 1);

    this->verticies [0].texCoords = sf::Vector2f (0, 0);
    this->verticies [1].texCoords = sf::Vector2f (imgSize.x - 1, 0);
    this->verticies [2].texCoords = sf::Vector2f (imgSize.x - 1, imgSize.y - 1);
    this->verticies [3].texCoords = sf::Vector2f (0, imgSize.y - 1);
}

void Scene::BgImage::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (this->verticies, &this->image);
}
