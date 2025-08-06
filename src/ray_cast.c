/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 04:59:52 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/06 15:08:19 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

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

void	paint_block(t_mlx *st_mlx, int x, int y, int block_size, int color, int flag)
{
	int	dx;
	int	dy;
	int pos_x;
	int pos_y;

	dx = -1;
	while (++dx < block_size)
	{
		dy = -1;
		while (++dy < block_size)
		{
			if (flag == 2 || flag == 3)
			{
				pos_x = x * block_size + dx;
				pos_y = y * block_size + dy;
			}
			else if (flag == 1)
			{
				pos_x = (st_mlx->minimap_size - 1 - y) * block_size + dx;
                pos_y = x * block_size + dy;
			}
			else
			{
				pos_x = y * block_size + dx;
                pos_y = (st_mlx->minimap_size - 1 - x) * block_size + dy;
			}
			ft_mlx_pixel_put(st_mlx->minimap, pos_x, pos_y, color);
		}
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->minimap->img, 12, 12);
	}
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	draw_column(t_mlx *st_mlx, int x, int init_x, int init_y, int player_x, int player_y, int flag)
{
	int	y;
	int map_x;
	int map_y;
	int	map_height;

	y = -1;
	if (flag == 0)
		map_x = init_y + y;
	else if (flag == 1)
		map_x = init_y - y;
	else if (flag == 2)
		map_x = init_x + x;
	else
		map_x = init_x - x;

	map_height = get_map_height(st_mlx->st_file->map);
	while (++y < st_mlx->minimap_size)
	{

		if (flag == 0)
			map_y = init_x + x;
		else if (flag == 1)
			map_y = init_x - x;
		else if (flag == 2)
			map_y = init_y + y;
		else
			map_y = init_y - y;

		if (map_y >= 0 && map_y < map_height && st_mlx->st_file->map[map_y][map_x] == '1')
			paint_block(st_mlx, x, y, st_mlx->minimap_block_size, 16777215, flag);
		else if (map_y >= 0 && map_y < map_height && map_x == player_x && map_y == player_y)
			paint_block(st_mlx, x, y, st_mlx->minimap_block_size, 10360107, flag);
		else
			paint_block(st_mlx, x, y, st_mlx->minimap_block_size, 2568960, flag);
	}
}

void	render_minimap(t_mlx *st_mlx)
{
	int	x;
	int player_x;
    int player_y;
    int mm_init_x;
    int mm_init_y;
	int	flag;
	
	player_x = (int)st_mlx->st_coord->p_posx;
    player_y = (int)st_mlx->st_coord->p_posy;

	if (st_mlx->st_coord->ray_dir_x < 0 && st_mlx->st_coord->ray_dir_y < 0)
	{
		mm_init_x = player_x - 2;
		mm_init_y = player_y + 2;
		flag = 0;
		
	}
	else if (st_mlx->st_coord->ray_dir_x > 0 && st_mlx->st_coord->ray_dir_y > 0)
	{
		mm_init_x = player_x + 2;
		mm_init_y = player_y - 2;
		flag = 1;
	}
	else if (st_mlx->st_coord->ray_dir_x > 0 && st_mlx->st_coord->ray_dir_y < 0)
	{
		mm_init_x = player_x - 2;
		mm_init_y = player_y - 2;
		flag = 2;
	}
	else
	{
		mm_init_x = player_x + 2;
		mm_init_y = player_y + 2;
		flag = 3;
	}


	if (flag == 2 || flag == 3)
	{
		x = -1;
		while (++x < st_mlx->minimap_size)
			draw_column(st_mlx, x, mm_init_x, mm_init_y, player_x, player_y, flag);
	}
	else
	{
		x = st_mlx->minimap_size;
		while (--x >= 0)
			draw_column(st_mlx, x, mm_init_x, mm_init_y, player_x, player_y, flag);

	}

	// mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->minimap->img, 12, 12);
	// printf("%d - %d\n", mm_init_x, mm_init_y);
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
	
	render_minimap(st_mlx);
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->minimap->img, 12, 12);



}
