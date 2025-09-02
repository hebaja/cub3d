/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:50:04 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/01 20:39:03 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"
#include "bonus_struct.h"

void	basic_drawing(t_mlx *st_mlx, int screen_column, int y)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = set_ceiling_color(st_mlx);
	floor_color = set_floor_color(st_mlx);
	if (y < st_mlx->wall_ceiling_height)
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			ceiling_color);
	else if (y >= st_mlx->wall_ceiling_height && y <= st_mlx->wall_floor_height)
		put_wall_texture_pixel(st_mlx, screen_column, y);
	else
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			floor_color);
}

void	with_door_drawing(t_mlx *st_mlx, int screen_column, int y, int is_anim)
{
	int	ceiling_color;
	int	floor_color;

	ceiling_color = set_ceiling_color(st_mlx);
	floor_color = set_floor_color(st_mlx);
	if (y < st_mlx->st_file->doors->door_ceiling_height)
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			ceiling_color);
	else if (y >= st_mlx->st_file->doors->door_ceiling_height && y <= st_mlx->st_file->doors->door_floor_height)
	{
		if (is_anim)
		{
			if (!st_mlx->st_file->doors->is_door_open)
				put_door_texture_pixel(st_mlx, screen_column, y);
			else
				basic_drawing(st_mlx, screen_column, y);
		}
		else
			put_door_texture_pixel(st_mlx, screen_column, y);
	}
	else
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			floor_color);
}

void	animate_door(t_mlx *st_mlx, int screen_column, int y)
{
	float	door_open_ratio;
	int		door_height;
	int		vertical_position;

	door_open_ratio = (float)st_mlx->st_file->doors->door_offset / 100.0f;
	door_height = (int)((st_mlx->st_file->doors->door_floor_height
				- st_mlx->st_file->doors->door_ceiling_height) * door_open_ratio);
	vertical_position = y - st_mlx->st_file->doors->door_ceiling_height;
	if (vertical_position < (door_height))
		basic_drawing(st_mlx, screen_column, y);
	else
		with_door_drawing(st_mlx, screen_column, y, 0);
}

void	default_drawing(t_mlx *st_mlx, int screen_column)
{
	int	y;

	y = -1;
	while (++y < st_mlx->screen_height)
	{
		if (st_mlx->is_curtain && y < st_mlx->curtain_y)
			ft_mlx_pixel_put(st_mlx->screen, screen_column, y, 0x000000);
		else
		{
			if (!st_mlx->st_file->doors->is_door_col)
				basic_drawing(st_mlx, screen_column, y);
			else
			{
				if (!st_mlx->st_file->doors->is_door_anim)
					with_door_drawing(st_mlx, screen_column, y, 1);
				else
					animate_door(st_mlx, screen_column, y);
			}
		}
	}
}
