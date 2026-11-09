#ifndef SERVER
# define SERVER
# include "include.hpp"
# include "client.hpp"

class Server
{
private:
	pollfd serv;
	// tableau des fd reagrde par poll
	std::vector <struct pollfd> all_fd;
	// tableau de tt les clients
	std::map <int, Client> all_client;
public:
	void	loop();
	int		addclient(int clientfd, std::string hostname);
	Server(int servfd);
	~Server();
};


#endif
