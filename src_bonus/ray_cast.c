/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:59:52 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/08 03:43:07 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	define_dists(t_mlx *st_mlx, int curr_map_x, int curr_map_y)
{
	if (st_mlx->st_coord->ray_dir_x < 0)
	{
		st_mlx->st_coord->step_x = -1;
		st_mlx->st_coord->side_dist_x = (st_mlx->st_coord->p_posx - curr_map_x)
			* st_mlx->st_coord->delta_dist_x;
	}
	else
	{
		st_mlx->st_coord->step_x = 1;
		st_mlx->st_coord->side_dist_x = (curr_map_x + 1.0
				- st_mlx->st_coord->p_posx) * st_mlx->st_coord->delta_dist_x;
	}
	if (st_mlx->st_coord->ray_dir_y < 0)
	{
		st_mlx->st_coord->step_y = -1;
		st_mlx->st_coord->side_dist_y = (st_mlx->st_coord->p_posy - curr_map_y)
			* st_mlx->st_coord->delta_dist_y;
	}
	else
	{
		st_mlx->st_coord->step_y = 1;
		st_mlx->st_coord->side_dist_y = (curr_map_y + 1.0
				- st_mlx->st_coord->p_posy) * st_mlx->st_coord->delta_dist_y;
	}
}

void	hit_wall(t_mlx *st_mlx, int *curr_map_x, int *curr_map_y)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (st_mlx->st_coord->side_dist_x < st_mlx->st_coord->side_dist_y)
		{
			st_mlx->st_coord->side_dist_x += st_mlx->st_coord->delta_dist_x;
			*curr_map_x = *curr_map_x + st_mlx->st_coord->step_x;
			st_mlx->st_coord->side_hit = 0;
		}
		else
		{
			st_mlx->st_coord->side_dist_y += st_mlx->st_coord->delta_dist_y;
			*curr_map_y = *curr_map_y + st_mlx->st_coord->step_y;
			st_mlx->st_coord->side_hit = 1;
		}
		if (st_mlx->st_file->map[*curr_map_y][*curr_map_x] == '1')
			hit = 1;
	}
}

void	calculate_perp_wall_dist(t_mlx *st_mlx, int curr_map_x, int curr_map_y)
{
	if (st_mlx->st_coord->side_hit == 0)
		st_mlx->st_coord->perp_wall_dist = (curr_map_x
				- st_mlx->st_coord->p_posx
				+ (1 - st_mlx->st_coord->step_x) / 2)
			/ st_mlx->st_coord->ray_dir_x;
	else
		st_mlx->st_coord->perp_wall_dist = (curr_map_y
				- st_mlx->st_coord->p_posy
				+ (1 - st_mlx->st_coord->step_y) / 2)
			/ st_mlx->st_coord->ray_dir_y;
}

void	calculate_ray(t_mlx *st_mlx, int screen_column)
{
	int		curr_map_x;
	int		curr_map_y;
	double	camera_x;

	curr_map_x = (int)st_mlx->st_coord->p_posx;
	curr_map_y = (int)st_mlx->st_coord->p_posy;
	camera_x = 2 * screen_column / (double)st_mlx->screen_width - 1;
	st_mlx->st_coord->ray_dir_x = st_mlx->st_coord->dir_vec_x
		+ st_mlx->st_coord->cam_plane_x * camera_x;
	st_mlx->st_coord->ray_dir_y = st_mlx->st_coord->dir_vec_y
		+ st_mlx->st_coord->cam_plane_y * camera_x;
	st_mlx->st_coord->delta_dist_x = fabs(1 / st_mlx->st_coord->ray_dir_x);
	st_mlx->st_coord->delta_dist_y = fabs(1 / st_mlx->st_coord->ray_dir_y);
	define_dists(st_mlx, curr_map_x, curr_map_y);
	hit_wall(st_mlx, &curr_map_x, &curr_map_y);
	calculate_perp_wall_dist(st_mlx, curr_map_x, curr_map_y);
	draw_vertical_line(st_mlx, screen_column);
}

void	ray_cast(t_mlx *st_mlx)
{
	int	screen_column;

	screen_column = 0;
	while (screen_column < st_mlx->screen_width)
	{
		calculate_ray(st_mlx, screen_column);
		screen_column++;
	}
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win,
		st_mlx->screen->img, 0, 0);
}
