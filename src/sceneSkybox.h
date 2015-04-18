//
// Created by ck01- on 2015/4/18.
//

#ifndef GLHEART_SCENESKYBOX_H
#define GLHEART_SCENESKYBOX_H

#include "sceneBase.h"

class sceneSkybox : public sceneBase
{
public:
    virtual void Init();
    virtual void Update();
    virtual void Draw();

private:
    eCamera* mCamera;
};


#endif //GLHEART_SCENESKYBOX_H
