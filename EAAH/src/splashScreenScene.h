#ifndef SPLASHSCREENSCENE_H_
#define SPLASHSCREENSCENE_H_

#include "scene.h"

class SplashScreenScene : public Scene
{
public:
    SplashScreenScene ();

    void update () override final;

    void onSwitchTo () override final;
    void onSwitchFrom () override final;
private:
    float elapsedTime;
};

#endif // SPLASHSCREENSCENE_H_
