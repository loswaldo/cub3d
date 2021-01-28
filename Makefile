NAME = cub3D
HEADER = cub.h
CFLAG = -Wall -Werror -Wextra
OPTION = -c I.c
SRC = *.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all