#include "include.hpp"
// #include "server.hpp"


void setup_address(const char *port_str, struct addrinfo **res) 
{
    struct addrinfo hints;
    
    std::memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;     // Accepte IPv4 (AF_INET) ou IPv6 (AF_INET6)
    hints.ai_socktype = SOCK_STREAM;   // Indispensable pour le protocole TCP
    hints.ai_flags    = AI_PASSIVE;    // Remplit automatiquement l'adresse IP de l'hôte local

    int status = getaddrinfo(NULL, port_str, &hints, res);
    
    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        std::exit(1);
    }
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	addrinfo *res;
	setup_address(argv[1], &res);
	int servfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	bind(servfd, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	fcntl(servfd, F_SETFL, O_NONBLOCK);
	listen(servfd, 1);
	//tableau des futurs fd de tt les clients (le 1er (adaj) est le serveur)
	pollfd adaj;
	std::vector <struct pollfd> all_fd;
	adaj.fd = servfd;
	adaj.events = POLLIN;
	adaj.revents = 0;
	all_fd.push_back(adaj);
	//la boucle principale
	std::cout << "setup fini" << std::endl;
	while (1)
	{
		int ret = poll(&all_fd[0], all_fd.size(), -1);
		if (ret > 0)
		{
			for (size_t i = 0; i < all_fd.size(); i++)
				if (all_fd[i].revents & POLLIN && i == 0)
				{
					std::cout << "coucou la tcheam" << std::endl;
					sockaddr_storage client_addr;
					socklen_t addrlen = sizeof(client_addr);
					int clientfd = accept(servfd, (sockaddr *)&client_addr, &addrlen);
					if (clientfd < 0)
						break ;
					fcntl(clientfd, F_SETFL, O_NONBLOCK);
					pollfd user;
					user.fd = clientfd;
					user.events = POLLIN;
					user.revents = 0;
					all_fd.push_back(user);
				}
		}
	}
}

