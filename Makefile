##
## Makefile for  in /home/maret_a/Projets/Nibbler/cpp_nibbler
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## 
## Started on  21/03/2014 12:43
##

CC	=	clang++

SRCS	=	sources/main.cpp \

CXXFLAGS=	-Wall -W -Wextra

LDFLAGS	=	-ldl

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
