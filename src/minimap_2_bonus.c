/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:45:03 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/08 02:45:33 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	paint_player_area(t_mlx *st_mlx, int x, int y, int color)
{
	ft_mlx_pixel_put(st_mlx->minimap,
		x * st_mlx->minimap_block_size + st_mlx->minimap_block_x,
		y * st_mlx->minimap_block_size + st_mlx->minimap_block_y,
		color);
}

void	paint_player(t_mlx *st_mlx, int x, int y)
{
	int	start_paint_x;
	int	end_paint_x;

	start_paint_x = st_mlx->minimap_block_size / 2;
	end_paint_x = start_paint_x;
	st_mlx->minimap_block_y = -1;
	while (++st_mlx->minimap_block_y < st_mlx->minimap_block_size)
	{
		st_mlx->minimap_block_x = -1;
		while (++st_mlx->minimap_block_x < st_mlx->minimap_block_size)
		{
			if (st_mlx->minimap_block_x >= start_paint_x
				&& st_mlx->minimap_block_x <= end_paint_x)
				paint_player_area(st_mlx, x, y, MM_PLAY_COLOR);
			else
				paint_player_area(st_mlx, x, y, MM_SPACE_COLOR);
		}
		if (st_mlx->minimap_block_y % 3 == 0)
		{
			start_paint_x--;
			end_paint_x++;
		}
	}
}
