#ifndef CLIENT
# define CLIENT
#include "include.hpp"

class Client
{
private:
	int fd;
	std::string hostname;
	//Buffer (pour recv() et send())
	std::string inbuffer;
	std::string outbuffer;
	// User info
	std::string nickname;
	std::string username;
	std::string realname;
	bool password_given;
	bool registered;
	bool is_op;

public:
	void	setPassOk(bool b);
	void	setRegisOk(bool b);
	void	setOpOk(bool b);
	int		recv_usage();
	bool	is_cmd(std::string &line);
	Client(int fd, std::string ip);
	~Client();
};

#endif