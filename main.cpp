#include "include.hpp"
#include "server.hpp"


void setup_address(const char *port_str, struct addrinfo **res) 
{
    struct addrinfo hints;
    
    std::memset(&hints, 0, sizeof(hints));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags    = AI_PASSIVE;

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
	Server service(servfd);
	std::cout << "setup fini" << std::endl;
	// service contient le tableau de pollfd  avec le fd du server qui ecoute et contiendra tt les prochains fd de clients
	service.loop();
}

