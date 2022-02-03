#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <deque>
#include <unordered_map>
#include <string>

// Avoid cyclic dependency
class Scene;

class SceneManager
{
public:
    enum class Scenes
    {
        SPLASH_SCREEN,
        MAIN_MENU,
        PAUSE_MENU,
        GAME
    };

    struct SceneSettings
    {
        std::string bgImagePath;
    };

    static void pushScene (Scene* scene);
    static void popScene ();
    // Returns false if no active scene can be found
    static bool returnToScene (Scenes scene);
    static Scene* createScene (Scenes scene);
    static Scene* currScene ();
    static const char* getBgPath (Scenes scene);
    static void setBgPath (Scenes scene, std::string path);

private:
    static std::deque<Scene*> sceneQueue;
    static std::unordered_map<Scenes, SceneSettings> defaultSceneSettings;
};

#endif // SCENEMANAGER_H
