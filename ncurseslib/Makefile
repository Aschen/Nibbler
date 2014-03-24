##
## Makefile for - in /home/brunne_r/Links/nibbler/sdllib
##
## Made by brunne-r
## Login   <brunne-r@epitech.net>
##
## Started on  Sat Mar 22 15:55:59 2014 brunne-r
## Last update Mon Mar 24 12:42:07 2014 brunne-r
##

##
## NCURSES
##

CXX	=	clang++

CXXFLAGS=	-fPIC -Wall -Wextra -W -I ../includes

NAME	=	libncurses.so

SRCS	=	NcursesDisplay.cpp \
		../sources/NibblerException.cpp

OBJS	=	$(SRCS:.cpp=.o)

LDFLAGS	=	-I ../includes -lncurses

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) -shared $(OBJS)
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
