/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 09:47:15 by ellarbi           #+#    #+#             */
/*   Updated: 2022/01/23 20:24:53 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "../../webserv.hpp"

class Config
{
	private:
		Config();
		std::string			_content;
		std::list<Server*>	_servers;

		std::string 		singleServerConfig(size_t index);
		void				select_loop();
		void				terminate_serv();
		void				init_fd_sets(int *max_socket, 
			fd_set	*current_sockets, fd_set *read_sockets, fd_set *write_socket);

	public:
		Config(std::string conf_file);
		~Config();

		int 	readConfFile(char const *path);
		void	createServers(void);
};

#endif
