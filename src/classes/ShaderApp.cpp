#include "../../inc/classes/ShaderApp.hpp"
#include "../../inc/main.hpp"

ShaderApp::ShaderApp(void) : _id(0), _vertex_shader(""), _fragment_shader("")
{
	return ;
}

ShaderApp::ShaderApp(ShaderApp const & src) : _id(src._id), _vertex_shader(src._vertex_shader),
									_fragment_shader(src._fragment_shader)
{
	return ;
}

ShaderApp & ShaderApp::operator=(ShaderApp const & rhs)
{
	if (this != &rhs)
	{
		this->_id = rhs._id;
		this->_fragment_shader = rhs._fragment_shader;
		this->_vertex_shader = rhs._vertex_shader;
	}
	return (*this);
}

ShaderApp::~ShaderApp(void)
{
	if (this->_id)
		GL_CALL(glDeleteProgram(this->_id));
	return ;
}

ShaderApp::ShaderApp(const std::string &vertex_shader_stream,
			const std::string &fragment_shader_stream) : _id(0),
								_vertex_shader(vertex_shader_stream),
								_fragment_shader(fragment_shader_stream)
{
	return ;
}

ShaderApp::ShaderApp(std::ifstream &shader_stream) : _id(0)
{
	std::stringstream	ss[2];
	std::string			line;
	ShaderType			type;

	type = ShaderType::NONE;
	if (shader_stream.is_open())
	{
		while (std::getline(shader_stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
			}
			else if (type != ShaderType::NONE)
				ss[(int)type] << line << '\n';
		}
		shader_stream.close();
		this->_vertex_shader = ss[(int)ShaderType::VERTEX].str();
		this->_fragment_shader = ss[(int)ShaderType::FRAGMENT].str();
	}
	else
		std::cerr << "Bad file for shader" << std::endl;
}

bool	ShaderApp::Compile(void)
{
	unsigned int	program;
	unsigned int	vs;
	unsigned int	fs;
	int				linkStatus;

	program = GL_CALL(glCreateProgram());
	if (!program)
		return (false);
	this->_id = program;
	vs = ShaderApp::compileShader(GL_VERTEX_SHADER, this->_vertex_shader);
	fs = ShaderApp::compileShader(GL_FRAGMENT_SHADER, this->_fragment_shader);
	if (vs)
	{
		GL_CALL(glAttachShader(program, vs));
		GL_CALL(glDeleteShader(vs));
	}
	if (fs)
	{
		GL_CALL(glAttachShader(program, fs));
		GL_CALL(glDeleteShader(fs));
	}
	if (vs || fs)
	{
		GL_CALL(glLinkProgram(program));
    	GL_CALL(glGetProgramiv(program, GL_LINK_STATUS, &linkStatus));
		if (linkStatus == GL_TRUE)
		{
			GL_CALL(glValidateProgram(program));
			return (true);
		}
		std::cerr << "Failed to Link Program" << std::endl;
	}
	GL_CALL(glDeleteProgram(program));
	this->_id = 0;
	return (false);
}

void	ShaderApp::Bind(void)	const
{
	if (this->_id != 0)
		GL_CALL(glUseProgram(this->_id));
}

unsigned int	ShaderApp::GetId(void)	const
{
	return (this->_id);
}

unsigned int	ShaderApp::compileShader(unsigned int type,
									const std::string &source)
{
	const std::string	type_s = (type == GL_VERTEX_SHADER
									? "Vertex shader" : "Fragment shader");
	const char			*src = source.c_str();
	unsigned int		id;
	char				*log;
	int					log_l;
	int					result;

	id = GL_CALL(glCreateShader(type));
	if (!id)
	{
		std::cerr << "Failed to create " << type_s << std::endl;
		return (0);
	}
	GL_CALL(glShaderSource(id, 1, &src, nullptr));
	GL_CALL(glCompileShader(id));
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_l));
		log = (char *) alloca(log_l * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, log_l, &log_l, log));
		std::cerr << "Failed to compile " << type_s << std::endl;
		std::cerr << log << std::endl;
		GL_CALL(glDeleteShader(id));
		return (0);
	}
	return (id);
}
