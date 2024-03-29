NAME = cub3D

HEADER = cub.h \
		config.h \
		for_texture_n_sprites.h \
		parser.h

CFLAG = -Wall -Werror -Wextra

LIBFT = libft/libft.a

MLX = libmlx.dylib

RM = rm -f

INCLUDES = -I./libft -I./get_next_line

SRC =	get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		main.c \
		part_of_parser.c \
		parse_config.c \
		parse_rgb.c \
		for_window.c \
		function_for_draw.c \
		parser.c \
		sprite_draw.c \
		calculate_texture.c \
		draw_texture.c \
		general_function.c \
		key_hooks.c \
		screenshot.c \
		sprite_sort.c \
		map_validate.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	gcc -o $(NAME) $(OBJ) $(LIBFT) $(MLX) -lmlx -framework OpenGL -framework AppKit $(INCLUDES)

%.o: %.c
	gcc -MMD -c $< -o $@ $(INCLUDES)

-include $(SRC:%.c=%.d)

$(LIBFT):
	make -C libft/

$(MLX):
	make -C minilibx_mms_20200219/
	cp minilibx_mms_20200219/libmlx.dylib .

clean:
	$(RM) $(OBJ)
	$(RM) $(SRC:%.c=%.d)
	make clean -C libft/
	make clean -C minilibx_mms_20200219/

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/
	make clean -C minilibx_mms_20200219/
	$(RM) $(MLX)

re: fclean all

.PHONY: all clean fclean re