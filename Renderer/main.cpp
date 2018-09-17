
#include "context.h"
#include "render.h"



int main()
{
	context game;
	game.init(400, 200, "OpenGL Renderer");

	vertex triVerts[] =
	{
		{{ -0.5f, -0.5f, 0.0f, 1.0f }},
		{{  0.5f, -0.5f, 0.0f, 1.0f }},
		{{  0.0f,  0.5f, 0.0f, 1.0f }}
	};
	unsigned triIndices[] = { 2,1,0 };

	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);

	const char* basicVert =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"void main() {gl_Position = position;}";

	const char* basicFrag =
		"#version 330\n"
		"out vec4 vertColor;\n"
		"void main() { vertColor = vec4(0.0, 1.0, 0.0, 1.0); }";

	shader basicShad = makeShader(basicVert, basicFrag);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!game.shouldClose())
	{
		game.tick();

		draw(basicShad, triangle);
	}

	game.term();

	return 0;
}
