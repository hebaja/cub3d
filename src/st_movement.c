/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/18 17:56:57 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_door	*find_door(t_file *st_file, int x, int y)
{
	t_door	*door;

	door = st_file->door;
	while (door)
	{
		if (door->x == x && door->y == y)
			return (door);
		door = door->next;
	}
	return (NULL);
}

void	try_open_door(t_mlx *st_mlx)
{
	int	check_x;
	int	check_y;
	t_door	*door;

	check_x = (int)(st_mlx->st_coord->p_posx + st_mlx->st_coord->dir_vec_x);
	check_y = (int)(st_mlx->st_coord->p_posy + st_mlx->st_coord->dir_vec_y);
	if (st_mlx->st_file->map[check_y][check_x] == 'D')
	{
		door = find_door(st_mlx->st_file, check_x, check_y);
		if (door)
		{
			if (door->offset <= 0.0 && !door->is_opening)
			{
				door->is_opening = 1;
				door->is_closing = 0;
			}
			else if (door->offset >= 1.0 && !door->is_closing)
			{
				door->is_closing = 1;
				door->is_opening = 0;
			}
		}
	}
}

int	mouse_move(int x, int y, t_mlx *st_mlx)
{
	int  		diff_x;
	int			center_win;

	(void)y;
	center_win = st_mlx->screen_width / 2;
	diff_x = x - center_win;
	if (diff_x < -300 || diff_x > 300)
	{
		mlx_mouse_move(st_mlx->mlx, st_mlx->win, center_win, st_mlx->screen_height / 2);
		return (0);
	}
	st_mlx->mouse_x += diff_x;
	if (x != center_win)
		mlx_mouse_move(st_mlx->mlx, st_mlx->win, center_win, st_mlx->screen_height / 2);
	return (0);
}

void	set_keys_rotate(t_mlx *st_mlx)
{
	t_coord	*coord;

	coord = st_mlx->st_coord;
	if (st_mlx->key_w)
		move_player(st_mlx, coord->dir_vec_x * MOVE, coord->dir_vec_y * MOVE);
	if (st_mlx->key_s)
		move_player(st_mlx, -coord->dir_vec_x * MOVE, -coord->dir_vec_y * MOVE);
	if (st_mlx->key_d)
		move_player(st_mlx, coord->cam_plane_x * MOVE, coord->cam_plane_y * MOVE);
	if (st_mlx->key_a)
		move_player(st_mlx, -coord->cam_plane_x * MOVE, -coord->cam_plane_y * MOVE);
	if (st_mlx->key_left)
		rotate_angle(coord, -ROTATE);
	if (st_mlx->key_right)
		rotate_angle(coord, ROTATE);
}

int	game_loop(void *param)
{
	t_mlx	*st_mlx;
	int		steps;
	double	angle;
	double	angle_step;

	st_mlx = (t_mlx *)param;
	set_keys_rotate(st_mlx);
	if (st_mlx->mouse_x != 0)
	{
		angle = st_mlx->mouse_x * MOUSE_SENS;
		steps = 5;
		angle_step = angle / steps;
		while (steps-- > 0)
		{
			rotate_angle(st_mlx->st_coord, angle_step);
		}
		st_mlx->mouse_x = 0;
	}
	update_door(st_mlx->st_file);
	ray_cast(st_mlx);
	return (0);
}


void	init_event(t_mlx *st_mlx)
{
	mlx_hook(st_mlx->win, 2, (1L << 0), key_press, st_mlx);
	mlx_hook(st_mlx->win, 3, (1L << 1), key_release, st_mlx);
	mlx_hook(st_mlx->win, 17, 0, close_window, st_mlx);
	mlx_hook(st_mlx->win, 6, (1L << 6), mouse_move, st_mlx);
	mlx_loop_hook(st_mlx->mlx, game_loop, st_mlx);
	mlx_loop(st_mlx->mlx);
}
