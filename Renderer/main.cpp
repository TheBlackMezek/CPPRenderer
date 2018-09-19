
#include "context.h"
#include "render.h"

#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>

#include "glm/ext.hpp"
#include "glm/mat4x4.hpp"



void LoadShaderFiles(const char* vertPath, const char* fragPath, char** vert, char** frag);



int main()
{
	context game;
	game.init(800, 400, "OpenGL Renderer");

	vertex triVerts[] =
	{
		{ { -0.5f,  1.5f,  0.0f, 1.0f }, { 0, 0 } },
		{ {  0.5f,  1.5f,  0.0f, 1.0f }, { 1, 0 } },
		{ {  0.0f,  0.5f,  0.0f, 1.0f }, { 0.5, 1 } },
		{ {  0.0f, -0.5f, -0.5f, 1.0f }, { 0, 0 } },
		{ {  0.0f, -0.5f,  0.5f, 1.0f }, { 1, 0 } }
	};
	unsigned triIndices[] = { 2,1,0, 2,4,3 };

	geometry triangle = makeGeometry(triVerts, 5, triIndices, 6);

	char* basicVert = nullptr;
	char* basicFrag = nullptr;
	
	LoadShaderFiles("VertexMVP.txt", "FragmentBasic.txt", &basicVert, &basicFrag);

	shader basicShad = makeShader(basicVert, basicFrag);

	unsigned char whitePixel[] = { 0, 200, 0 };
	texture whiteTexture = makeTexture(1, 1, 3, whitePixel);
	texture testImgTexture = loadTexture("Img.png");

	glm::mat4 cam_proj = glm::perspective(glm::radians(45.0f), 800.0f / 400.0f, 0.1f, 1000.0f);
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 triangle_model = glm::identity<glm::mat4>();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!game.shouldClose())
	{
		game.tick();

		game.clear();

		triangle_model = glm::rotate(triangle_model, glm::radians(5.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		setUniform(basicShad, 0, cam_proj);
		setUniform(basicShad, 1, cam_view);
		setUniform(basicShad, 2, triangle_model);
		setUniform(basicShad, 3, testImgTexture, 0);

		draw(basicShad, triangle);
	}

	game.term();

	delete[] basicVert;
	delete[] basicFrag;

	return 0;
}

void LoadShaderFiles(const char* vertPath, const char* fragPath, char** vert, char** frag)
{
	int fileLength;
	int lineBreakCount = 0;
	char c;

	char* basicVert;
	char* basicFrag;

	std::ifstream in;

	in.open(vertPath);
	in.seekg(0, in.end);
	fileLength = in.tellg();
	in.seekg(0, in.beg);

	while (in.get(c))
	{
		if (c == '\n')
		{
			++lineBreakCount;
		}
	}
	fileLength -= lineBreakCount;

	basicVert = new char[fileLength + 1];

	in.close();
	in.open(vertPath);
	in.seekg(0, in.beg);
	in.read(basicVert, fileLength);
	basicVert[fileLength] = '\0';
	in.close();

	lineBreakCount = 0;

	in.open(fragPath);
	in.seekg(0, in.end);
	fileLength = in.tellg();
	in.seekg(0, in.beg);

	while (in.get(c))
	{
		if (c == '\n')
			++lineBreakCount;
	}
	fileLength -= lineBreakCount;

	basicFrag = new char[fileLength + 1];

	in.close();
	in.open(fragPath);
	in.seekg(0, in.beg);
	in.read(basicFrag, fileLength);
	basicFrag[fileLength] = '\0';
	in.close();

	*vert = basicVert;
	*frag = basicFrag;
}
