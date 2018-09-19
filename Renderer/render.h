#pragma once

#include "glew/glew.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"

struct vertex
{
	glm::vec4 pos;
	glm::vec2 uv;
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

struct texture
{
	GLuint handle;
	unsigned int width, height, channels;
};



geometry makeGeometry(vertex* verts, size_t vertCount,
					  unsigned int* indices, size_t indexCount);

void freeGeometry(geometry &geo);

shader makeShader(const char* vertSource,
				  const char* fragSource);

void freeShader(shader& shad);

texture loadTexture(const char* imgPath);
texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
void freeTexture(texture& tex);

void draw(const shader& shader, const geometry& geo);

void setUniform(const shader& shad, GLuint location, const glm::mat4 value);
void setUniform(const shader& shad, GLuint location, const texture& value, GLuint textureSlot);
