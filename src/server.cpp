#include "../include/server.hpp"

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
						std::string line;
						while (it->second.is_cmd(line))
						{
							process_cmd(line, it->second);
						}
					}
				}
		}
	}
}


Command	Server::parse_cmd(std::string line)
{
	Command pars;
	long unsigned int i = 0;
	while (std::isspace(line[i]) || i > line.size())
		i++;
	while (!std::isspace(line[i]) || i > line.size()) {
		pars.cmd += std::toupper(line[i]);
		i++;
	}
	while (i < line.size())
	{
		while (i < line.size() && line[i] == ' ')
			i++;
		if (i >= line.size())
			break;

		// ":" detecte, on garde tout le reste en 1 arg
		if (line[i] == ':')
		{
			i++;
			pars.args.push_back(line.substr(i));
			break;
		}

		// Normal
		std::string	param;
		while (i < line.size() && line[i] != ' ')
		{
			param += line[i];
			i++;
		}
		pars.args.push_back(param);
	}
	return (pars);
	
}

int	Server::process_cmd(std::string line, Client &user)
{
	Command cmd = parse_cmd(line);
	// std::cout << "|" << cmd.cmd << "|" << std::endl;
	// for (size_t i = 0; i < cmd.args.size(); ++i) {
	// 	std::cout << "Element " << i << " : " << cmd.args[i] << std::endl; }


	//ok la foret de if commence ici
	//oubliez pas pour les fonctions, il faut faire en sorte que le mec qui en execute une aie bien fait le handshake (preliminaire d'inscription en gros)
	if (cmd.cmd.empty())
		return (0);
	if (cmd.cmd == "PASS")
		handle_pass(cmd, user);
	else
		std::cout << "NO COMMAND IDENTIFIED" << std::endl;
	return (0);

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

void	Server::handle_pass(Command cmd, Client user)
{
	if (cmd.args.size() != 1)
		return ; //la faut envoyer au bougue un message d'erreur;
	if (cmd.args[0].compare(this->password) == 0)
	{
		std::cout << "good password" << std::endl;
		user.setPassOk(true);
	}
	else
		std::cout << this->password << " != " << cmd.args[0] << std::endl;
	return ; //same ici
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
