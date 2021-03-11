
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "config.h"
#include "for_texture.h"

#include "get_next_line.h"
#include "libft.h"
#include "minilibx_mms_20200219/mlx.h"

void ft_print_st(t_config *map); 				//надо снести
int			get_next_line(int fd, char **line);
void		cub();
void ft_parse_map(t_config *config, char *line);
void parser_for_rgb(char *line, t_rgb *part_of_struct);
void rgb_conversion(t_rgb *color, int *part_of_struct);
int check_line(char *line, t_config *config);
int ft_skip_spaces(char *line, int i);
int ft_is_identifier(char *line, int i, t_config *config);
int check_data_filled(t_config *config);
void map_validation(t_config *config);
void parser_for_texture(char *line, char **part_of_struct, int i);
void parser_for_resolution(t_config *config, char *line);
void for_window(t_config *config);
void my_mlx_pixel_put(t_for_win *data, int x, int y, unsigned int color);
void output(t_config *config, int is_screenshot);
void	draw_map(t_config *config);
int key_hook(int key,t_config *config);
void fill_texture(t_config *config);
void	parse(t_config *config, char *file_name);
void sprites_coord(t_config *config, t_sprites *sprite);
void draw_sprites(t_config *config, float *ZBuffer);
unsigned int	my_mlx_pixel_take(t_for_win *win, int x, int y);
void error_output_n_exit(char *str);

void			screenshot(t_config *config);
//void			continue_screenshot(t_config *config, int fd);
//static void		filling_file_screenshot(int fd, t_config *config);

#endif