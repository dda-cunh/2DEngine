#ifndef MAIN_HPP
# define MAIN_HPP

# include <GL/glew.h> 
# include <GLFW/glfw3.h>

# include <iostream>
# include <sstream>

# include "classes/ShaderApp.hpp"
# include "classes/Engine.hpp"

# define HEIGHT				600
# define WIDTH				800

# define MAIN_WINDOW_TITLE	"Engine"

# define GL_CALL(f)         f;\
                            if (glGetError())\
                            std::cerr << __FILE__ << ':' << __LINE__ << std::endl;

#endif
