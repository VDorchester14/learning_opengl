#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <vector>

// source code for our vertex shader
const char* vertexShaderSource = "#version 440 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// source code for fragment shader
const char* fragmentShaderSource = "#version 440 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

/* declarations or whatever */
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

    /*
    *
    * Defining and setting up our shader objects and program
    *
    */

    // define our vertex shader
    unsigned int vertexShader; // to store id of vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER); // create vertex shader and assign id to vertexShader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // shader to compile to, number of strings, source, and null
    glCompileShader(vertexShader); // now compile the shader

    // test out our shader
    int  success; // to store bool of success or not
    char infoLog[512]; // to store error log
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // function to check if compilation was successful

    if (!success) // was it unsuccessful
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // if so, get error log
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED, %s \n", infoLog); // print it
    }

    unsigned int fragmentShader; // id for frag shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // set source
    glCompileShader(fragmentShader); // compile source

    unsigned int shaderProgram; // shader program id to use shaders
    shaderProgram = glCreateProgram(); // create shader program

    glAttachShader(shaderProgram, vertexShader); // attach the vertex shader
    glAttachShader(shaderProgram, fragmentShader); // attach the fragment shader
    glLinkProgram(shaderProgram); // now link the shader program

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success); // check if it worked successfully
    if (!success) { // if not
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog); // get log
        printf("ERROR::SHADER::PROGRAM::COMPILATIOIN::FALED %s\n", infoLog); // print error log
    }

    glDeleteShader(vertexShader); // delete old shaders since they are now set and no longer needed
    glDeleteShader(fragmentShader); // same

    /* 
    *
    * General steps for drawing
    *
    */
    
    float vertices[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };

    float vertices2[] = {
        0.0f, -0.5f, 0.0f,
        0.9f, -0.5f, 0.0f,
        0.45f, 0.5f, 0.0f
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    // glBindVertexArray(0); // no need to unbind at all as we directly bind a different VAO the next few lines
    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Process key input */
        processInput(window); 
        
        /* Render here */
        glUseProgram(shaderProgram);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < sizeof(VAOs); i++) {
            glBindVertexArray(VAOs[i]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }


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