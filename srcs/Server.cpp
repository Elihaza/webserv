/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 12:02:34 by ellarbi           #+#    #+#             */
/*   Updated: 2022/02/04 21:27:17 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Server.hpp"

Server::Server(Config &conf, std::string server_conf) : 
    _rqst(*(new Request)), _main_conf(conf), _server_conf(server_conf),
    _client_socket(-1)
{
    std::string ip_str;
    try
    {
        ip_str = parsingIPAddress(server_conf, &this->_ip, &this->_port); //recup l'ip
        this->_name = parsingName(server_conf); // recup le server
        Location *general = new Location(std::string(), trimLocations(server_conf), Location());
        this->_routes.push_front(general);
        parsingLocations(this->_routes, server_conf);

        this->_root = findRootLocation(_routes);


        /*on rempli notre structure en lui specifiant la famille d'adresse, le port, l'adresse ip*/
        this->_host.sin_family = AF_INET; // AF_INET fait référence aux adresses d'internet, adresses IP spécifiquement
        this->_host.sin_addr.s_addr = inet_addr(ip_str.c_str()); // sin_addr est l'adresse IP de l'hôte , on utilise inet_addr pour convertir en binaire
        this->_host.sin_port = htons(this->_port);  //sin_port contient le numéro de port, dans l'ordre des octets du réseau
        this->_addrlen = sizeof(this->_host);
        this->_socket = socket(PF_INET, SOCK_STREAM, 0); //Création d’un socket et de son descripteur , avec le protocol tcp(SOCK_STREAM)

        int enable = 1;
        if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
            throw InternalServerError();
        /* La fonction bind() permet de lier une socket à une adresse ou un port donnés.*/
        if (bind(this->_socket, (struct sockaddr *)&this->_host, this->_addrlen) < 0)
            throw InternalServerError();
        /*La fonction listen() permet de mettre un socket en attente de connexion, avec le nombre maximal de connection*/
        if (listen(this->_socket, 32) < 0)
            throw InternalServerError();
        std::cout << "Server currently running on " << ip_str << ':' << this->_port << std::endl;
    }
    catch (std::exception &e) {
        if (e.what() == InternalServerError().what())
        {
            std::cout << "ERROR: Server on " << ip_str << ':' << this->_port;
            std::cout << " was unable to start" << std::endl;
        }
        else
            std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

Server::~Server()
{
    close(this->_socket);
    delete &this->_rqst;
    std::list<Location*>::iterator it = _routes.begin();
    for (; it != _routes.end(); it++)
        delete (*it);
}

int 	Server::exec_accept()
{ 
    if ((this->_client_socket = accept(this->_socket, (struct sockaddr *)&this->_host, (socklen_t*)&this->_addrlen)) < 0)
        throw InternalServerError();
    fcntl(this->_client_socket, F_SETFL, O_NONBLOCK);
    return (this->_client_socket);
}

int 	Server::exec_server()
{
    if (this->_rqst.parseRequest(this->_client_socket, this->_routes) < 0)
        return (this->exit_exec_server());
    if (this->_rqst.getBadRequest() == 100)
    {
        execRequest((*this));
        if (this->_rqst.parseRequest(this->_client_socket, this->_routes) < 0)
            return (this->exit_exec_server());
    }
    execRequest((*this));
    this->exit_exec_server();
    return 1;
}

int			Server::exit_exec_server()
{
    close(this->_client_socket);
    this->_client_socket = -1; 
    return (-1);
}

void		Server::clearServer()
{
    close(this->_socket);
    delete &this->_rqst;
    delete &this->_main_conf;
    std::list<Location*>::iterator it = _routes.begin();
    for (; it != _routes.end(); it++)
        delete [] (*it);
}


int			Server::getPort() const
{
    return this->_port;
}

std::string	Server::getName() const
{
    return this->_name;
}
std::string	Server::getRoot() const
{
    return this->_root->getRoot();
}
const Location	&Server::getRootLocation() const
{
    return *(this->_root);
}
int			Server::getFd() const
{
    return this->_socket;
}

int			Server::getSocket() const
{
    return this->_socket;
}

int			Server::getClientSocket() const
{
    return this->_client_socket;
}

Request		&Server::getRequest() const
{
    return this->_rqst;
}

const std::list<Location*> &Server::getRoutes() const
{
    return this->_routes;
}
