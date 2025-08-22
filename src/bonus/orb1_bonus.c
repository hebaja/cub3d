/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb1_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:51:17 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 04:16:44 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	render_orb(t_mlx *st_mlx, t_spr *st_spr)
{
	int	y;
	int	line;

	line = st_spr->draw_start_x -1;
	while (++line < st_spr->draw_end_x)
	{
		st_spr->tex_x = (int)(256 * (line - (-st_spr->spr_width / 2
						+ st_spr->spr_screen_x))
				* st_spr->curr_sprite->width / st_spr->spr_width) / 256;
		if (st_spr->transform_y > 0 && line > 0 && line < st_mlx->screen_width
			&& st_spr->transform_y < st_mlx->z_buffer[line])
		{
			y = st_spr->draw_start_y;
			while (++y < st_spr->draw_end_y)
				put_orb_pixel(st_mlx, st_spr, y, line);
		}
	}
}

void	set_orb_main_coord(t_mlx *st_mlx, t_spr *st_spr)
{
	st_spr->curr_sprite = st_spr->sprites[st_spr->frame_pos];
	st_spr->spr_x = st_spr->pos_x - st_mlx->st_coord->p_posx;
	st_spr->spr_y = st_spr->pos_y - st_mlx->st_coord->p_posy;
	st_spr->cam_spac = 1.0 / (st_mlx->st_coord->cam_plane_x
			* st_mlx->st_coord->dir_vec_y - st_mlx->st_coord->dir_vec_x
			* st_mlx->st_coord->cam_plane_y);
	st_spr->transform_x = st_spr->cam_spac * (st_mlx->st_coord->dir_vec_y
			* st_spr->spr_x - st_mlx->st_coord->dir_vec_x * st_spr->spr_y);
	st_spr->transform_y = st_spr->cam_spac * (-st_mlx->st_coord->cam_plane_y
			* st_spr->spr_x + st_mlx->st_coord->cam_plane_x * st_spr->spr_y);
	st_spr->spr_screen_x = (int)((st_mlx->screen_width / 2)
			* (1 + st_spr->transform_x / st_spr->transform_y));
	st_spr->spr_width = abs((int)(st_mlx->screen_height
				/ st_spr->transform_y * 0.7));
	st_spr->draw_start_x = -st_spr->spr_width / 2 + st_spr->spr_screen_x;
	st_spr->draw_end_x = st_spr->spr_width / 2 + st_spr->spr_screen_x;
	st_spr->spr_height = abs((int)(st_mlx->screen_height
				/ st_spr->transform_y * 0.7));
	st_spr->draw_start_y = -st_spr->spr_height / 2 + st_mlx->screen_height / 2;
	st_spr->draw_end_y = st_spr->spr_height / 2 + st_mlx->screen_height / 2;
}

void	protect_orb_drawing(t_mlx *st_mlx, t_spr *st_spr)
{
	if (st_spr->draw_start_y < 0)
		st_spr->draw_start_y = 0;
	if (st_spr->draw_end_y >= st_mlx->screen_height)
		st_spr->draw_end_y = st_mlx->screen_height - 1;
	if (st_spr->draw_start_x < 0)
		st_spr->draw_start_x = 0;
	if (st_spr->draw_end_x >= st_mlx->screen_width)
		st_spr->draw_end_x = st_mlx->screen_width - 1;
}

void	set_orb(t_mlx *st_mlx)
{
	t_spr	*st_spr;
	size_t	time;

	if (!st_mlx->is_invert)
		st_spr = st_mlx->st_spr1;
	else
		st_spr = st_mlx->st_spr2;
	set_orb_main_coord(st_mlx, st_spr);
	protect_orb_drawing(st_mlx, st_spr);
	render_orb(st_mlx, st_spr);
	time = get_current_time();
	if (time - st_spr->anim_time >= 30)
	{
		st_spr->anim_time = time;
		if (st_spr->frame_pos == 2)
			st_spr->frame_pos = 0;
		else
			st_spr->frame_pos++;
	}
}
