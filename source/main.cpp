#include <GLFW/glfw3.h>
#include <iostream>
int main()
{
    //initialize library
    
    //if we failed to initialize the glfw library stop the program
    if (!glfwInit()) {
        return -1;
    }
    //otherwise, attempt to create a window
    GLFWwindow* window = glfwCreateWindow(1200, 720, "Egypt's Game Engine", nullptr, nullptr);


    //check whether the window was successfully created
    
    // if failed notify the user, terminate the glfw library and exit the program
    if (window == nullptr) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //if the window was successfully created enter the main event loop

    //set window position
    //glfwSetWindowPos(window, -, -);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    //if we have exited the while loop above the window has been requested to be closed so now clean and clear the glfw library
    glfwTerminate();
    return 0;

}