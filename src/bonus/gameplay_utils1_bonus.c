/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_utils1_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/09/01 20:41:34 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	try_open_door(t_mlx *st_mlx)
{
	int	check_x;
	int	check_y;

	check_x = (int)(st_mlx->st_coord->p_posx + st_mlx->st_coord->dir_vec_x);
	check_y = (int)(st_mlx->st_coord->p_posy + st_mlx->st_coord->dir_vec_y);
	if (st_mlx->st_file->map[check_y][check_x] == 'D')
		st_mlx->st_file->doors->is_door_anim = 1;
}

int	key_press(int key, t_mlx *st_mlx)
{
	if (!st_mlx->is_invert_prep && !st_mlx->is_curtain)
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
		else if (key == KEY_SPACE)
			try_open_door(st_mlx);
	}
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
