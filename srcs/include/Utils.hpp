/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 12:10:32 by ellarbi           #+#    #+#             */
/*   Updated: 2022/01/23 20:25:50 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "../../webserv.hpp"

std::string     ft_itoa_cpp(int n);
int             hexa_to_int(std::string hexa);
int             ft_gnl(unsigned char *buf, int buf_start);
size_t          ft_atoul(std::string ulong);
int             ft_atoi_parsing(const char *str);

template <typename T>
T *MyRealloc( T*& src, int oldSize, int newSize ) 
{
  T *dst = new T[newSize];

  if ( newSize < oldSize )
    oldSize = newSize;

  std::memcpy(dst, src, oldSize);

  // Free the old block and reuse the pointer
  delete[] src;
  src = dst;

  // Return the pointer for convenience
  return src;
}

#endif