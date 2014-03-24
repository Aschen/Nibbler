##
## Makefile for  in /home/maret_a/Projets/Nibbler/cpp_nibbler
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## 
## Started on  21/03/2014 12:43
##

CXX	=	g++

SRCS	=	sources/main.cpp \
		sources/Snake.cpp \
		sources/Wall.cpp \
		sources/Fruit.cpp \
		sources/NibblerException.cpp \
		sources/Game.cpp \

CXXFLAGS=	-Wall -W -Wextra -Iincludes

LDFLAGS	=	-ldl

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
