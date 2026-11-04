#ifndef SERVER
# define SERVER
# include "include.hpp"

class Server
{
private:
	
public:
	Server(pollfd server);
	~Server();
};


#endif
Server::Server(pollfd server)
{
	all_fd.push_back(server);
}

Server::~Server()
{
}
