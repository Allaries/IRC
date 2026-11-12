#ifndef SERVER
# define SERVER
# include "client.hpp"
# include "channel.hpp"
# include "command.hpp"
# include "include.hpp"

class Channel;

class Server
{
private:
	std::string password;
	pollfd serv;
	// tableau des fd reagrde par poll
	std::vector <struct pollfd> all_fd;
	// tableau de tt les clients (on peut les chercher avec le fd)
	std::map <int, Client> all_client;
	//liste de touts les channel ouverts
	std::map <std::string, Channel> all_channel;
public:
	void	loop();
	int		process_cmd(std::string line, Client &user);
	Command	parse_cmd(std::string line);
	int		addclient(int clientfd, std::string hostname);
	void	remove_client(int fd);

	//Server related command
	void	handle_pass(Command cmd, Client user);

	Server(int servfd, std::string password);
	~Server();
};


#endif
