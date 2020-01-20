#include "Shaders.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int InitializeShaders() {
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
        //printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED, %s \n", infoLog); // print it
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
        //printf("ERROR::SHADER::PROGRAM::COMPILATIOIN::FALED %s\n", infoLog); // print error log
    }

    glDeleteShader(vertexShader); // delete old shaders since they are now set and no longer needed
    glDeleteShader(fragmentShader); // same

    return shaderProgram;
}