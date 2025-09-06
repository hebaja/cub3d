/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_draw3_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbatista <dbatista@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 20:53:42 by hebatist          #+#    #+#             */
/*   Updated: 2025/09/04 14:46:20 by hebatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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
		tex_y = st_mlx->door_texture->height - 1 - (int)st_mlx->current_door->door_tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= st_mlx->door_texture->height)
			tex_y = st_mlx->door_texture->height - 1;
	}
	else
		tex_y = (int)st_mlx->current_door->door_tex_pos;
	st_mlx->current_door->door_tex_pos += st_mlx->current_door->door_tex_step;
	tex_offset = tex_y * st_mlx->door_texture->size_line
		+ st_mlx->current_door->door_tex_x * (st_mlx->door_texture->bpp / 8);
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
		tex_y = st_mlx->curr_texture->height
			- 1 - (int)st_mlx->st_coord->wall_tex_pos;
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
