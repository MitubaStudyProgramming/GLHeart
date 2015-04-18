//
// Created by ck01- on 2015/4/18.
//

#ifndef GLHEART_SCENEBASE_H
#define GLHEART_SCENEBASE_H

#include "Heart.h"
#include <GLFW/glfw3.h>

class eCamera;
class ePointLight;

class sceneBase {

public:
    sceneBase();

    void SetWindow(GLFWwindow* window);

    virtual void Init();
    virtual void Update();
    virtual void Draw();

protected:
    GLFWwindow* mWindow;
};


#endif //GLHEART_SCENEBASE_H
