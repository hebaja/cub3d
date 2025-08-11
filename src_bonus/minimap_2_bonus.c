/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:45:03 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/08 03:42:04 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include <stdio.h>
#include <sys/time.h>

void	paint_player_area(t_mlx *st_mlx, int x, int y, int color)
{
	ft_mlx_pixel_put(st_mlx->minimap,
		x * st_mlx->minimap_block_size + st_mlx->minimap_block_x,
		y * st_mlx->minimap_block_size + st_mlx->minimap_block_y,
		color);
}

void	paint_player(t_mlx *st_mlx, int x, int y, int color)
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
				paint_player_area(st_mlx, x, y, color);
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		perror("gettimeofday() error");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	animate_player(t_mlx *st_mlx, int x, int y)
{
	size_t time;

	if (st_mlx->minimap_counter == 0)
		st_mlx->minimap_anim_dir = 0;
	if (st_mlx->minimap_counter == 10)
		st_mlx->minimap_anim_dir = 1;

	time = get_current_time();

	// printf("%lu\n", time - st_mlx->minimap_time);

	if (time - st_mlx->minimap_time >= 100)
	{
		st_mlx->minimap_time = time;
		paint_player(st_mlx, x, y, st_mlx->minimap_colors[st_mlx->minimap_counter]);
		if (st_mlx->minimap_anim_dir == 0)
			st_mlx->minimap_counter++;
		else
			st_mlx->minimap_counter--;
	}

	// if (st_mlx->minimap_frame == 0)
	// 	st_mlx->minimap_frame = get_current_time();

	if (st_mlx->minimap_anim_dir == 0)
		st_mlx->minimap_frame++;
	if (st_mlx->minimap_anim_dir == 1)
		st_mlx->minimap_frame--;
}
