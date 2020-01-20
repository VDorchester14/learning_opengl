#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // current cube code
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// A data structure to hold the x, y, and z of a vertex in 3D space
struct Vertex {
    float coordinates [3];

    Vertex(float x_in, float y_in, float z_in) {
        coordinates[0] = x_in;
        coordinates[1] = y_in;
        coordinates[2] = z_in;
    }
};

// A data structure to hold a vector of vertices
struct VertexArray {
    std::vector<Vertex> vertices;

    VertexArray() {
        // Constructor
    }
    ~VertexArray() {
        // Destructor
    }
    void add_vertex(Vertex v) {
        vertices.push_back(v);
    }
};

// a data scructure that holds a vertex array of the points of a cube
struct Cube {
    VertexArray vertex_array;
    Cube(float x=0.0f, float y=0.0f, float z=0.0f) {
        Vertex origin = Vertex(x, y, z);
    }
};