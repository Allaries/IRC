#include "client.hpp"

int	Client::recv_usage()
{
	char	buffer[512];
	int octet = recv(this->fd, buffer, sizeof(buffer), 0);
	if (octet > 0)
	{
		buffer[octet] = '\0';
		this->inbuffer += buffer;
		std::cout << this->inbuffer;
	}
	if (octet == 0)
	{
		std::cout << this->hostname << " disconnected" << std::endl;
		return (octet);
	}
	return (octet);
}

Client::Client(int fd, std::string ip) : fd(fd), hostname(ip), inbuffer(""), outbuffer(""), nickname(""), username(""), realname(""), password_given(false), registered(false), is_op(false)
{
	//bad long le truc
}

Client::~Client()
{
}
