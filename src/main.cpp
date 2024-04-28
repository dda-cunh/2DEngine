#include "../inc/main.hpp"
#include <fstream>

void fixPort(GLFWwindow* window, int w, int h)
{
	(void) window;
	glViewport(0, 0, w, h);
}

void display(void)
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
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
	{
		float	data[6] = {-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
		unsigned int buff;
		glGenBuffers(1, &buff);
		glBindBuffer(GL_ARRAY_BUFFER, buff);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), data, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		std::ifstream	tringle_shader("res/shaders/triangle.shader");
		ShaderApp		shadeApp(tringle_shader);
		shadeApp.Compile();
		shadeApp.run();
	}
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}
