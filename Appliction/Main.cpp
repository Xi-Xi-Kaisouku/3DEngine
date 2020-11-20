#include "pch.h"
#include <glad\glad.h>
#include "Engine/Graphics/Renderer.h"
#include "Engine\Graphics\Program.h"
#include "Engine\Graphics\Texture.h"


int main(int argc, char** argv)
{
	nc::Renderer renderer;
	renderer.Startup();
	renderer.Create("OpenGL", 800, 600);

	//initialization
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //point 1
		0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5, 1.0f, //point 2
		0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f //point 3
	};

	/*std::string vertexShaderSource;
	ReadFileToString("shaders\\basic.vs.txt", vertexShaderSource);*/

	/*const char* vertexShaderSource = "#version 430 core\n"
		"layout (location = 0) in vec3 vs_position;\n"
		"layout (location = 1) in vec3 vs_color;\n"
		"out vec3 fs_color;\n"
		"void main()\n"
		"{\n"
		"	fs_color = vs_color;\n"
		"	gl_Position = vec4(vs_position.x, vs_position.y, vs_position.z, 1.0);\n"
		"}\0";
		*/

	/*std::string fragmentShaderSource;
	ReadFileToString("shaders\\basic.fs.txt", fragmentShaderSource);*/

	/*const char* fragmentShaderSource = "#version 430 core\n"
		"in vec3 fs_color"
		"out vec4 out_color;\n"
		"void main()\n"
		"{\n"
		"	out_color = vec4(fs_color, 1.0)\n"
		"}\0";
		*/

	Program program;
	program.CreateShaderFromFile("shaders\\basic.vert.txt", GL_VERTEX_SHADER);
	program.CreateShaderFromFile("shaders\\basic.frag.txt", GL_FRAGMENT_SHADER);
	program.Link();
	program.Use();

	
	// create vertex buffers
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// set position pipeline (vertex attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// set color pipeline (vertex attribute)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// set uv pipeline (vertex attribute)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//uniform
	glm::mat4 transform = glm::mat4(1.0f);
	//GLuint uniform = glGetUniformLocation(program.GetProgramID(), "transform");
	//glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform));

	program.SetUniform("transform", transform);

	nc::Texture texture;
	texture.CreateTexture("textures\\llama.jpg");
	


	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				quit = true;
			}
		}

		SDL_PumpEvents();

		transform = glm::rotate(transform, 0.00004f, glm::vec3(0, 0, 1));
		program.SetUniform("transform", transform);
		/*glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(transform));*/


		renderer.BeginFrame();

		//render triangle
		glDrawArrays(GL_TRIANGLES, 0, 3);

		renderer.EndFrame();
	}

	return 0;
}