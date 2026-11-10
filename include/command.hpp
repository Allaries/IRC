#ifndef COMMAND
# define COMMAND
# include "include.hpp" 

class Command
{
private:
	//litteralement du parsing minishell
	//le 1er truc c'est la commande (JOIN, KICK, NICK ...)
	//et le reste ensuite c'est les arguments (t'as des fonction qui ont besoin de par exemple le nom du bougue que tu veux MP + message ou alors juste ton nickname
	//on va avoir une fonction qui va parser, et une autre qui va executer la cmd (MAIS des fois c'est le serv principal, d'autre fois les channel ou juste la classe client qui va les executer)
	//bref une fois le parsing fait on pourra coder les commandes et les tester
	//on va faire le parsing
	std::string cmd;
	std::vector<std::string> args;
public:
	Command(/* args */);
	~Command();
};

Command::Command(/* args */)
{
}

Command::~Command()
{
}


#endif