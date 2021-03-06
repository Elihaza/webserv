/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:49:40 by ellarbi           #+#    #+#             */
/*   Updated: 2022/02/11 18:03:04 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Config.hpp"

# define BUFF_SIZE 1000

static void			ctr_c(int num)
{
	(void)num;
	g_ctrl_c = 1;
}

Config::Config() { g_ctrl_c = 0;}

Config::Config(std::string conf_file) : _servers()
{
	if (readConfFile(conf_file.c_str()) > 0)
	{
		createServers();
		this->_content.clear();
		select_loop();
	}
}

Config::~Config()
{
	this->_content.clear();
	std::list<Server*>::iterator it = _servers.begin();
    for (; it != _servers.end(); it++)
	{
		
        delete (*it);
	}
}

int 	Config::readConfFile(char const *path)
{
	/*fonction qui recupere la config en regardan ligne par ligne si c'est un commentaire
	si ce n'est pas un commentaire on ecrit la ligne dans _content suivi d'un retour a ligne*/
	std::fstream conf_stream(path, std::ios_base::in); //open file for reading
	char *line = NULL;
	
	if ( (conf_stream.rdstate() & std::ifstream::failbit ) != 0 )
    {
		std::cerr << "Error opening conf file (are you sure " << path << " exist ?)" << std::endl;
		return -1;
	}	
	try {
		line = new char [BUFF_SIZE];
	}
	catch (std::exception &e) {
        std::cout << e.what() << std::endl;
		return (-1);
	}
	while (1)
	{
		conf_stream.getline(line, BUFF_SIZE);
		if (!isCommentLine(line))
		{
			this->_content.append(line);
			this->_content.push_back('\n');
		}
		memset(line, '\0', BUFF_SIZE);
		if (conf_stream.eof())
			break ;
	}
	delete [] line;
	conf_stream.close();
	return 1;
}

std::string Config::singleServerConfig(size_t index)
{
	size_t open_bracket = this->_content.find_first_not_of("serv \t\n\r\v\f", index);
	size_t close_bracket = findClosingBracket(_content, open_bracket);
	
	if (this->_content[open_bracket] == '{' && _content[close_bracket] == '}')
		return (this->_content.substr(open_bracket, close_bracket - open_bracket + 1));
	return (std::string());
}

void	Config::createServers(void)
{
	/*regarde si il y a bien un ou plusieur server , check les acolade et stock les conf dans une liste 
	chainer qui prend des pointeur sur Server */
	
	size_t last_found = _content.find("server", 0);
	
	while (last_found < _content.size() && last_found < std::string::npos)
	{
		last_found += 7;
		std::string single_server_conf = getScope(_content, last_found);
		if (!single_server_conf.empty())
		{
			Server *to_push = new Server(*this, single_server_conf);
			this->_servers.push_back(to_push);
		}
		last_found = _content.find("server", last_found);
	}

}

void				Config::terminate_serv()
{
	std::list<Server*>::iterator it;

	for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
	{
		if ((*it)->getClientSocket() > -1)
			close ((*it)->getClientSocket());
		if ((*it)->getSocket() > -1)
			close ((*it)->getSocket());
	}
	exit(EXIT_SUCCESS);
}

void	Config::init_fd_sets(int *max_socket, 
	fd_set *current_sockets, fd_set *read_sockets, fd_set *write_sockets)
{
	FD_ZERO(current_sockets);
	for (std::list<Server*>::iterator it = this->_servers.begin(); it != this->_servers.end(); ++it)
	{
		
		if ((*it)->getClientSocket() == -1)
		{
			FD_SET((*it)->getSocket(), current_sockets);
			if ((*it)->getSocket() > *max_socket)
				*max_socket = (*it)->getSocket();
		}
		else
		{
			FD_SET((*it)->getClientSocket(), current_sockets);
			if ((*it)->getClientSocket() > *max_socket)
				*max_socket = (*it)->getClientSocket();
		}
	}
	FD_ZERO(read_sockets);
	FD_ZERO(write_sockets);
	std::memcpy(read_sockets, current_sockets, sizeof(*current_sockets));
	std::memcpy(write_sockets, current_sockets, sizeof(*current_sockets));
}

void	Config::select_loop()
{
	int ret;
	int max_socket = 0;
    fd_set current_sockets, read_sockets, write_sockets;
	std::list<Server*>::iterator it;
	int select_ret;

    while (1)
    {
		signal(SIGINT, &ctr_c);
		if (g_ctrl_c)
			break ;
		this->init_fd_sets(&max_socket, &current_sockets, &read_sockets, &write_sockets);
		try
		{
			/*Les fonctions select() permettent ?? un programme de surveiller plusieurs descripteurs de fichier, attendant qu'au moins l'un des descripteurs de fichier devienne ?? pr??t ??*/
			select_ret = select(max_socket + 1, &read_sockets, &write_sockets, NULL, NULL);
			if (select_ret < 0)
				break ;
			if (select_ret > 0)
			{
				for (int i = 0; i < max_socket + 1; i++)
				{
					/*FD_ISSET() v??rifie si un descripteur de fichier est utilisable */
					if (FD_ISSET(i, &read_sockets))
					{
						for (it = this->_servers.begin(); it != this->_servers.end(); ++it)
						{
							if (i == (*it)->getSocket() && (*it)->getClientSocket() < 0)
							{
								ret = (*it)->exec_accept();
								/*FD_SET() ajoute,  un descripteur de fichier dans un ensemble*/
								FD_SET(ret, &current_sockets);
								if (ret > max_socket)
									max_socket = ret;
							}
							else if (FD_ISSET(i, &write_sockets) && (*it)->getClientSocket() == i)
							{
								(*it)->exec_server();
								/*FD_CLR() suppriment,  un descripteur de fichier dans un ensemble*/
								FD_CLR(i, &current_sockets);
								FD_CLR(i, &read_sockets);
							}
						}
					}
				}
			}
		}
		catch(const std::exception& e)
		{

			std::cerr << e.what() << '\n';
		}
	}
}