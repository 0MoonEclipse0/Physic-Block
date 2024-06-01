#include <stdio.h>
#include <GLFW/glfw3.h>
#include "window.h"

int main() 
{
    if (CreateWindow(640, 480, "Hello, World!") != 0) 
    {
        return -1;
    }

    glfwTerminate();
    return 0;
}