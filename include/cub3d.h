/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:38:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/05 22:55:48 by dbatista         ###   ########.fr       */
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

# define KEY_PRESS		2
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define KEY_UP			65362
# define KEY_DOWN		65364
# define KEY_A			97
# define KEY_D			100
# define KEY_W			119
# define KEY_S			115
# define RADIUS			0.1
# define FOV			0.66
# define MOVE			0.05
# define ROTATE			0.02
# define MOUSE_SENS		0.005

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

typedef struct s_coord
{
	int		curr_map_x;
	int		curr_map_y;
	int		side_hit;
	int		wall_tex_x;
	int		wall_tex_y;
	char	player_dir;
	double	dir_vec_x;
	double	dir_vec_y;
	double	cam_plane_x;
	double	cam_plane_y;
	double	camera_x;
	double	p_posx;
	double	p_posy;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	double	wall_tex_pos;
	double	wall_tex_step;	
}	t_coord;

typedef struct s_img
{
	void	*img;
	char	*img_addr;
	int		width;
	int		height;
	int		size_line;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*screen;
	t_img	*no_texture;
	t_img	*so_texture;
	t_img	*we_texture;
	t_img	*ea_texture;
	t_img	*curr_texture;
	int		screen_height;
	int		screen_width;
	int		c_color;
	int		f_color;
	int		mouse_x;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	t_file	*st_file;
	t_coord	*st_coord;
}	t_mlx;

t_file	*build_st_file(char *map_path);
t_coord	*build_st_coord(t_file *st_file);
t_mlx	*build_st_mlx(t_file *st_file, t_coord *st_coord);
void	init_event(t_mlx *st_mlx);
void	exit_mlx(t_mlx *st_mlx);
void	clean_st_file(t_file *st_file);
void	clean_st_mlx(t_mlx *st_mlx);
void	clean_all(t_mlx *st_mlx);
void	open_map_error(void);
void	case_error_reading_file(t_file *st_file);
void	put_error(char *msg, char *data);
void	put_perror(char *msg);
void	put_error_char(char *msg, char elem);
void	clean_args(char **args);
void	clean_map(char **map);
void	expanded_map(char **map, t_file *st_file);
void	draw_vertical_line(t_mlx *st_mlx, int screen_column);
void	rotate_angle(t_coord *coord, double angle);
void    move_player(t_mlx *st_mlx, double move_x, double move_y);
char	**fill_duplicate_map(int height, int width);
int		is_not_valid_move(double new_x, double new_y, t_mlx *st_mlx);
int		key_release(int key, t_mlx *st_mlx);
int		key_press(int key, t_mlx *st_mlx);
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
int		handle_input(int keycode, t_mlx *st_mlx);
int		close_window(t_mlx *st_mlx);
void	ray_cast(t_mlx *st_mlx);

/* DEBU */
void	print_map(char **map);

#endif
