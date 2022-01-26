# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 14:21:19 by ellarbi           #+#    #+#              #
#    Updated: 2022/01/26 01:49:05 by ellarbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# NAME		= webserv

# SRCS = 	srcs/main.cpp \
# 		srcs/Server.cpp \
# 		srcs/Request.cpp \
# 		srcs/execPostMethod.cpp \
# 		srcs/execMethod.cpp \
# 		srcs/execRequest.cpp \
# 		srcs/execCGI.cpp \
# 		srcs/Response.cpp \
# 		srcs/Config.cpp \
# 		srcs/parsing_utils.cpp \
# 		srcs/Utils.cpp \
# 		srcs/parsing.cpp \
# 		srcs/Location.cpp \
# 		srcs/Autoindex.cpp \
# 		srcs/RequestBody.cpp

# CC			=	clang++

# OBJS		=	$(SRCS:.cpp=.o)

# FLAGS	=	-Wall -Wextra -Werror -std=c++98

# all			:	$(NAME)

# $(NAME)		:	$(OBJS)
# 				$(CC) -o $(NAME) $(FLAGS) $(OBJS) 

# clean		:
# 				rm -rf $(OBJS)

# fclean		:	clean
# 				rm -f $(NAME)

# re			:	fclean all

# Test nouveau makefile :

NAME		=	webserv

DIRSRC		=	srcs
OBJD		=	obj
INCLUDE		=	srcs/include

INCLUDEF	=	$(INCLUDE)/Autoindex.hpp		\
				$(INCLUDE)/Config.hpp		\
				$(INCLUDE)/Location.hpp		\
				$(INCLUDE)/Request.hpp		\
				$(INCLUDE)/Response.hpp		\
				$(INCLUDE)/Server.hpp		\
				$(INCLUDE)/Utils.hpp		\
				$(INCLUDE)/parsing.hpp		\
				$(INCLUDE)/exceptions.hpp	\
				$(INCLUDE)/execRequest.hpp

SRC			=	main.cpp			\
				Autoindex.cpp		\
				Config.cpp			\
				Location.cpp			\
				Request.cpp			\
				RequestBody.cpp	\
				Response.cpp	\
				Server.cpp			\
				Utils.cpp		\
				execCGI.cpp		\
				execMethod.cpp	\
				execPostMethod.cpp	\
				execRequest.cpp	\
				parsing_utils.cpp	\
				parsing.cpp

OBJ			=	$(SRC:.cpp=.o)
OBJS		=	$(OBJ:%=$(OBJD)/%)

CFLAGS		=	-Wall -Wextra -Werror -std=c++98# -g3 -fsanitize=address -Ofast
CC			=	clang++
RM			=	rm -rf

DEBUG		=	0


$(NAME)		:	$(OBJD) $(OBJS) $(INCLUDEF)
				$(CC) -I ./$(INCLUDE) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJD)		:
				@mkdir $(OBJD)

$(OBJD)/%.o	:	$(DIRSRC)/%.cpp $(INCLUDEF)
				$(CC) -I ./$(INCLUDE) $(CFLAGS) -D DEBUG_ACTIVE=$(DEBUG) -o $@ -c $<

all			:	$(NAME)

clean		:
				$(RM) $(OBJS) $(OBJD)

fclean		:	clean

				$(RM) $(NAME) $(LIB)

run			:	all
				./webserv confs/webserv.conf

run_config	:	all
				./webserv confs/$(filter-out $@, $(MAKECMDGOALS)).conf

%:
	@:

bonus		:	all

re			:	fclean all

.PHONY		:	all clean re fclean
