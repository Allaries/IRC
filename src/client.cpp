#include "../include/client.hpp"
#include "../include/command.hpp"

int	Client::recv_usage()
{
	char	buffer[512];
	int octet = recv(this->fd, buffer, sizeof(buffer), 0);
	if (octet > 0)
	{
		buffer[octet] = '\0';
		this->inbuffer += buffer;
	}
	if (octet == 0)
	{
		std::cout << this->hostname << " disconnected" << std::endl;
		return (octet);
	}
	return (octet);
}

bool	Client::is_cmd(std::string& outLine)
{
	std::string::size_type	pos = this->inbuffer.find("\r\n");
	size_t					delimLen = 2;

	if (pos == std::string::npos)
	{
		pos = this->inbuffer.find("\n");
		delimLen = 1;
	}
	if (pos == std::string::npos)
		return false;

	outLine = this->inbuffer.substr(0, pos);
	this->inbuffer.erase(0, pos + delimLen);
	return true;
}


void	Client::setPassOk(bool b)
{
	this->password_given = b;
}

Client::Client(int fd, std::string ip) : fd(fd), hostname(ip), inbuffer(""), outbuffer(""), nickname(""), username(""), realname(""), password_given(false), registered(false), is_op(false)
{
	//bad long le truc
}

Client::~Client()
{
}
