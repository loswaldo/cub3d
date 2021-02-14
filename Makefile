NAME = cub3d

HEADER = cub.h

CFLAG = -Wall -Werror -Wextra

LIBFT = libft/libft.a

RM = rm -f

OPTION = -c $< -o $@ -I ./includes

SRC = get_next_line/get_next_line.c\
      get_next_line/get_next_line_utils.c\
      main.c\
      other.c\
      parse_config.c\
      parse_rgb.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc $(CFLAG) -o $(NAME) $^
%.o: %.c
		gcc $(CFLAG) $(OPTION)

$(LIBFT):
		make -C libft/

clean:
	$(RM) $(OBJ)
	make clean -C libft/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: all clean fclean re