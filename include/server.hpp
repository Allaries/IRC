#ifndef SERVER
# define SERVER
# include "include.hpp"
# include "client.hpp"
# include "channel.hpp"

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
	int		addclient(int clientfd, std::string hostname);
	Server(int servfd, std::string password);
	~Server();
};


#endif
