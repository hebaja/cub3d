/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_movement_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/08 05:43:03 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	is_not_valid_move(double new_x, double new_y, t_mlx *st_mlx)
{
	t_file	*st_file;
	char	**map;
	int		map_x;
	int		map_y;

	st_file = st_mlx->st_file;
	map = st_file->map;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (new_x < 0 || new_y < 0)
		return (1);
	if (map_y < 0 || map_y >= st_file->height)
		return (1);
	if (map_x < 0 || map_x >= (int)ft_strlen(map[map_y]))
		return (1);
	if (map[(int)(new_y + RADIUS)][(int)(new_x + RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y + RADIUS)][(int)(new_x - RADIUS)] == '1'
	|| map[(int)(new_y - RADIUS)][(int)(new_x + RADIUS)] == '1')
		return (1);
	if (map[map_y][map_x] == '1' || map[map_y][map_x] == ' ')
		return (1);
	return (0);
}

void	move_player(t_mlx *st_mlx, double move_x, double move_y)
{
	if (!is_not_valid_move(st_mlx->st_coord->p_posx + move_x,
			st_mlx->st_coord->p_posy, st_mlx))
		st_mlx->st_coord->p_posx += move_x;
	if (!is_not_valid_move(st_mlx->st_coord->p_posx,
			st_mlx->st_coord->p_posy + move_y, st_mlx))
		st_mlx->st_coord->p_posy += move_y;
}

int	key_press(int key, t_mlx *st_mlx)
{
	if (key == KEY_ESC)
	{
		clean_all(st_mlx);
		exit(EXIT_SUCCESS);
	}
	if (key == KEY_UP || key == KEY_W)
		st_mlx->key_w = 1;
	else if (key == KEY_DOWN || key == KEY_S)
		st_mlx->key_s = 1;
	else if (key == KEY_D)
		st_mlx->key_d = 1;
	else if (key == KEY_A)
		st_mlx->key_a = 1;
	else if (key == KEY_LEFT)
		st_mlx->key_left = 1;
	else if (key == KEY_RIGHT)
		st_mlx->key_right = 1;
	return (0);
}

int	key_release(int key, t_mlx *st_mlx)
{
	if (key == KEY_UP || key == KEY_W)
		st_mlx->key_w = 0;
	else if (key == KEY_DOWN || key == KEY_S)
		st_mlx->key_s = 0;
	else if (key == KEY_D)
		st_mlx->key_d = 0;
	else if (key == KEY_A)
		st_mlx->key_a = 0;
	else if (key == KEY_LEFT)
		st_mlx->key_left = 0;
	else if (key == KEY_RIGHT)
		st_mlx->key_right = 0;
	return (0);
}

void	rotate_angle(t_coord *coord, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = coord->dir_vec_x;
	old_plane_x = coord->cam_plane_x;
	coord->dir_vec_x = coord->dir_vec_x * cos(angle)
		- coord->dir_vec_y * sin(angle);
	coord->dir_vec_y = old_dir_x * sin(angle)
		+ coord->dir_vec_y * cos(angle);
	coord->cam_plane_x = coord->cam_plane_x * cos(angle)
		- coord->cam_plane_y * sin(angle);
	coord->cam_plane_y = old_plane_x * sin(angle)
		+ coord->cam_plane_y * cos(angle);
}
