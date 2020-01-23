#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>

#include "primitives/shapes.h"
#include "Shaders/Shader.h"

/* declarations or whatever */
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawTri(float x=0.0f, float y=0.0f, float z=0.0f);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load in our GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    //unsigned int shaderProgram = InitializeShaders();

    Shader ourShader("./source/Shaders/shader.vert", "./source/Shaders/shader.frag");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Process key input */
        //processInput(window); 
        
        /* Render here */
        ourShader.use();
        ourShader.setFloat("someUniform", 1.0f);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        DrawTriangle(-0.5f, 0.0f, 0.0f, 1.0, 0.0, 0.0);
        DrawTriangle(0.5f, 0.0f, 0.0f, 0.0, 1.0, 0.0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// Process key input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}