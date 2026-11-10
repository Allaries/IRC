#ifndef CHANNEL
# define CHANNEL
# include "server.hpp"
# include "include.hpp"

class Server;

class Channel
{
private:
	//info basique channel
	std::string name;
	std::string topic;
	std::string password;
	//liste des membres et operator
	std::map <int, Client> all_client;
	std::map <int, Client> op;
	//Options du channel
	bool i;//invitation uniquement ?
	bool t;//changement de Topic uniquement pour les op ?
	bool k;//besoin de mdp ?
	bool l;//limite de personne ?
	int size; //nombre de user max dans le channel
public:
	Channel();
	~Channel();
};


#endif