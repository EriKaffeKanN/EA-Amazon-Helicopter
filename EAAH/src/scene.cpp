#include "scene.h"
#include "game.h"

Scene::Scene (SceneManager::Scenes type, const char* bgPath)
    : background (game.window, bgPath), sceneType (type) {  }

SceneManager::Scenes Scene::getType ()
{
    return this->sceneType;
}

Scene::BgImage::BgImage (sf::Window& window, const char* imgPath)
{
    sf::Vector2u windowSize = window.getSize ();
    this->verticies.setPrimitiveType (sf::Quads);
    this->verticies.resize (4);
    this->image.loadFromFile (imgPath);
    sf::Vector2u imgSize = image.getSize ();

    this->verticies [0].position = sf::Vector2f (0, 0);
    this->verticies [1].position = sf::Vector2f (windowSize.x, 0);
    this->verticies [2].position = sf::Vector2f (windowSize.x, windowSize.y);
    this->verticies [3].position = sf::Vector2f (0, windowSize.y);

    this->verticies [0].texCoords = sf::Vector2f (0, 0);
    this->verticies [1].texCoords = sf::Vector2f (imgSize.x, 0);
    this->verticies [2].texCoords = sf::Vector2f (imgSize.x, imgSize.y);
    this->verticies [3].texCoords = sf::Vector2f (0, imgSize.y);
}

void Scene::BgImage::draw (sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw (this->verticies, &this->image);
}
