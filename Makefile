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
		sources/Fruit.cpp \
		sources/NibblerException.cpp \
		sources/Game.cpp \

CXXFLAGS=	-Wall -W -Wextra -I ./includes -fPIC -lpthread

LDLIBS =	-ldl -lSDL -lSDL_image -lpthread

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler


all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDLIBS)
	make -C ./sdllib/
	make -C ./ncurseslib/
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./sdllib/
	make fclean -C ./ncurseslib/

re: fclean all
