NAME = cub3D

HEADER = cub.h

CFLAG = -Wall -Werror -Wextra

LIBFT = libft/libft.a

MLX = libmlx.dylib

RM = rm -f

OPTION = -c $< -o $@ -I ./includes

SRC = get_next_line/get_next_line.c \
      get_next_line/get_next_line_utils.c \
      main.c \
      other.c \
      parse_config.c \
      parse_rgb.c \
      for_window.c \
      function_for_draw.c \
      parser.c \
      sprite_draw.c \
      calculate_texture.c \
      draw_texture.c \
      general_function_for_drawing.c \
      key_hooks.c \
      screenshoot.c



OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	gcc  -o $(NAME) $(OBJ) $(LIBFT) -lmlx -framework OpenGL -framework AppKit -I./includes

%.o: %.c
		gcc  $(OPTION)

$(LIBFT):
		make -C libft/

$(MLX):
		make -C minilibx_mms_20200219/
		cp minilibx_mms_20200219/libmlx.dylib .

clean:
	$(RM) $(OBJ)
	make clean -C libft/
	make clean -C minilibx_mms_20200219/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/
	make clean -C minilibx_mms_20200219/
	$(RM) $(MLX)

re: fclean all

.PHONY: all clean fclean re