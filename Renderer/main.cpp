
#include "context.h"
#include "render.h"

#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>



void LoadShaderFiles(char** vert, char** frag);



int main()
{
	context game;
	game.init(800, 400, "OpenGL Renderer");

	vertex triVerts[] =
	{
		{{ -0.5f, -0.5f, 0.0f, 1.0f }},
		{{  0.5f, -0.5f, 0.0f, 1.0f }},
		{{  0.0f,  0.5f, 0.0f, 1.0f }}
	};
	unsigned triIndices[] = { 2,1,0 };

	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);

	char* basicVert = nullptr;
	char* basicFrag = nullptr;
	
	LoadShaderFiles(&basicVert, &basicFrag);

	shader basicShad = makeShader(basicVert, basicFrag);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!game.shouldClose())
	{
		game.tick();

		game.clear();

		draw(basicShad, triangle);
	}

	game.term();

	delete[] basicVert;
	delete[] basicFrag;

	return 0;
}

void LoadShaderFiles(char** vert, char** frag)
{
	int fileLength;
	int lineBreakCount = 0;
	char c;

	char* basicVert;
	char* basicFrag;

	std::ifstream in;

	in.open("VertexBasic.txt");
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
	in.open("VertexBasic.txt");
	in.seekg(0, in.beg);
	in.read(basicVert, fileLength);
	basicVert[fileLength] = '\0';
	in.close();

	lineBreakCount = 0;

	in.open("FragmentBasic.txt");
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
	in.open("FragmentBasic.txt");
	in.seekg(0, in.beg);
	in.read(basicFrag, fileLength);
	basicFrag[fileLength] = '\0';
	in.close();

	*vert = basicVert;
	*frag = basicFrag;
}
