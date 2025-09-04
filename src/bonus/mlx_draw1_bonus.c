/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:15:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/04 23:40:36 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	set_door_texture(t_mlx *st_mlx)
{
	double	door_hit_point;

	if (st_mlx->is_door_col)
	{
		if (st_mlx->current_door->door_side == 0)
			door_hit_point = st_mlx->st_coord->p_posy
				+ (st_mlx->current_door->perp_door_dist * st_mlx->st_coord->ray_dir_y);
		else
			door_hit_point = st_mlx->st_coord->p_posx
				+ (st_mlx->current_door->perp_door_dist * st_mlx->st_coord->ray_dir_x);
		door_hit_point -= floor(door_hit_point);
		st_mlx->current_door->door_tex_x = (int)(door_hit_point
				* (double)st_mlx->door_texture->width);
		if (st_mlx->current_door->door_side == 0 && st_mlx->st_coord->ray_dir_x > 0)
			st_mlx->current_door->door_tex_x = st_mlx->door_texture->width
				- st_mlx->current_door->door_tex_x - 1;
		if (st_mlx->current_door->door_side == 1 && st_mlx->st_coord->ray_dir_y < 0)
			st_mlx->current_door->door_tex_x = st_mlx->door_texture->width
				- st_mlx->current_door->door_tex_x - 1;
		st_mlx->current_door->door_tex_step = 1.0
			* st_mlx->door_texture->height / st_mlx->current_door->door_line_height;
		st_mlx->current_door->door_tex_pos = (st_mlx->current_door->door_ceiling_height
				- (double)st_mlx->screen_height
				/ 2 + (double)st_mlx->current_door->door_line_height / 2) * st_mlx->current_door->door_tex_step;
	}
}

void	set_wall_texture(t_mlx *st_mlx, int wall_line_height)
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
	st_mlx->st_coord->wall_tex_pos = (st_mlx->wall_ceiling_height
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

int	set_heights(int line_height, int screen_height, int changer)
{
	int	height;

	height = line_height * changer / 2 + screen_height / 2;
	if (height < 0)
		height = 0;
	return (height);
}

void	draw_vertical_line(t_mlx *st_mlx, int screen_column)
{
	int	wall_line_height;

	st_mlx->z_buffer[screen_column] = st_mlx->st_coord->perp_wall_dist;
	if (st_mlx->is_door_col)
	{
		st_mlx->current_door->door_ceiling_height = set_heights(st_mlx->current_door->door_line_height,
				st_mlx->screen_height, -1);
		st_mlx->current_door->door_floor_height = set_heights(st_mlx->current_door->door_line_height,
				st_mlx->screen_height, 1);
		if (st_mlx->current_door->perp_door_dist < st_mlx->st_coord->perp_wall_dist
		&& !st_mlx->current_door->is_door_open)
			st_mlx->z_buffer[screen_column] = st_mlx->current_door->perp_door_dist;
	}
	wall_line_height = (int)(st_mlx->screen_height
			/ st_mlx->st_coord->perp_wall_dist);
	st_mlx->wall_ceiling_height = set_heights(wall_line_height,
			st_mlx->screen_height, -1);
	st_mlx->wall_floor_height = set_heights(wall_line_height,
			st_mlx->screen_height, 1);

	set_current_texture(st_mlx);
	set_door_texture(st_mlx);
	set_wall_texture(st_mlx, wall_line_height);
	default_drawing(st_mlx, screen_column);
	st_mlx->is_first_door = 0;
}
