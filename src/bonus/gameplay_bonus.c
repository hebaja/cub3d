/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/17 14:43:45 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	set_keys_rotate(t_mlx *st_mlx)
{
	t_coord	*coord;

	coord = st_mlx->st_coord;
	if (st_mlx->key_w)
		move_player(st_mlx, coord->dir_vec_x * MOVE,
			coord->dir_vec_y * MOVE);
	if (st_mlx->key_s)
		move_player(st_mlx, -coord->dir_vec_x * MOVE,
			-coord->dir_vec_y * MOVE);
	if (st_mlx->key_d)
		move_player(st_mlx, coord->cam_plane_x * MOVE,
			coord->cam_plane_y * MOVE);
	if (st_mlx->key_a)
		move_player(st_mlx, -coord->cam_plane_x * MOVE,
			-coord->cam_plane_y * MOVE);
	if (st_mlx->key_left)
		rotate_angle(coord, -ROTATE);
	if (st_mlx->key_right)
		rotate_angle(coord, ROTATE);
}

int	game_loop(t_mlx *st_mlx)
{
	int		steps;
	double	angle;
	double	angle_step;

	set_keys_rotate(st_mlx);
	if (st_mlx->mouse_x != 0)
	{
		angle = st_mlx->mouse_x * MOUSE_SENS;
		steps = 5;
		angle_step = angle / steps;
		while (steps-- > 0)
			rotate_angle(st_mlx->st_coord, angle_step);
		st_mlx->mouse_x = 0;
	}
	if (!st_mlx->is_screen_flip)
	{
		ray_cast(st_mlx);
		render_minimap(st_mlx);
	}
	else
	{
		if (!(st_mlx->st_coord->dir_vec_x >= -0.05 && st_mlx->st_coord->dir_vec_x <= 0.05))
		{
			rotate_angle(st_mlx->st_coord, -ROTATE);
			ray_cast(st_mlx);
			render_minimap(st_mlx);
		}
		else
		{
			t_img *tmp_texture;
			tmp_texture = st_mlx->ea_texture;
			st_mlx->ea_texture = st_mlx->we_texture;
			st_mlx->we_texture = tmp_texture;
			st_mlx->is_screen_flip = 0;
			if (st_mlx->is_invert)
				st_mlx->is_invert = 0;
			else
				st_mlx->is_invert = 1;
		}
	}
	return (0);
}

void	init_gameplay(t_mlx *st_mlx)
{
	mlx_hook(st_mlx->win, 2, (1L << 0), key_press, st_mlx);
	mlx_hook(st_mlx->win, 3, (1L << 1), key_release, st_mlx);
	mlx_hook(st_mlx->win, 17, 0, close_window, st_mlx);
	mlx_loop_hook(st_mlx->mlx, game_loop, st_mlx);
	mlx_loop(st_mlx->mlx);
}
