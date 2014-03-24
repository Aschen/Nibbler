##
## Makefile for - in /home/brunne_r/Links/nibbler/sdllib
##
## Made by brunne-r
## Login   <brunne-r@epitech.net>
##
## Started on  Sat Mar 22 15:55:59 2014 brunne-r
## Last update Mon Mar 24 17:18:57 2014 brunne-r
##

##
## SDL
##

CXX	=	clang++

CXXFLAGS=	-fPIC -Wall -Wextra -W `sdl-config --cflags` -I ../includes

NAME	=	../libsdl.so

SRCS	=	SdlDisplay.cpp \
		../sources/NibblerException.cpp

OBJS	=	$(SRCS:.cpp=.o)

LDFLAGS	=	-I ../includes `sdl-config --libs` -lSDL_image

all:		$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) -shared $(OBJS)
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
