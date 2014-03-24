##
## Makefile for  in /home/maret_a/Projets/Nibbler/cpp_nibbler
##
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
##
##
## Started on  21/03/2014 12:43
##

<<<<<<< HEAD
CXX	=	g++

SRCS	=	sources/main.cpp \
		sources/Snake.cpp \
		sources/Wall.cpp \
		sources/Fruit.cpp \
		sources/NibblerException.cpp \
		sources/Game.cpp \

CXXFLAGS=	-Wall -W -Wextra -Iincludes
=======
##
## CORE
##

CXX	=	clang++

SRCS	=	sources/main.cpp \
		sources/NibblerException.cpp \

CXXFLAGS=	-Wall -W -Wextra -I ./includes -fPIC
>>>>>>> c64b610d051bb4c4402f533c688a70ca75735a88

LDLIBS =	-ldl -lSDL -lSDL_image

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	nibbler


all:	$(NAME)

$(NAME):	$(OBJS)
<<<<<<< HEAD
	$(CXX) -o $(NAME) $(OBJS)

=======
	$(CXX) -o $(NAME) $(OBJS) $(LDLIBS)
	make -C ./sdllib/
	make -C ./ncurseslib/
>>>>>>> c64b610d051bb4c4402f533c688a70ca75735a88
clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./sdllib/
	make fclean -C ./ncurseslib/

re: fclean all
