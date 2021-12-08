#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <deque>

// Avoid cyclic dependency
class Scene;

class SceneManager
{
public:
    enum class Scenes
    {
        SPLASH_SCREEN,
        MAIN_MENU,
        GAME
    };

    static void pushScene (Scene* scene);
    static void popScene ();
    // Returns false if no active scene can be found
    static bool returnToScene (Scenes scene);
    static Scene* createScene (Scenes scene);
    static Scene* currScene ();

private:
    static std::deque<Scene*> sceneQueue;
};

#endif // SCENEMANAGER_H
