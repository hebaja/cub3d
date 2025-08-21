/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:55:14 by dbatista          #+#    #+#             */
/*   Updated: 2025/08/20 17:01:50 by hebatist         ###   ########.fr       */
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

int ft_mlx_pixel_get(t_img *st_img, int x, int y)
{
    char    *dst;

	if (x < 0 || x >= st_img->width || y < 0 || y >= st_img->height)
		return 0; 
    dst = st_img->img_addr + (y * st_img->size_line + x * (st_img->bpp / 8));
    return (*(unsigned int *)dst);
}

void	render_orb(t_mlx *st_mlx, t_spr *st_spr)
{
	int	line;
	int	tex_x;
	int	tex_y;
	int	y;
	int	d;
	int	color;

	y = -1;
	line = st_spr->draw_start_x;
	while (line < st_spr->draw_end_x)
	{
		tex_x = (int)(256 * (line - (-st_spr->spr_width / 2 + st_spr->spr_screen_x))
		   * st_spr->sprite->width / st_spr->spr_width) / 256;

		if (st_spr->transform_y > 0 && line > 0 && line < st_mlx->screen_width
			&& st_spr->transform_y < st_mlx->z_buffer[line])
		{
			y = st_spr->draw_start_y;
			while (++y < st_spr->draw_end_y)
			{
				d = (y - st_mlx->screen_height / 2 + st_spr->spr_height / 2) * 256;
				tex_y = ((d * st_spr->sprite->height) / st_spr->spr_height) / 256;
				
				color = ft_mlx_pixel_get(st_spr->sprite, tex_x, tex_y);
				if ((color & 0x00FFFFFF) != 0)
					ft_mlx_pixel_put(st_mlx->screen, line, y, color);
			}
		}
		line++;
	}
}

void	set_orb(t_mlx *st_mlx)
{
	t_spr	*st_spr;

	if (!st_mlx->is_invert)
		st_spr = st_mlx->st_spr1;
	else
		st_spr = st_mlx->st_spr2;

	st_spr->spr_x = st_spr->pos_x - st_mlx->st_coord->p_posx;
	st_spr->spr_y = st_spr->pos_y - st_mlx->st_coord->p_posy;

	st_spr->cam_spac = 1.0 / (st_mlx->st_coord->cam_plane_x * st_mlx->st_coord->dir_vec_y - st_mlx->st_coord->dir_vec_x * st_mlx->st_coord->cam_plane_y);
	
	st_spr->transform_x = st_spr->cam_spac * (st_mlx->st_coord->dir_vec_y * st_spr->spr_x - st_mlx->st_coord->dir_vec_x * st_spr->spr_y);
	st_spr->transform_y = st_spr->cam_spac * (-st_mlx->st_coord->cam_plane_y * st_spr->spr_x + st_mlx->st_coord->cam_plane_x * st_spr->spr_y);

	st_spr->spr_screen_x = (int)((st_mlx->screen_width / 2) * (1 + st_spr->transform_x / st_spr->transform_y));

	st_spr->spr_width = abs((int)(st_mlx->screen_height / st_spr->transform_y));
	st_spr->draw_start_x = -st_spr->spr_width / 2 + st_spr->spr_screen_x;
	st_spr->draw_end_x = st_spr->spr_width / 2 + st_spr->spr_screen_x;

	st_spr->spr_height = abs((int)(st_mlx->screen_height / st_spr->transform_y));
	st_spr->draw_start_y = -st_spr->spr_height / 2 + st_mlx->screen_height / 2;
	st_spr->draw_end_y = st_spr->spr_height / 2 + st_mlx->screen_height / 2;

	if (st_spr->draw_start_y < 0)
		st_spr->draw_start_y = 0;
	if (st_spr->draw_end_y >= st_mlx->screen_height)
		st_spr->draw_end_y = st_mlx->screen_height - 1;

	if (st_spr->draw_start_x < 0)
		st_spr->draw_start_x = 0;
	if (st_spr->draw_end_x >= st_mlx->screen_width)
		st_spr->draw_end_x = st_mlx->screen_width - 1;
	render_orb(st_mlx, st_spr);
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
	ray_cast(st_mlx);




	if (!st_mlx->is_invert && (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr1->pos_x && (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr1->pos_y)
		st_mlx->is_invert_prep = 1;
	else if (st_mlx->is_invert && (int)st_mlx->st_coord->p_posx == (int)st_mlx->st_spr2->pos_x && (int)st_mlx->st_coord->p_posy == (int)st_mlx->st_spr2->pos_y)
		st_mlx->is_invert_prep = 1;




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
