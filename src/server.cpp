#include "server.hpp"

void	Server::loop()
{
	while (1)
	{
		int ret = poll(&this->all_fd[0], this->all_fd.size(), -1);
		if (ret > 0)
		{
			for (size_t i = 0; i < this->all_fd.size(); i++)
				if (this->all_fd[i].revents & POLLIN && i == 0)
				{
					std::cout << "new client detected" << std::endl;
					sockaddr_storage client_addr;
					socklen_t addrlen = sizeof(client_addr);
					int clientfd = accept(this->serv.fd, (sockaddr *)&client_addr, &addrlen);
					if (clientfd < 0)
						break ;
					char hostname[NI_MAXHOST];
					getnameinfo((struct sockaddr *)&client_addr, addrlen, hostname, sizeof(hostname), NULL, 0, 0);					
					this->addclient(clientfd, hostname);
				}
				else if (this->all_fd[i].revents & POLLIN && i != 0)
				{
					std::map<int, Client>::iterator it = this->all_client.find(this->all_fd[i].fd);
					if (it != this->all_client.end())
					{
						int status = it->second.recv_usage();
						if (status == 0)
						{
							this->all_client.erase(all_fd[i].fd);
							this->all_fd.erase(all_fd.begin() + i);
							i--;
						}
						//chopper la cmd ici
						// it->second.check_cmd();
					}
				}
		}
	}
}


//ajoute un client au tableau de fd client regarde par poll() ET au tableau contenant tout les clients

int	Server::addclient(int clientfd, std::string hostname)
{
	fcntl(clientfd, F_SETFL, O_NONBLOCK);
	pollfd user;

	user.fd = clientfd;
	user.events = POLLIN;
	user.revents = 0;
	this->all_fd.push_back(user);
	Client n(clientfd, hostname);
	this->all_client.insert(std::make_pair(clientfd, n));
	return (1);
}

Server::Server(int servfd, std::string password)
{
	pollfd adaj;
	adaj.fd = servfd;
	adaj.events = POLLIN;
	adaj.revents = 0;
	this->serv = adaj;
	all_fd.push_back(adaj);
	this->password = password;
}

Server::~Server()
{
}
