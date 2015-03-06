#include <time.h>
#include "eTime.h"

namespace eTime
{
    static double gEllapsedTime = 0;
    static double gDeltaTime = 0;

    void Update()
    {
        double time = glfwGetTime();
        gDeltaTime = time - gEllapsedTime;
        gEllapsedTime = time;
    }

    double GetDeltaTime() {
        return gDeltaTime;
    }

    double GetEllapsedTime() {
        return gEllapsedTime;
    }
}