/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:10:03 by ellarbi           #+#    #+#             */
/*   Updated: 2022/01/23 20:27:14 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Utils.hpp"

std::string     ft_itoa_cpp(int n)
{
	std::ostringstream convert;
	convert << n;
	return (convert.str());
}

int             hexa_to_int(std::string hexa)
{
    int x;
    std::stringstream ss;
    ss << std::hex << hexa;
    ss >> x;
    return x;
}

int             ft_gnl(unsigned char *buf, int buf_start)
{
    int		next_n = 0;

    if (!buf)
        return -1;
    while (1)
	{
        if (std::memchr(buf + buf_start + next_n, '\n', 1))
            return (next_n);
        next_n++;
	}
}

size_t ft_atoul(std::string ulong)
{
    size_t x;
    std::stringstream ss;
    ss << std::dec << ulong;
    ss >> x;
    return (x);
}

int	ft_atoi_parsing(const char *str)
{
	int i;
	int n;
	int neg;

	i = 0;
	n = 0;
	neg = 1;
	std::cout << str << std::endl;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	std::cout << str + i << std::endl;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i++] - '0');
	}
	
	if (str[i] != '\0')
	{
	 	std::cout << "Error listen, mauvais port" << std::endl;
	    exit(EXIT_FAILURE);
	}
	return (n * neg);
}


