#include <iostream>
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include "mainScene.h"

using namespace std;

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
    }

    glfwMakeContextCurrent(window);

    glewInit();

    MainScene scene;
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