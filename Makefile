##
## Makefile for  in /home/maret_a/Projets/Nibbler/cpp_nibbler
##
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
##
##
## Started on  21/03/2014 12:43
##

CXX	=	clang++

SRCS	=	sources/main.cpp \
		sources/Snake.cpp \
		sources/Wall.cpp \
		sources/Powerup.cpp \
		sources/NibblerException.cpp \
		sources/Game.cpp \
		sources/Portal.cpp \

CXXFLAGS=	-Wall -W -Wextra -I ./includes -fPIC

LDLIBS =	-ldl -lSDL -lSDL_image -lSDL_gfx -lpthread -lncurses

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler


all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDLIBS)
	make -C ./sdllib/
	make -C ./ncurseslib/
	make -C ./opengllib/

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./sdllib/
	make fclean -C ./ncurseslib/
	make fclean -C ./opengllib/

re: fclean all
