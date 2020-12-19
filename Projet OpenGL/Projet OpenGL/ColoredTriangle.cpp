/*#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glad/glad.h> // Glad need to be imported first because it imports the basics of OpenGL elements
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

// Callback function called to resize the window
void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
}


float warpValue(0.0f);

// Function called to process th user's inputs
void processInput(GLFWwindow* window) {
    // Close the window when escape is pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (warpValue < 1.0f) {
            warpValue += 0.001f;
        }
        else {
            warpValue = 1.0f;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (warpValue > 0.0f) {
            warpValue -= 0.001f;
        }
        else {
            warpValue = 0.0f;
        }
    }
}

// Dimensions of the windows
const int W_WIDTH(800), W_HEIGHT(600);

// Datas of a triangle with a color for each vertice
float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
};
unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

float X_OFFSET = 0.3f;


int main()
{

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

    glViewport(0, 0, W_WIDTH, W_HEIGHT);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    Shader shader("./vertex.glsl", "./fragment.glsl");


    // VAO / VBO
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);
    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set our vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    //TEXTURE
    int textWidth, textHeight, nbChannels;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(true);

    unsigned int textures[2];
    glGenTextures(2, textures);

    for (int i = 0; i < 2; i++) {
        switch (i) {
            case 0:
                data = stbi_load("./face.png", &textWidth, &textHeight, &nbChannels, 0);
                break;
            case 1:
                data = stbi_load("./container.jpg", &textWidth, &textHeight, &nbChannels, 0);
                break;
            default:
                data = stbi_load("./container.jpg", &textWidth, &textHeight, &nbChannels, 0);
                break;
        }
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (data) {
            if(i==0)
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            else
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textWidth, textHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
    }
    stbi_image_free(data);
    shader.use();
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); ==> this line permits to draw without filling the drawings

    // We iterate while we don't say explicitly we want to close the window
    while (!glfwWindowShouldClose(window)) {
        // clear the screen with a color
        glClearColor(0.0f, 0.1f, 0.6f, 1.0f); // state-setting function
        glClear(GL_COLOR_BUFFER_BIT); // state-using function

        // input
        processInput(window);

        shader.setFloat("offset", X_OFFSET);
        shader.setFloat("warp", warpValue);
        shader.use();

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate(); // clean/delete all of GLFW's ressources allocated
    return 0;

}*/