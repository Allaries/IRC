#ifndef COMMAND
# define COMMAND
# include "include.hpp" 
# include "client.hpp"

struct Command
{
	std::string cmd;
	std::vector<std::string> args;
};

void	handle_pass(Command cmd, Client &user);
#endif