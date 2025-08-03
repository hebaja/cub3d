/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 05:15:25 by hebatist          #+#    #+#             */
/*   Updated: 2025/07/31 16:34:03 by dbatista         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_mlx_pixel_put(t_mlx *st_mlx, int x, int y, int color)
{
	char	*dst;

	dst = st_mlx->screen_img_addr + (
			y * st_mlx->line_length + x * (st_mlx->screen_img_bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	draw_vertical_line(t_mlx *st_mlx, int screen_column)
{
	int	y;
	int	color;
	int	wall_line_height;
	int	c_line_height;
	int	f_line_height;

	//if (st_mlx->st_coord->side_hit == 1)
		//color = 0xFFFFFF;
	//else
	color = 10573867;
	wall_line_height = (int)(st_mlx->screen_height
			/ st_mlx->st_coord->perp_wall_dist);
	c_line_height = -wall_line_height / 2 + st_mlx->screen_height / 2;
	f_line_height = wall_line_height / 2 + st_mlx->screen_height / 2;
	y = -1;
	while (++y < st_mlx->screen_height)
	{
		if (y < c_line_height)
			ft_mlx_pixel_put(st_mlx, screen_column, y, st_mlx->c_color);
		else if (y >= c_line_height && y <= f_line_height)
			ft_mlx_pixel_put(st_mlx, screen_column, y, color);
		else
			ft_mlx_pixel_put(st_mlx, screen_column, y, st_mlx->f_color);
	}
}
