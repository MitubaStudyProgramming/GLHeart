#include <iostream>
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include "sceneShadowMap.h"
#include "sceneSkybox.h"
#include "sceneTeapot.h"

using namespace std;

GLFWwindow* gWindow = NULL;

int main()
{
    if( glfwInit() == -1 )
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(1024, 768, "GLHeartTest", NULL, NULL);
    if(window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    gWindow = window;

    glfwMakeContextCurrent(window);

    glewInit();

    sceneSkybox scene;
    //sceneShadowMap scene;
    //sceneTeapot scene;

    scene.SetWindow(window);
    scene.Init();

    while( !glfwWindowShouldClose( window ) )
    {
        scene.Update();
        scene.Draw();

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}