#pragma once

#include "sceneBase.h"

class sceneTeapot : public sceneBase
{
public:
    sceneTeapot();

    virtual void Init();
    virtual void Update();
    virtual void Draw();

private:
    eCamera* mCamera;
    ePointLight* mPointLight;
};
