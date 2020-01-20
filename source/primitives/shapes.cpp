#include "shapes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

void DrawTriangle(float x, float y, float z) {
    float vertices[] = {
    x + -0.5f, y + -0.5f, z + 0.0f,
    x + 0.5f, y + -0.5f, z + 0.0f,
    x + 0.0f, y + 0.5f, z + 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(1, &VBO);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    return;
}

Triangle::Triangle(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
    vertices[0] = x - 0.5f;
    vertices[1] = y + -0.5f;
    vertices[2] = z + 0.0f;
    vertices[3] = x + 0.5f;
    vertices[4] = y + -0.5f;
    vertices[5] = z + 0.0f;
    vertices[6] = z + 0.0f;
    vertices[7] = x + 0.0f;
    vertices[8] = y + 0.5f;
    vertices[9] = z + 0.0f;
	
	return;
}

void Triangle::InitializeVAO() {

}