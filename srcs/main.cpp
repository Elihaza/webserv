/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 10:54:51 by ellarbi           #+#    #+#             */
/*   Updated: 2022/02/13 16:40:37 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../webserv.hpp"

int main (int ac, char **av) //the conf file is the only possible argument 
{
	if (ac == 2) // use the given conf file
		Config(std::string(av[1]));
	else if (ac == 1) // use a default conf file
		Config("confs/default.conf");
	else // ERROR
	{
		std::cout << "ERROR" << std::endl;
		return -1;
	}
	return 0;
}