/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:15:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/30 04:37:03 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
#include <stdio.h>

void    set_wall_texture(t_mlx *st_mlx, int wall_line_height, int door_line_height, int w_c_line_height, int d_c_line_height)
{
        double  wall_hit_point;
		double	door_hit_point;

	wall_hit_point = 0.0;
	door_hit_point = 0.0;

	if (st_mlx->is_door_col)
	{
        if (st_mlx->door_side == 0)
                door_hit_point = st_mlx->st_coord->p_posy
                        + (st_mlx->perp_door_dist * st_mlx->st_coord->ray_dir_y);
        else
                door_hit_point = st_mlx->st_coord->p_posx
                        + (st_mlx->perp_door_dist * st_mlx->st_coord->ray_dir_x);

        door_hit_point -= floor(door_hit_point);
        st_mlx->door_tex_x = (int)(door_hit_point
                        * (double)st_mlx->door_texture->width);
        
        if (st_mlx->door_side == 0 && st_mlx->st_coord->ray_dir_x > 0)
                st_mlx->door_tex_x = st_mlx->door_texture->width
                        - st_mlx->door_tex_x - 1;
        if (st_mlx->door_side == 1 && st_mlx->st_coord->ray_dir_y < 0)
                st_mlx->door_tex_x = st_mlx->door_texture->width
                        - st_mlx->door_tex_x - 1;
        
        st_mlx->door_tex_step = 1.0
                * st_mlx->door_texture->height / door_line_height;
        st_mlx->door_tex_pos = (d_c_line_height
                        - (double)st_mlx->screen_height / 2 + (double)door_line_height / 2)
                * st_mlx->door_tex_step;
	
	}
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
	st_mlx->st_coord->wall_tex_pos = (w_c_line_height
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
	int	door_line_height;
	int	w_c_line_height;
	int	w_f_line_height;
	int	d_c_line_height;
	int	d_f_line_height;

	st_mlx->z_buffer[screen_column] = st_mlx->st_coord->perp_wall_dist;

	wall_line_height = (int)(st_mlx->screen_height
			/ st_mlx->st_coord->perp_wall_dist);
	door_line_height = (int)(st_mlx->screen_height
			/ st_mlx->perp_door_dist);

	w_c_line_height = -wall_line_height / 2 + st_mlx->screen_height / 2;
	if (w_c_line_height < 0)
		w_c_line_height = 0;
	w_f_line_height = wall_line_height / 2 + st_mlx->screen_height / 2;
	if (w_f_line_height >= st_mlx->screen_height)
		w_f_line_height = st_mlx->screen_height - 1;
	
	d_c_line_height = -door_line_height / 2 + st_mlx->screen_height / 2;
	if (d_c_line_height < 0)
		d_c_line_height = 0;
	d_f_line_height = door_line_height / 2 + st_mlx->screen_height / 2;
	if (d_f_line_height >= st_mlx->screen_height)
		d_f_line_height = st_mlx->screen_height - 1;

	set_current_texture(st_mlx);
	set_wall_texture(st_mlx, wall_line_height, door_line_height, w_c_line_height, d_c_line_height);
	
	if (!st_mlx->is_invert)
		default_drawing(st_mlx, screen_column, w_c_line_height, w_f_line_height, d_c_line_height, d_f_line_height);
	else
		invert_drawing(st_mlx, screen_column, w_c_line_height, w_f_line_height);
}
