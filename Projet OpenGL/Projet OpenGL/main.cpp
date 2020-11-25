#include <glad/glad.h> // Glad need to be imported first because it imports the basics of OpenGL elements
#include <GLFW/glfw3.h>
#include <iostream>

// Callback function called to resize the window
void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}

// Function called to process th user's inputs
void processInput(GLFWwindow* window) {
    // Close the window when escape is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    // Dimensions of the windows
    const int W_WIDTH(800), W_HEIGHT(600);

    // Initialisation of GLFW
    glfwInit();
    // Adding OpenGL's version (3.3) --> ensure that we have the right version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Setting OpenGL's profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating window object
    GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Project OpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // We tell GLFW to make the context of our window the main context on our current thread
    glfwMakeContextCurrent(window);

    // We pass GLAD the function to load the adress of the OpenGL function pointers (OS-Specific)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // We tell OpenGL the size of the window so that he could adapt to it
    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    // CALLBACK FUNCTIONS: to setup after having created the window and before the render loop
    // We tell GLFW to call the callback function frameBufferSizeCallback when the window is resized
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    // We iterate while we don't say explicitly we want to close the window
    while (!glfwWindowShouldClose(window)) {
        // clear the screen with a color
        glClearColor(0.5f, 0.4f, 0.1f, 1.0f); // state-setting function
        glClear(GL_COLOR_BUFFER_BIT); // state-using function

        // input
        processInput(window);

        //rendering commands here

        // check and call events and swap the buffers
        glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }

    glfwTerminate(); // clean/delete all of GLFW's ressources allocated
    return 0;
    
}