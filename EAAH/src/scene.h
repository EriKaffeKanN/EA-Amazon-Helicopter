#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
    virtual ~Scene () { };

    virtual void update () = 0;

    virtual void onSwitchTo () = 0;
    virtual void onSwitchFrom () = 0;

private:
    // Entities and other stuff
};

#endif
