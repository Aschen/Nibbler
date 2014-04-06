##
## Makefile for - in /home/brunne_r/Links/nibbler/sdllib
##
## Made by brunne-r
## Login   <brunne-r@epitech.net>
##
## Started on  Sat Mar 22 15:55:59 2014 brunne-r
## Last update Sun Apr  6 13:09:30 2014 brunne-r
##

##
## SDL
##

CXX	=	g++

CXXFLAGS=	-fPIC -Wall -Wextra -W `sdl-config --cflags` -I ../includes -lGL -lGLU

NAME	=	../lib_nibbler_opengl.so

SRCS	=	OpenGLDisplay.cpp \

OBJS	=	$(SRCS:.cpp=.o)

LDFLAGS	=	-I ../includes `sdl-config --libs` -lSDL_image -lglut -lGL -lGLU -lm

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) -shared $(OBJS) -lGL -lGLU

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
