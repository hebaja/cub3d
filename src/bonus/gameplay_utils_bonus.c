/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 22:26:51 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/19 23:39:57 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

void	try_open_door(t_mlx *st_mlx)
{
	int	check_x;
	int	check_y;

	check_x = (int)(st_mlx->st_coord->p_posx + st_mlx->st_coord->dir_vec_x);
	check_y = (int)(st_mlx->st_coord->p_posy + st_mlx->st_coord->dir_vec_y);
	if (st_mlx->st_file->map[check_y][check_x] == 'D')
	{
		// st_mlx->is_door_open = !st_mlx->is_door_open;
		st_mlx->is_door_anim = 1;
		printf("check_x=%d check_y=%d cell=%c open=%d\n", check_x, check_y, st_mlx->st_file->map[check_y][check_x], st_mlx->is_door_open);
		// if (door)
		// {
		// 	printf("porta encontrada em (%d,%d) offset=%.2f\n", door->x, door->y, door->offset);
		// 	if (door->offset <= 0.0 && !door->is_opening)
		// 	{
		// 		door->is_opening = 1;
		// 		door->is_closing = 0;
		// 	}
		// 	else if (door->offset >= 1.0 && !door->is_closing)
		// 	{
		// 		door->is_closing = 1;
		// 		door->is_opening = 0;
		// 	}
		// }
		// else
  //   		printf("nenhuma porta encontrada!\n");
	}
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
		{
			printf("teclas apertada: %d\n", key);
			try_open_door(st_mlx);
		}
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
