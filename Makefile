CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -fsanitize=address -g -Iincludes -Isrcs/Classes
LDFLAGS = -lGL -lGLU -lglut 

NAME = scop
SRC =	srcs/main.cpp\
		srcs/globals.cpp\
		srcs/keys.cpp\
		srcs/parsing.cpp\
		srcs/math.cpp\
		srcs/raycast.cpp\
		srcs/mouse.cpp\
		srcs/Classes/Vertex.cpp\
		srcs/Classes/Face.cpp\

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re all clean fclean
