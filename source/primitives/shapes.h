#ifndef SHAPES_H // include guard
#define SHAPES_H
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

void DrawTriangle(float x, float y, float z, float r, float g, float b);

class Triangle {
public:
	float vertices[9];
	
	Triangle(float x, float y, float z);
	void InitializeVAO();
private:
	;
};

#endif