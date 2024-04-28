#include "../inc/main.hpp"

void fixPort(GLFWwindow* window, int w, int h)
{
	(void) window;
	glViewport(0, 0, w, h);
}

static void _init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void	processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


GLFWwindow	*setNewWindow(int width, int height, std::string title,
							void (*init)(void))
{
	static bool	glew = false;
	GLFWwindow	*win;

	win = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!win)
	{
		std::cerr << "Couldn't create new GLFW window" << std::endl;
		return (nullptr);
	}
	glfwMakeContextCurrent(win);
	if (!glew && (glewInit() != GLEW_OK))
	{
		std::cerr << "Couldn't Init GLEW" << std::endl;
		glfwSetWindowShouldClose(win, true);
		return (NULL);
	}
	if (init)
		init();
	glfwSetFramebufferSizeCallback(win, fixPort);
	glew = true;
	return (win);
}

int main(void)
{
	GLFWwindow	*window;

	if ((!glfwInit()))
	{
		std::cerr << "Problem Initing GLFW" << std::endl;
		return (-1);
	}
	window = setNewWindow(WIDTH, HEIGHT, MAIN_WINDOW_TITLE, _init);
	if (!window)
		return (-2);
	std::cout << glGetString(GL_VERSION) << std::endl;
	float	data[8] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f
	};
	unsigned int	indices[6] =
	{
		0, 1, 2,
		2, 3, 0	
	};
	unsigned int buff;
	GL_CALL(glGenBuffers(1, &buff));
	GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buff));
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), data, GL_STATIC_DRAW));

	GL_CALL(glEnableVertexAttribArray(0));
	GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	unsigned int ibo;
	GL_CALL(glGenBuffers(1, &ibo));
	GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int),
		indices, GL_STATIC_DRAW));
	std::ifstream	tringle_shader("res/shaders/basic.shader");
	ShaderApp		shadeApp(tringle_shader);
	shadeApp.Compile();
	shadeApp.Bind();
	int location = GL_CALL(glGetUniformLocation(shadeApp.GetId(), "u_Color"));
	GL_CALL(glUniform4f(location, 0.9f, 0.4f, 0.8f, 1.0));
	while (!glfwWindowShouldClose(window))
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		processInput(window);
		GL_CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
