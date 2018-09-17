#pragma once

#include "glew/glew.h"
#include "glm/vec4.hpp"

struct vertex
{
	//float pos[4];
	glm::vec4 pos;
};

struct geometry
{
	GLuint vao, vbo, ibo;
	GLuint size;
};

struct shader
{
	GLuint program;
};



geometry makeGeometry(vertex* verts, size_t vertCount,
					  unsigned int* indices, size_t indexCount);

void freeGeometry(geometry &geo);

shader makeShader(const char* vertSource,
				  const char* fragSource);

void freeShader(shader& shad);

void draw(const shader& shader, const geometry& geo);
