/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/22 02:42:03 by hebatist         ###   ########.fr       */
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

void	catch_mouse_move(t_mlx *st_mlx)
{
	int		steps;
	double	angle;
	double	angle_step;

	if (st_mlx->mouse_x != 0)
	{
		angle = st_mlx->mouse_x * MOUSE_SENS;
		steps = 5;
		angle_step = angle / steps;
		while (steps-- > 0)
			rotate_angle(st_mlx->st_coord, angle_step);
		st_mlx->mouse_x = 0;
	}
}

void	check_inversion(t_mlx *st_mlx)
{
	if (!st_mlx->is_invert
		&& (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr1->pos_x
		&& (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr1->pos_y)
		st_mlx->is_invert_prep = 1;
	else if (st_mlx->is_invert
		&& (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr2->pos_x
		&& (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr2->pos_y)
		st_mlx->is_invert_prep = 1;
}

int	game_loop(t_mlx *st_mlx)
{
	set_keys_rotate(st_mlx);
	catch_mouse_move(st_mlx);
	ray_cast(st_mlx);
	check_inversion(st_mlx);
	if (!st_mlx->is_curtain)
	{
		render_minimap(st_mlx);
		set_orb(st_mlx);
	}
	if (st_mlx->is_invert_prep)
		prepare_for_invert(st_mlx);
	if (st_mlx->is_curtain)
		start_curtain_effect(st_mlx);
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
