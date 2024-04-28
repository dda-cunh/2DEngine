#ifndef SHADERAPP_HPP
# define SHADERAPP_HPP

# include <GL/glew.h>
# include <iostream>
# include <fstream>
# include <sstream>

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

class	ShaderApp
{
	public:
		ShaderApp(void);
		ShaderApp(ShaderApp const & src);
		ShaderApp & operator=(ShaderApp const & rhs);
		virtual ~ShaderApp(void);

		ShaderApp(const std::string &vertex_shader,
			const std::string &fragment_shader);
		ShaderApp(std::ifstream &shader_stream);

		bool	Compile(void);
		void	run(void) const;

	private:
		unsigned int	_id;
		std::string		_vertex_shader;
		std::string		_fragment_shader;

		static unsigned int	compileShader(unsigned int type,
								const std::string &source);
};

#endif
