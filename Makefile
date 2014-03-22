##
## Makefile for  in /home/maret_a/Projets/Nibbler/cpp_nibbler
##
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
##
##
## Started on  21/03/2014 12:43
##

##
## CORE
##

CXX	=	clang++

SRCS	=	sources/main.cpp \

CXXFLAGS=	-Wall -W -Wextra -I ./includes

LDFLAGS	=	-ldl

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler


all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS)
	make -C ./sdllib/

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./sdllib/

re: fclean all
