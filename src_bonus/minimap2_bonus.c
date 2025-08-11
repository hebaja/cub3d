/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:10:39 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/11 13:40:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_paint_direction(t_mlx *st_mlx, int x, int y, int color)
{
	if (st_mlx->st_coord->ray_dir_x > 0 && st_mlx->st_coord->ray_dir_y < 0)
		ft_mlx_pixel_put(st_mlx->minimap,
			x * st_mlx->minimap_block_size + st_mlx->minimap_block_x,
			y * st_mlx->minimap_block_size + st_mlx->minimap_block_y, color);
	else if (st_mlx->st_coord->ray_dir_x < 0 && st_mlx->st_coord->ray_dir_y < 0)
		ft_mlx_pixel_put(st_mlx->minimap,
			(st_mlx->minimap_size - 1 - y)
			* st_mlx->minimap_block_size + st_mlx->minimap_block_y,
			x * st_mlx->minimap_block_size + st_mlx->minimap_block_x, color);
	else if (st_mlx->st_coord->ray_dir_x > 0 && st_mlx->st_coord->ray_dir_y > 0)
		ft_mlx_pixel_put(st_mlx->minimap,
			y * st_mlx->minimap_block_size + st_mlx->minimap_block_y,
			(st_mlx->minimap_size - 1 - x)
			* st_mlx->minimap_block_size + st_mlx->minimap_block_x, color);
	else
		ft_mlx_pixel_put(st_mlx->minimap,
			(st_mlx->minimap_size - 1 - x)
			* st_mlx->minimap_block_size + st_mlx->minimap_block_x,
			(st_mlx->minimap_size - 1 - y)
			* st_mlx->minimap_block_size + st_mlx->minimap_block_y, color);
}

void	paint_block(t_mlx *st_mlx, int x, int y, int color)
{
	st_mlx->minimap_block_x = -1;
	while (++st_mlx->minimap_block_x < st_mlx->minimap_block_size)
	{
		st_mlx->minimap_block_y = -1;
		while (++st_mlx->minimap_block_y < st_mlx->minimap_block_size)
			set_paint_direction(st_mlx, x, y, color);
	}
}

void	draw_column(t_mlx *st_mlx, int x, int init_x, int init_y)
{
	int	y;
	int	map_x;
	int	map_y;

	y = -1;
	map_x = init_x + x;
	while (++y < st_mlx->minimap_size)
	{
		map_y = init_y + y;
		if (map_y >= 0 && map_y < st_mlx->st_file->map_height && map_x >= 0
			&& st_mlx->st_file->map[map_y][map_x] == '1')
			paint_block(st_mlx, x, y, MM_WALL_COLOR);
		else if (map_y >= 0 && map_y < st_mlx->st_file->map_height
			&& map_x == st_mlx->abs_player_x && map_y == st_mlx->abs_player_y)
			animate_player(st_mlx, x, y);
		else if (map_y >= 0 && map_y < st_mlx->st_file->map_height && map_x >= 0
			&& (st_mlx->st_file->map[map_y][map_x] == '0'
			|| st_mlx->st_file->map[map_y][map_x] == 'N'
			|| st_mlx->st_file->map[map_y][map_x] == 'W'
			|| st_mlx->st_file->map[map_y][map_x] == 'S'
			|| st_mlx->st_file->map[map_y][map_x] == 'E'))
			paint_block(st_mlx, x, y, MM_SPACE_COLOR);
		else
			paint_block(st_mlx, x, y, MM_OUTER_COLOR);
	}
}

void	render_minimap(t_mlx *st_mlx)
{
	int	x;
	int	mm_init_x;
	int	mm_init_y;

	st_mlx->abs_player_x = (int)st_mlx->st_coord->p_posx;
	st_mlx->abs_player_y = (int)st_mlx->st_coord->p_posy;
	mm_init_x = st_mlx->abs_player_x - 3;
	mm_init_y = st_mlx->abs_player_y - 3;
	x = -1;
	while (++x < st_mlx->minimap_size)
		draw_column(st_mlx, x, mm_init_x, mm_init_y);
	mlx_put_image_to_window(st_mlx->mlx, st_mlx->win, st_mlx->minimap->img,
		12, 12);
}
