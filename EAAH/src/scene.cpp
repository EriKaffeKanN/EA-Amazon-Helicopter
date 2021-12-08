#include "scene.h"

Scene::Scene (SceneManager::Scenes type)
    : sceneType (type) {  }

SceneManager::Scenes Scene::getType ()
{
    return this->sceneType;
}
