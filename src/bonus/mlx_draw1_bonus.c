/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:15:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/20 03:16:23 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	set_wall_texture(t_mlx *st_mlx, int wall_line_height, int c_line_height)
{
	double	wall_hit_point;

	if (st_mlx->st_coord->side_hit == 0)
		wall_hit_point = st_mlx->st_coord->p_posy
			+ (st_mlx->st_coord->perp_wall_dist * st_mlx->st_coord->ray_dir_y);
	else
		wall_hit_point = st_mlx->st_coord->p_posx
			+ (st_mlx->st_coord->perp_wall_dist * st_mlx->st_coord->ray_dir_x);
	wall_hit_point -= floor(wall_hit_point);
	st_mlx->st_coord->wall_tex_x = (int)(wall_hit_point
			* (double)st_mlx->curr_texture->width);
	if (st_mlx->st_coord->side_hit == 0 && st_mlx->st_coord->ray_dir_x > 0)
		st_mlx->st_coord->wall_tex_x = st_mlx->curr_texture->width
			- st_mlx->st_coord->wall_tex_x - 1;
	if (st_mlx->st_coord->side_hit == 1 && st_mlx->st_coord->ray_dir_y < 0)
		st_mlx->st_coord->wall_tex_x = st_mlx->curr_texture->width
			- st_mlx->st_coord->wall_tex_x - 1;
	st_mlx->st_coord->wall_tex_step = 1.0
		* st_mlx->curr_texture->height / wall_line_height;
	st_mlx->st_coord->wall_tex_pos = (c_line_height
			- (double)st_mlx->screen_height / 2 + (double)wall_line_height / 2)
		* st_mlx->st_coord->wall_tex_step;
}

void	set_current_texture(t_mlx *st_mlx)
{
	if (st_mlx->st_coord->side_hit == 0 && st_mlx->st_coord->ray_dir_x < 0)
		st_mlx->curr_texture = st_mlx->we_texture;
	else if (st_mlx->st_coord->side_hit == 0)
		st_mlx->curr_texture = st_mlx->ea_texture;
	else if (st_mlx->st_coord->side_hit == 1 && st_mlx->st_coord->ray_dir_y < 0)
		st_mlx->curr_texture = st_mlx->no_texture;
	else
		st_mlx->curr_texture = st_mlx->so_texture;
}

void	draw_vertical_line(t_mlx *st_mlx, int screen_column)
{
	int	wall_line_height;
	int	c_line_height;
	int	f_line_height;

	st_mlx->z_buffer[screen_column] = st_mlx->st_coord->perp_wall_dist;
	wall_line_height = (int)(st_mlx->screen_height
			/ st_mlx->st_coord->perp_wall_dist);
	c_line_height = -wall_line_height / 2 + st_mlx->screen_height / 2;
	if (c_line_height < 0)
		c_line_height = 0;
	f_line_height = wall_line_height / 2 + st_mlx->screen_height / 2;
	if (f_line_height >= st_mlx->screen_height)
		f_line_height = st_mlx->screen_height - 1;
	set_current_texture(st_mlx);
	set_wall_texture(st_mlx, wall_line_height, c_line_height);
	if (!st_mlx->is_invert)
		default_drawing(st_mlx, screen_column, c_line_height, f_line_height);
	else
		invert_drawing(st_mlx, screen_column, c_line_height, f_line_height);
}
