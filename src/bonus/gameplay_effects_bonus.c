/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay_effects_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:50:44 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/22 04:00:54 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	swap_maps(t_mlx *st_mlx)
{
	char	**map_tmp;

	map_tmp = st_mlx->st_file->map;
	st_mlx->st_file->map = st_mlx->st_file->inv_map;
	st_mlx->st_file->inv_map = map_tmp;
}

void	swap_side_texures(t_mlx *st_mlx)
{
	t_img	*tmp_texture;

	tmp_texture = st_mlx->ea_texture;
	st_mlx->ea_texture = st_mlx->we_texture;
	st_mlx->we_texture = tmp_texture;
}

void	prepare_for_invert(t_mlx *st_mlx)
{
	if (!(st_mlx->st_coord->dir_vec_x >= -0.05
			&& st_mlx->st_coord->dir_vec_x <= 0.05))
	{
		rotate_angle(st_mlx->st_coord, -ROTATE);
		ray_cast(st_mlx);
		render_minimap(st_mlx);
	}
	else
	{
		st_mlx->is_curtain = 1;
		st_mlx->is_invert_prep = 0;
	}
}

void	start_curtain_effect(t_mlx *st_mlx)
{
	if (!st_mlx->curtain_dir)
		st_mlx->curtain_y += CURTAIN_SPEED;
	else
		st_mlx->curtain_y -= CURTAIN_SPEED;
	if (!st_mlx->curtain_dir && st_mlx->curtain_y == st_mlx->screen_height)
	{
		st_mlx->curtain_dir = 1;
		if (st_mlx->is_invert)
			st_mlx->is_invert = 0;
		else
			st_mlx->is_invert = 1;
		swap_maps(st_mlx);
		swap_side_texures(st_mlx);
		st_mlx->st_coord->p_posx = (st_mlx->st_file->map_width)
			- st_mlx->st_coord->p_posx - 1;
		st_mlx->st_spr2->pos_x = (st_mlx->st_file->map_width)
			- st_mlx->st_spr2->pos_x - 1;
	}
	if (st_mlx->curtain_dir && st_mlx->curtain_y == 0)
	{
		st_mlx->curtain_dir = 0;
		st_mlx->is_curtain = 0;
	}
}
