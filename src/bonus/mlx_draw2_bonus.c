/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebatist <hebatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:50:04 by hebatist          #+#    #+#             */
/*   Updated: 2025/08/31 19:29:26 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	ft_mlx_pixel_put(t_img *st_img, int x, int y, int color)
{
	char	*dst;

	dst = st_img->img_addr + (
			y * st_img->size_line + x * (st_img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	put_door_texture_pixel(t_mlx *st_mlx, int screen_column, int y)
{
	int				tex_y;
	int				tex_offset;
	unsigned int	color;

	if (st_mlx->is_invert)
	{
		tex_y = st_mlx->door_texture->height - 1 - (int)st_mlx->door_tex_pos;
		if (tex_y < 0)
		    tex_y = 0;
		else if (tex_y >= st_mlx->door_texture->height)
		    tex_y = st_mlx->door_texture->height - 1;
	}
	else
		tex_y = (int)st_mlx->door_tex_pos;
	st_mlx->door_tex_pos += st_mlx->door_tex_step;
	tex_offset = tex_y * st_mlx->door_texture->size_line
		+ st_mlx->door_tex_x * (st_mlx->door_texture->bpp / 8);
	color = *(unsigned int *)(st_mlx->door_texture->img_addr + tex_offset);
	ft_mlx_pixel_put(st_mlx->screen, screen_column, y, color);
}

void	put_wall_texture_pixel(t_mlx *st_mlx, int screen_column, int y)
{
	int				tex_y;
	int				tex_offset;
	unsigned int	color;

	if (st_mlx->is_invert)
	{
		tex_y = st_mlx->curr_texture->height - 1 - (int)st_mlx->st_coord->wall_tex_pos;
		if (tex_y < 0)
		    tex_y = 0;
		else if (tex_y >= st_mlx->curr_texture->height)
		    tex_y = st_mlx->curr_texture->height - 1;
	}
	else
		tex_y = (int)st_mlx->st_coord->wall_tex_pos;
	st_mlx->st_coord->wall_tex_pos += st_mlx->st_coord->wall_tex_step;
	tex_offset = tex_y * st_mlx->curr_texture->size_line
		+ st_mlx->st_coord->wall_tex_x * (st_mlx->curr_texture->bpp / 8);
	color = *(unsigned int *)(st_mlx->curr_texture->img_addr + tex_offset);
	ft_mlx_pixel_put(st_mlx->screen, screen_column, y, color);
}

int	set_ceiling_color(t_mlx *st_mlx)
{
	int	ceiling_color;
	
	ceiling_color = st_mlx->c_color;
	if (st_mlx->is_invert)
		ceiling_color = st_mlx->f_color;
	return (ceiling_color);
}

int	set_floor_color(t_mlx *st_mlx)
{
	int	floor_color;
	
	floor_color = st_mlx->f_color;
	if (st_mlx->is_invert)
		floor_color = st_mlx->c_color;
	return (floor_color);
}

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
	if (y < st_mlx->door_ceiling_height)
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			ceiling_color);
	else if (y >= st_mlx->door_ceiling_height && y <= st_mlx->door_floor_height)

		if (is_anim)
		{
			if (!st_mlx->is_door_open)
				put_door_texture_pixel(st_mlx, screen_column, y);
			else
				basic_drawing(st_mlx, screen_column, y);
		}
		else
			put_door_texture_pixel(st_mlx, screen_column, y);
	else
		ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
			floor_color);
}

void	animate_door(t_mlx *st_mlx, int screen_column, int y)
{
	float	door_open_ratio;
	int		door_height;
	int		vertical_position;
	int		ceiling_color;
	int		floor_color;

	ceiling_color = set_ceiling_color(st_mlx);
	floor_color = set_floor_color(st_mlx);
	door_open_ratio = (float)st_mlx->door_offset / 100.0f;
	door_height = (int)((st_mlx->door_floor_height - st_mlx->door_ceiling_height) * door_open_ratio);
	vertical_position = y - st_mlx->door_ceiling_height;
	if (vertical_position < (door_height))
	{
		if (y < st_mlx->wall_ceiling_height)
			ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
				ceiling_color);
		else if (y >= st_mlx->wall_ceiling_height && y <= st_mlx->wall_floor_height)
			put_wall_texture_pixel(st_mlx, screen_column, y);
		else
			ft_mlx_pixel_put(st_mlx->screen, screen_column, y,
				floor_color);
	}
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
			if (!st_mlx->is_door_col)
				basic_drawing(st_mlx, screen_column, y);
			else
			{
				if (!st_mlx->is_door_anim)
					with_door_drawing(st_mlx, screen_column, y, 1);
				else
					animate_door(st_mlx, screen_column, y);
			}
		}
	}
}
