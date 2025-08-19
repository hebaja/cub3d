/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/18 14:47:50 by hebatist         ###   ########.fr       */
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


void draw_screen(t_mlx *st_mlx, double cx, double cy, double dx, double dy)
{
	int y;
	int x;

	y = -1;
	while (++y < st_mlx->screen_height)
	{
		x = -1;
		while (++x < st_mlx->screen_width)
		{
			double  vx = x - cx;
			double  vy = y - cy;
			double  side = vx * dy - vy * dx;
			if (side >= 0)
				ft_mlx_pixel_put(st_mlx->screen, x, y, st_mlx->bar_color_1);
			else
				ft_mlx_pixel_put(st_mlx->screen, x, y, st_mlx->bar_color_2);
		}
	}
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->screen->img, 0, 0);
}

int     draw_two_bars(t_mlx *st_mlx)
{
	double  cx = st_mlx->screen_width / 2.0;
	double  cy = st_mlx->screen_height / 2.0;
	double  theta = st_mlx->angle * M_PI / 180.0;
	double  dx = cos(theta);
	double  dy = sin(theta);
	size_t  time;

	
	
		if (st_mlx->is_flipping)
		{
			time = get_current_time();
			if (time - st_mlx->anim_time >= 30)
				draw_screen(st_mlx, cx, cy, dx, dy);
			st_mlx->angle++;
			printf("%f\n", st_mlx->angle);
			if (st_mlx->angle == 180.0)
			{
				st_mlx->angle = 0;
				st_mlx->is_flipping_done = 1;
				int tmp_color = st_mlx->bar_color_1;
				st_mlx->bar_color_1 = st_mlx->bar_color_2;
				st_mlx->bar_color_2 = tmp_color;
			}
		}
		else
			draw_screen(st_mlx, cx, cy, dx, dy);
	
	return (0);
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

	// if (!st_mlx->is_curtain)
	// {
		ray_cast(st_mlx);
		if (!st_mlx->is_curtain)
			render_minimap(st_mlx);
	// }
	if (st_mlx->is_curtain)
	{
		if (!st_mlx->curtain_dir)
			st_mlx->curtain_y += 5;
		else
			st_mlx->curtain_y -= 5;

		if (!st_mlx->curtain_dir && st_mlx->curtain_y == st_mlx->screen_height)
		{
			st_mlx->curtain_dir = 1;
			t_img *tmp_texture;
			tmp_texture = st_mlx->ea_texture;
			st_mlx->ea_texture = st_mlx->we_texture;
			st_mlx->we_texture = tmp_texture;
			if (st_mlx->is_invert)
				st_mlx->is_invert = 0;
			else
				st_mlx->is_invert = 1;
		}
		if (st_mlx->curtain_dir && st_mlx->curtain_y == 0)
		{
			st_mlx->curtain_dir = 0;
			st_mlx->is_curtain = 0;
		}
	}

	/*
	if (!st_mlx->is_flipping_prep && !st_mlx->is_flipping)
	{
		ray_cast(st_mlx);
		render_minimap(st_mlx);
	}
	else if (st_mlx->is_flipping_prep && !st_mlx->is_flipping)
	{
		if (!(st_mlx->st_coord->dir_vec_x >= -0.05 && st_mlx->st_coord->dir_vec_x <= 0.05))
		{
			rotate_angle(st_mlx->st_coord, -ROTATE);
			ray_cast(st_mlx);
			render_minimap(st_mlx);
		}
		else
			st_mlx->is_flipping_prep = 0;
	}
	else if (!st_mlx->is_flipping_prep && st_mlx->is_flipping)
	{
		if (!st_mlx->is_flipping_done)
			draw_two_bars(st_mlx);
		else
		{


			// t_img *tmp_texture;
			// tmp_texture = st_mlx->ea_texture;
			// st_mlx->ea_texture = st_mlx->we_texture;
			// st_mlx->we_texture = tmp_texture;
			// if (st_mlx->is_invert)
			// 	st_mlx->is_invert = 0;
			// else
			// 	st_mlx->is_invert = 1;
			// 
			// ft_printf("flip done %d\n", st_mlx->is_invert);

		}

	}
	*/
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
