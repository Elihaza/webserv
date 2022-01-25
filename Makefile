# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 14:21:19 by ellarbi           #+#    #+#              #
#    Updated: 2022/01/23 20:23:56 by ellarbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= webserv

SRCS = 	srcs/main.cpp \
		srcs/Server.cpp \
		srcs/Request.cpp \
		srcs/execPostMethod.cpp \
		srcs/execMethod.cpp \
		srcs/execRequest.cpp \
		srcs/execCGI.cpp \
		srcs/Response.cpp \
		srcs/Config.cpp \
		srcs/parsing_utils.cpp \
		srcs/Utils.cpp \
		srcs/parsing.cpp \
		srcs/Location.cpp \
		srcs/Autoindex.cpp \
		srcs/RequestBody.cpp

CC			=	clang++

OBJS		=	$(SRCS:.cpp=.o)

FLAGS	=	-Wall -Wextra -Werror -std=c++98

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) -o $(NAME) $(FLAGS) $(OBJS) 

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean all
			

