/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/29 20:11:43 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_file
{
	char	**file_content;
	char	**map;
	char	**dup_map;
	char	*path;
	int		width;
	int		height;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color[3];
	int		c_color[3];
	int		map_start;
	int		map_finish;
	int		player_pos;
	int		player_x;
	int		player_y;
}	t_file;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*screen_img;
	char	*screen_img_addr;
	int		screen_img_bpp;
	int		screen_img_endian;
	int		screen_height;
	int		screen_width;
	int		line_length;
	t_file	*st_file;
}	t_mlx;

t_file	*build_st_file(char *map_path);
t_mlx	*build_st_mlx(t_file *st_file, int screen_width, int screen_height);
void	clean_st_file(t_file *st_file);
void	open_map_error(void);
void	case_error_reading_file(t_file *st_file);
void	put_error(char *msg, char *data);
void	put_perror(char *msg);
void	put_error_char(char *msg, char elem);
void	clean_args(char **args);
void	clean_map(char **map);
void	expanded_map(char **map, t_file *st_file);
char	**fill_duplicate_map(int height, int width);
int		is_blank_line(char *line);
int		elements_complete(t_file *st_file);
int		invalid_line(char *line);
int		check_map(char **file_content, t_file *st_file);
int		is_valid_map_path(int argc, char **argv);
int		parse_elements(t_file *st_file);
int		check_texture_element(char *elem, char *line, t_file *st_file);
int		check_color_line(char *line, char elem);
int		print_error(char *str);
int		is_not_coord(char *line);
int		valid_map(t_file	*st_file);
int		is_map(char *line);
int		get_height_file(char *map_path);
int		get_height_map(char **map);
int		get_width_map(char **map);
int		map_flood_fill(char **map, int x, int y);
int		get_last_valid(char *line);
int		valid_character(char **map);
void	ray_cast(t_mlx *st_mlx, int width, int height, int dirX, int dirY, float planeX, float planeY, int screen_column);

/* DEBU */
void	print_map(char **map);

#endif
