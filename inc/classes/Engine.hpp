#ifndef ENGINE_HPP
# define ENGINE_HPP

class	Engine	//TODO
{
	public:
		Engine(void);
		Engine(Engine const & src);
		Engine & operator=(Engine const & rhs);
		virtual ~Engine(void);
};

#endif
